#pragma once

#include "sonyCamera.h" // For the Sony camera

// Data directories, these must exist
#define CAM_DATADIR "C:\\Users\\sklep\\Desktop\\Norwegia\\Project_II\\uioCam_v2.1\\data"

#define CAM_CONFIG_FILE "C:\\Users\\sklep\\Desktop\\Norwegia\\Project_II\\uioCam_v2.1\\etc\\config.txt"
#define CAM_TIME_FILE "C:\\Users\\sklep\\Desktop\\Norwegia\\Project_II\\uioCam_v2.1\\etc\\time.txt"
#define CAM_README_FILE "C:\\Users\\sklep\\Desktop\\Norwegia\\Project_II\\uioCam_v2.1\\ReadMe.txt"

#define CONFIG_WINDOW_NAME "config.txt - Notisblokk"
#define TIME_WINDOW_NAME "time.txt - Notisblokk"
#define README_WINDOW_NAME "ReadMe.txt - Notisblokk"
#define EXPOSURE_WINDOW_NAME "exposure.txt - Notisblokk"

#define CAM_LOGDIR "C:\\Users\\sklep\\Desktop\\Norwegia\\Project_II\\uioCam_v2.1\\log"
#define CAM_INFO_PATH  "C:\\Users\\sklep\\Desktop\\Norwegia\\Project_II\\uioCam_v2.1\\info"

#define SUNMOON_FILE "C:\\Users\\sklep\\Desktop\\Norwegia\\Project_II\\uioCam_v2.1\\etc\\sunmoon.txt"

// Max length of camera name
#define CAM_NAME_LEN 32

// Software version, updated ny programmer
//-- okay, so what to do with this one..
//-- used in file.cpp
#define CAM_VERSION 1.86

// Number of filters in filter wheel
#define FILTER_MAX 5

// For func.cpp
#define IMAGEPATHLAST "C:\\Users\\sklep\\Desktop\\Norwegia\\Project_II\\uioCam_v2.1\\pictures\\last" // path to where Remote will save the photos
#define IMAGEPATHRAW "C:\\Users\\sklep\\Desktop\\Norwegia\\Project_II\\uioCam_v2.1\\pictures\\RAW" // path to where ICE will save correct pictures
// uioCam will automtically find names of the latest .jpg and .arw files in folder defined under IMAGEPATH
#define LOGPATH "C:\\Users\\sklep\\Desktop\\Norwegia\\Project_II\\uioCam_v2.1\\tmp\\camlog.txt"
#define LOGNAME "camlog.tmp"

// Define paths to external .exe files running python scripts ICE (Intensity control) and PINE (Post-processing)
#define ICE_EXE_NAME "C:\\Users\\sklep\\Desktop\\Norwegia\\Project_II\\uioCam_v2.1\\ICE_RICHARD\\ICE_RICHARD.exe"

// Path to exposure file created by ICE.exe, it does not matter if it exists or not
#define CAM_EXPOSURE_FILE "C:\\Users\\sklep\\Desktop\\Norwegia\\Project_II\\uioCam_v2.1\\etc\\exposure.txt"