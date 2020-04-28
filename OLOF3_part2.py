# -*- coding: utf-8 -*-
"""
Created on Tue Apr 28 13:05:14 2020

Tutorial for image segmentation using neural networks:
https://towardsdatascience.com/a-keras-pipeline-for-image-segmentation-part-1-6515a421157d

Part Two: preparing the batches
"""
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