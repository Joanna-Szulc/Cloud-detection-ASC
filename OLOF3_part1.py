# -*- coding: utf-8 -*-
"""
Created on Mon Apr 27 10:41:49 2020

Labelling test: does images labelled in photoshop are alright?

Are images using Labelbox better?

Tested on tutorial for image segmentation using neural networks:
https://towardsdatascience.com/a-keras-pipeline-for-image-segmentation-part-1-6515a421157d

Part One: setting up folders for training, testing and validation
"""
import os
import random
import re
from PIL import Image

DATA_PATH = './data/'
FRAME_PATH = DATA_PATH + '/img/'
MASK_PATH = DATA_PATH + '/masks/'

# Create folders to hold images and masks
folders = ['train_frames', 'train_masks', 'val_frames', 'val_masks', 'test_frames', 'test_masks']

for folder in folders:
    os.makedirs(DATA_PATH + folder)

# Get all frames and masks, sort them, shuffle them to generate data sets.
all_frames = os.listdir(FRAME_PATH)
all_masks = os.listdir(MASK_PATH)

all_frames.sort(key=lambda var:[int(x) if x.isdigit() else x 
                                for x in re.findall(r'[^0-9]|[0-9]+', var)])
all_masks.sort(key=lambda var:[int(x) if x.isdigit() else x 
                               for x in re.findall(r'[^0-9]|[0-9]+', var)])

random.seed(230)
random.shuffle(all_frames)
random.seed(230)
random.shuffle(all_masks)

# Generate train, val, and test sets for frames
train_split = int(0.7*len(all_frames))
val_split = int(0.9 * len(all_frames))

train_frames = all_frames[:train_split]
val_frames = all_frames[train_split:val_split]
test_frames = all_frames[val_split:]

# Generate corresponding mask lists for masks
train_masks = all_masks[:train_split]
val_masks = all_masks[train_split:val_split]
test_masks = all_masks[val_split:]

# Add train, val, test frames and masks to relevant folders
def add_frames(dir_name, image):
    img = Image.open(FRAME_PATH + image)
    img.save(DATA_PATH + '/{}'.format(dir_name)+'/' + image)


def add_masks(dir_name, image):
    img = Image.open(MASK_PATH + image)
    img.save(DATA_PATH + '/{}'.format(dir_name) + '/' + image)


frame_folders = [(train_frames, 'train_frames'), (val_frames, 'val_frames'), 
                 (test_frames, 'test_frames')]

mask_folders = [(train_masks, 'train_masks'), (val_masks, 'val_masks'), 
                (test_masks, 'test_masks')]

# Add frames
for folder in frame_folders:  
    array = folder[0]
    name = [folder[1]] * len(array)

    list(map(add_frames, name, array))

# Add masks
for folder in mask_folders:
    array = folder[0]
    name = [folder[1]] * len(array)
    list(map(add_masks, name, array))