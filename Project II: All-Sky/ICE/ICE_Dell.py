# -*- coding: utf-8 -*-
"""
Created: 28.05.2020

ICE v 1.3: Intensity Check Executive

This is a script used to create .exe file that runs the intensity check of 
the photos for the uioCam v 2.1. The script picks up a .jpg file from
a predefined uioCam folder \last\, detects the circular area of the
photo, crops it, substracts the black pixels in the corners and based
on the amount of dark, grey and bright pixels checks if the photo is
well exposed. The script returns the result as a exposure.txt file stating
the exposure according to key: 0 - underexposed, 1 - good exposure,
2 - overexposed.

The thresholds for the exposure check are set in "\etc\thresholds.txt" as
dark_down, dark_up, grey_down, grey_up, bright_down and bright_up and
may require adjusting after farther testing.

If the picture is well exposed the script deletes the .jpg file and
moves the .arw file to \RAW\ folder. If the photo is under- or over-
exposed the script will delete both .jpg and .arw files.

Based on exposure.txt file uioCam will either move on to make another
picture or will adjust shutter speed to improve the exposure and repeat
making the photo.

ICE requires extensive testing, especially during the night hours,
which was not possible at the time of development (because of the
midnight sun).

Known issues: If the script won't find any .jpg files in the specified folder
it will encounter an error while trying to sort files by time in line 238. 

uioCam v 2.1 is a C++ based application for running the All-Sky system
at Alomar Observatory.

cv2 is a python wrapper for C++ image processing library OpenCV:
    https://opencv.org/

Created for Anodya Space Center in 2020.

More information available in the All-Sky manual and the internship
report.

This version includes paths for uioCam v2.1 compiled at Dell computer
at Alomar Observatory.

Author: joanna.szulc.pl@gmail.com
"""
import numpy as np
import cv2 as cv
#import re
import os
import math
import warnings


#  Set coordinates of the all-sky image relative to image size based on Hough circle detection
#  algorithm. detected_circle is [[[(y_coord_centre, x_coord_centre, radius)]]]
def circle_coordinates(image_copy):
    width = image_copy.shape[1]
    height = image_copy.shape[0]
    #  Scale down
    scale = 6
    dsize = (int(image_copy.shape[1] / scale), int(image_copy.shape[0] / scale))
    image_copy = cv.resize(image_copy, dsize)
    # Convert to grayscale
    grey = cv.cvtColor(image_copy, cv.COLOR_RGB2GRAY)

    # Blur
    blurred = cv.GaussianBlur(grey, (5, 5), 0)
    ret,th = cv.threshold(blurred, 0, 255, cv.THRESH_BINARY + cv.THRESH_OTSU)
    #  if the image is too blurred the Hough transform won't
    #  detect the main circle, if it's too sharp then it can detect additional circles from
    #  clouds and even reflection of the fish-eye lens in the dome
    
    # Apply Hough transform on the blurred image
    detected_circle = cv.HoughCircles(th,
                                      cv.HOUGH_GRADIENT,  #  faster Hough algorithm
                                      dp=1,  #  ratio of the original image to accumulator matrix
                                      minDist=2000,  #  min. distance between circles
                                      param1=100,  #  canny edge detection parameter
                                      param2=10,  #  accumulator threshold for the circle candidates
                                      minRadius=int((dsize[1] / 2) * 0.7),  # radius no smaller than 0.3 of the image height
                                      maxRadius=int((dsize[1] / 2)))#  radius no larger than half of the image height

    try:
        detected_circle = detected_circle * scale  #  scale the circle back to the full size

    except TypeError:
        warnings.warn('No circle of all-sky image detected. Assuming default position of all-sky photo.')
        x_coordinate = int((width - width * 0.01)/ 2)
        y_coordinate = int((height + height * 0.05) / 2)
        radius = int(height * 0.87 / 2)
        #  tmp and fake_circle is needed because HoughCircles returns [[[x, y, r]]], not [x, y, r]
        fake_circle = [x_coordinate, y_coordinate, radius]
        detected_circle = []
        tmp = [fake_circle]
        detected_circle.append(tmp)
            
    return detected_circle[0]


#  Detect the circular photo area, crop to it, count the black pixels around the photo
def crop_image(image):
    image_copy = image

    detected_circle = circle_coordinates(image_copy)  #  detect photo area

    y_coordinate = int(detected_circle[0][0])  #  y-coord of the centre of the circle
    x_coordinate = int(detected_circle[0][1])  #  x-coord of the centre of the circle
    radius = int(detected_circle[0][2])
    
    offset_y = y_coordinate - radius
    offset_x = x_coordinate - radius
    
    begin_height = offset_y
    end_height = offset_y + radius * 2
    begin_width = offset_x
    end_width = offset_x + radius * 2

    cropped_image = image[begin_width:end_width, begin_height:end_height, :]
    
    # And now count the black pixels that are beyond the circle subtracting the area of a disk
    # from a square of the cropped image.
    width = cropped_image.shape[1]
    height = cropped_image.shape[0]
    masked_count = int((width * height) - (math.pi * radius ** 2))
    
    return cropped_image, masked_count


#  Transform sunmoon position to cartesian coordinates
def transform_to_cartesian(angles):
    d2r = np.pi/180
    sun_zenith = (90-float(angles[0]))*d2r      # degrees
    sun_azimuth = float(angles[1])*d2r     # degrees
    x_s = np.sin(sun_zenith)*np.cos(sun_azimuth)    # x_s/R
    y_s = np.sin(sun_zenith)*np.sin(sun_azimuth)    # y_s/R
    z_s = np.cos(sun_zenith)                        # z_s/R
    return x_s, y_s, z_s


#  Read the sunmoon file from uioCam and mask the sun from the histogram - not needed after all
#def mask_sun(sunmoon_path, cropped_image):
#    with open(sunmoon_path, 'rb') as f:     # Ensure that the text is UTF-8
#        data = str(f.read())        # Read file
#        angles = [s for s in re.findall(r'\d+\.\d+',data)]  # Store angles in list
#    coordinates = transform_to_cartesian(angles)
#    width = cropped_image.shape[0]
#    height = cropped_image.shape[1]
#    
#    R = int(width / 1.5)
#    X_s, Y_s = int(np.int(height / 2) + coordinates[0] * R), int(R - coordinates[1] * R)    # Sun coordinates on the image
#
#    histogram_image = cv.cvtColor(cropped_image, cv.COLOR_BGR2GRAY)
#
#    center_coordinates = (X_s, Y_s)
#    r_sun = int(width * 0.07)  # Radius of sun region
#
#    #  Make the circle covering the sun the average colour
#    avg_intensity = int(np.sum(histogram_image)/(width*height))
#    color = (avg_intensity, avg_intensity, avg_intensity)
#    thickness = -1  #  value > 0 circle, -1 = disk
#    histogram_image = cv.circle(histogram_image, center_coordinates, r_sun, color, thickness)
#    return histogram_image


class InvalidImageError(ValueError):
    pass


def check_histogram(histogram_image, masked_count, thresholds):
    #  Divide pixels into dark, grey and bright, thresholds is a tuple of shape:
    #  ((dark_down, dark_up), (grey_down, grey_up), (bright_down, bright_up)),
    #  the scale for RGB is 0-255
    dark = thresholds[0]
    grey = thresholds[1]
    bright = thresholds[2]
    
    histogram = histogram_image.ravel()  #  flatten the array into 1D

    #  Seperate pixels into dark, grey and bright
    histogram_dark = histogram[(histogram >= dark[0]) & (histogram <= dark[1])]
    histogram_grey = histogram[(histogram >= grey[0]) & (histogram <= grey[1])]
    histogram_bright = histogram[(histogram >= bright[0]) & (histogram <= bright[1])]

    dark_count = histogram_dark.shape[0] - masked_count  #  substract the black corners
    grey_count = histogram_grey.shape[0]
    bright_count = histogram_bright.shape[0]
    all_count = dark_count + grey_count + bright_count

    #  Actual exposure check
    if all_count > 0:
        ratio_dark = (dark_count / all_count, "U")
        ratio_grey = (grey_count / all_count, "G")  #  U - underexposed, G - good exposure,
        ratio_bright = (bright_count / all_count, "O")  #  O - overexposed
    else:
        raise InvalidImageError("No data in brightness histogram")

    ratios = [ratio_dark, ratio_grey, ratio_bright]
    ratios.sort(reverse=True)  # sort from largest to smallest value
    exposureIs = ratios[0][1]  # after sorting the letter describing the photo

    #  This path must be the same as in uioCam for uioCam to work
    exposure_out = "C:\\Users\\Student\\Desktop\\uioCam_v2_1\\etc\\exposure.txt"
    out = open(exposure_out, "w")
    if (exposureIs == "U"):
        print("0", file=out)
    elif (exposureIs == "G"):
        print("1", file=out)
    elif (exposureIs == "O"):
        print("2", file=out)
    else:
        print("Something went wrong with ICE.exe", file=out)
    out.close()
    
    if ratios[0][1] == "G":
        exposureCheck = True
        return exposureCheck
    else:
        exposureCheck = False
        return exposureCheck


def make_paths():
    path = "C:\\Users\\Student\\Desktop\\uioCam_v2_1"
    path_last = path + "\\pictures\\last\\"
    photo_names = os.listdir(path_last)  #  list all files in path_last
    jpg_paths = []
    #  Make list of all paths to .jpg files
    for i in photo_names:
        if (i[-3 : -1] == "JP"):
            jpg_paths.append(path_last + i)

    #  Find the latest .jpg file
    latest_file = max(jpg_paths, key=os.path.getctime)
    latest_file = latest_file[-12 : -4]
    latest_jpg_name = latest_file + ".JPG"
    latest_arw_name = latest_file + ".ARW"

    image_path_jpg = path_last + latest_jpg_name
    image_path_arw = path_last + latest_arw_name
    output_image_path = path + "\\pictures\\RAW\\" + latest_arw_name
    thresholds_path = path + "\\etc\\thresholds.txt"
    return image_path_jpg, image_path_arw, output_image_path, thresholds_path


#  Read thresholds values from thresholds.txt
def read_thresholds(thresholds_path):
    myvars = {}
    with open(thresholds_path) as myfile:
        for line in myfile:
            name, var = line.partition("=")[::2]
            myvars[name.strip()] = int(var)
    thresholds = ((myvars.get("dark_down"), myvars.get("dark_up")),
                  (myvars.get("grey_down"), myvars.get("grey_up")),
                  (myvars.get("bright_down"), myvars.get("bright_up")))
    return thresholds


#  Driver function for the check
def driver_JPG():
    image_path_jpg, image_path_arw, output_image_path, thresholds_path = make_paths()
    thresholds = read_thresholds(thresholds_path)
    image = cv.imread(image_path_jpg)
    
    cropped_image, masked_count = crop_image(image)  
    exposureCheck = check_histogram(cropped_image, masked_count, thresholds)
    
    if exposureCheck:
        print("RAW file moved to ", output_image_path)
        os.rename(image_path_arw, output_image_path)  #  move the good raw to \RAW
        os.remove(image_path_jpg)  # remove the tmp picture from \last
    else:
        os.remove(image_path_jpg)  # remove the tmp picture from \last
        os.remove(image_path_arw)  # remove the unusable raw picture from \last


#  Run the check
driver_JPG()