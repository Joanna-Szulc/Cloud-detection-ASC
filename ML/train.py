# -*- coding: utf-8 -*-
"""
Created on Tue Apr 28 14:09:39 2020

@author: sklep
"""
from keras.callbacks import ModelCheckpoint
from keras.callbacks import CSVLogger
from keras.callbacks import EarlyStopping
from keras.optimizers import Adam

import os

import model

from keras.preprocessing.image import ImageDataGenerator

train_datagen = ImageDataGenerator(
        rescale=1./255,
        shear_range=0.2,
        zoom_range=0.2,
        horizontal_flip=True)
        
val_datagen = ImageDataGenerator(rescale=1./255)

train_image_generator = train_datagen.flow_from_directory(
'./data/subdir/',
batch_size = 8)

train_mask_generator = train_datagen.flow_from_directory(
'./data/subdir/',
batch_size = 8)

val_image_generator = val_datagen.flow_from_directory(
'./data/subdir/',
batch_size = 8)

val_mask_generator = val_datagen.flow_from_directory(
'./data/subdir/',
batch_size = 8)

train_generator = zip(train_image_generator, train_mask_generator)
val_generator = zip(val_image_generator, val_mask_generator)

NO_OF_TRAINING_IMAGES = len(os.listdir('./data/subdir/train_frames/'))
NO_OF_VAL_IMAGES = len(os.listdir('./data/subdir/val_frames/'))

NO_OF_EPOCHS = 5

BATCH_SIZE = 8

weights_path = './results/'

m = model.FCN_Vgg16_32s()
opt = Adam(lr=1E-5, beta_1=0.9, beta_2=0.999, epsilon=1e-08)

m.compile(loss='dice_loss',
              optimizer=opt,
              metrics='accuracy')

checkpoint = ModelCheckpoint(weights_path, monitor='METRIC_TO_MONITOR', 
                             verbose=1, save_best_only=True, mode='max')

csv_logger = CSVLogger('./log.out', append=True, separator=';')

earlystopping = EarlyStopping(monitor = 'METRIC_TO_MONITOR', verbose = 1,
                              min_delta = 0.01, patience = 3, mode = 'max')

callbacks_list = [checkpoint, csv_logger, earlystopping]

results = m.fit_generator(train_generator, epochs=NO_OF_EPOCHS, 
                          steps_per_epoch = (NO_OF_TRAINING_IMAGES//BATCH_SIZE),
                          validation_data=val_generator, 
                          validation_steps=(NO_OF_VAL_IMAGES//BATCH_SIZE), 
                          callbacks=callbacks_list)


# test_acc = model.evaluate(test_images, test_masks)
# print('Test accuracy:', test_acc)

m.save('OLOF3.h5')
