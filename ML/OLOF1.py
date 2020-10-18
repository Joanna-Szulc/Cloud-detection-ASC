# -*- coding: utf-8 -*-
"""
Created on Thu Apr 23 20:06:27 2020

Simple neural network trained and tested on MNIST dataset of handwritten digits
Tutorial based on: https://towardsdatascience.com/deep-learning-for-beginners-practical-guide-with-python-and-keras-d295bfca4487
"""

import keras
from keras.datasets import mnist #  import mnist dataset
import matplotlib.pyplot as plt
from keras.utils import to_categorical
import numpy as np

(x_train, y_train), (x_test, y_test) = mnist.load_data() #  load training and testing data set

#  x are input information, numpy arrays that contain pictures of the handwritten
#  numbers, train has 60 000 pictures and test has 10 000 pictures both are 28x28 pixels
#  y are array of answers, outputs, saying what number it really is

# plt.imshow(x_train[9999], cmap=plt.cm.binary)
print(y_train[9999])

print(x_train.ndim) #  print number of dimnesions
print(x_train.shape) #  print shape of tensor
print(x_train.dtype) #  print type of data in tensor

#  normalize the data to floats in range [0, 1]
x_train = x_train.astype('float32')
x_test = x_test.astype('float32')
x_train /= 255
x_test /= 255

#  flatten to 1D arrays by concotating
x_train = x_train.reshape(60000, 784)
x_test = x_test.reshape(10000, 784)

#  change output numbers into vectors containing probability of being the right
#  input (which is 1. for the known data)
y_train = to_categorical(y_train, num_classes=10)
y_test = to_categorical(y_test, num_classes=10)
print("After to categoricaly")
print(y_test[0])
print(y_train[0])
print(y_train.shape)
print(y_test.shape)

#  and now to actually creating the NN
from keras.models import Sequential
from keras.layers.core import Dense, Activation
model = Sequential()
#  two layers, densly connected (fully connected), activated by sigmoid and
#  softmax, we only need to define the input shape and keras will deduce the
#  rest
model.add(Dense(10, activation='sigmoid', input_shape=(784,)))
model.add(Dense(10, activation='softmax')) #  this is output layer
#  to look up our model we write:
model.summary()

#  adjusting the way the NN learns, you can read more about loss, optimizer and
#  metrics elsewhere
model.compile(loss='categorical_crossentropy',
              optimizer='sgd',
              metrics = ['accuracy'])
#  training!
model.fit(x_train, y_train, batch_size=100, epochs=5)

#  evaluating
test_loss, test_acc = model.evaluate(x_test, y_test)
print('Test accuracy:', test_acc)

predictions = model.predict(x_test)
print(np.argmax(predictions[11]))