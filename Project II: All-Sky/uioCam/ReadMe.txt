========================================================================
                  README for APPLICATION : uioCam v2.0 
========================================================================
Last upadated: 2020-07-31
Author: Joanna Szulc (joanna.szulc.pl at gmail dot com)
Previously updated: 2018-07-21
Author: Marie Henriksen (marieboehenriksen at gmail dot com)

=======================================================================
	       	   FOR uioCam v2.1 scroll down
=======================================================================

GENERAL INFORMATION
------------------------------------

The uioCam application was originally made for the University of Oslo (UiO).
In 2018 both the application and the belonging system were modified from 
night time operation looking at the aurora to daytime operation looking at 
clouds. This modification was done for Andøya Space Center (ASC).

This ReadMe file is further divided into two parts: one for the USER and one
for the DEVELOPER. 


USER
------------------------------------

The application is started by running the file "uioCam_v2.0.exe" which can
be found in the folder "Debug" in the folder "uioCam_v2.0", 
(path: \uioCam_v2.0\Debug\uioCam_v2.0.exe) or from a shortcut on the desktop
if the system is already set up.

The program consists of different parts: 

    - The SMARTMOTOR part is used to control the motor behind the filter
      wheel. "Open" connects the motor and makes it ready for commands, 
      "Home" initializes the filter wheel and positions it at filter 1. 
      "Full turn" makes the filter wheel turn 360 degrees, while doing a
      short stop at each filter position. "Close" closes the connection to 
      the motor. "Shutter" opens and closes the shutter, "Filter" decides
      what filter position to go to.
    - The CAMERA part is used to control the camera. "Open Remote" opens the
      program "Remote", which is a part of Sony's Imaging Edge. This 
      software must be downloaded to the computer. "Get image" will make the
      camera take an image. The desired destination folder can be set in 
      Remote. Other adjustments such as increasing shutter speed, ISO etc.
      can also be controlled from Remote. "Close Remote" closes Remote again.
    - "Modes" are used to enter predefined modes for the system. Parameters
      such as filter, interval, and max and min intensity for each mode can 
      be set in the configuration file: config.txt.
    - "Edit config.txt" and the other edit buttons will open the respective
      text file in a text editor. If this doesn't work, make sure the
      correct paths and names are defined in define.h. 
    - "Manual" decides whether the program should run in auto, and run its
      predefined sequence defined in sequence.txt, or if the user controls
      the program manually. 
    - "Debug" decides whether debug comments are wanted or not.
    - "Log" decides whether to write to log file or not.
    - "Info" decides whether to use the info file or not.
    - "Intensity control" decides whether or not to use uioCam's own
      intensity control for the images. When running, it is adviced to 
      either have intensity control on, or the camera itself in auto mode.
      The camera must be in manual mode (M) if intensity control is to work.
    - "Read config" re-reads the textfiles and updates the system parameters.
    - "End" exits uioCam v2.0 safely

The desired behavior of the program should be specified in the different 
textfiles. Before a new experiment, make sure that the values set in 
config.txt are updated. Make sure the time interval in time.txt is correct. 
If the time is outside the time slot specified in time.txt, the program will
stop running. A specified start minute and start second can be set in 
config.txt. A specific start and end date can be set in time.txt.

NOTE:
No interaction with the actual data is made from uioCam v2.0. Where the 
images are saved and what format/quality can be set in Sony's Remote. Any 
back-up and deletion of data is not handled by uioCam v2.0, and should be 
handled by an external program. Any data processing software to be used is
not integrated with uioCam v2.0, but must detect new images itself.
 

DEVELOPER
------------------------------------

This application was created in Microsoft Visual Studio Community 2017 on 
Windows 10. The project is a based on a CLR empty project and Windows Forms.

A full list of the files that should be included can be found at the end of 
this document. The zlib files are used for compression to .png file, which 
was a feature in the original uioCam. These files can be removed, but then
the code using them must be found and removed as well. The yAstro files are
used in the process of calculating the position (az and el) of the sun and
the moon. It is possible that many of these files could be excluded as well,
but then the correct code must also be removed. Without changing/removing
any code, all files must be included to the project for it to run.

The files mostly used and edited are listed below, with a short explanation
of each file:

    define.h ---------- Defines paths and filenames
    include.h --------- All global structures used, function definitions
			acts as header file for most of the .cpp files
    MyForm.h ---------- Sets up the form (GUI). Initialization happens in
			MyForm_Load(). Most of the action happens in 
			secTimer_Tick(), and some in minTimer_Tick(). All
			other functionality to do with the buttons etc. is
			also specified in this file.

    func.cpp ---------- Initialization of all global variables happens in
			InitiateUioCam(). The function reading params from
			the config textfile is also located here.
    modes.cpp --------- Handles initialization of the different modes.
    sequence.cpp ------ Reads time.txt, checks sun/moon conditions.
    smartMotorIo.cpp -- All functionality to do with the smartmotor.
    sonyCameraIo.cpp -- Communication with the camera (via Remote).
    uioCam_v2.0.cpp --- The main file of the project.

More information about the new funcionality in uioCam v2.0 can be found
in the work document by the summer interns at ASC 2018.



========================================================================
                  README for APPLICATION : uioCam v2.1 
========================================================================
Last upadated: 2020-07-31
Author: Joanna Szulc (joanna.szulc.pl at gmail dot com)

=======================================================================
	       	   FOR uioCam v2.0 scroll up
=======================================================================

GENERAL INFORMATION
------------------------------------

The uioCam application was updated and modified into uioCam v 2.1 in
2020. While the main body of the program remained basically untouched
new functionalities were added.

This instruction in seperated into USER and DEVELOPER parts. Further
information on the All-Sky system can be found in "All-Sky Manual 2020"
including the set-up of the whole system from mounting to conducting
measurements.

USER
------------------------------------
UioCam v2.1 includes couple of new functionalities:

	Last image info - provides information on ISO, shutter speed
and exposure program of the latest photo found in the specified folder.
By default that should be /last when the intensity control is off, or
/RAW if the intensity control is on.

	Intensity control - uioCam v2.0 did not have functioning intensity
control. In v2.1 the intensity control is handled by external .exe file.
Everytime time that intensity control is switched on the uioCam will
make a single photo and update its internal settings to be in sync with
Remote application.

KNOWN ISSUE: If the intensity control is switched on when Remote is not
yet open the update will run, but without any effect. That may happen if
intensity control is loaded through config.txt or in automatic mode. To
be on the safe side make sure that the update was done after Remote was
already open.

After that, as long as intensity control is on every time a photo is taken
(both while making a single image through Get image button and in preprogrammed
sequence) uioCam will automatically check the exposure of the photo and 
either accept the photo, or erase it, change the shutter speed and take
another photo until the exposure will be right.

The intensity control sets ISO automatically for day time and night time.

Thresholds for intensity check can be adjusted in \etc\thresholds.txt.

	Post-process - unfortunately this button is mute. In possible
future v2.2 that would be a setting that would switch on automatic
post-processing and cloud detection of the accepted photos.

More information can be found in "All-Sky Manual 2020".

 

DEVELOPER
------------------------------------

This application was created in Microsoft Visual Studio Community 2017 on 
Windows 10. The project is a based on a CLR empty project and Windows Forms.

A full list of the files that should be included can be found at the end of 
this document. The zlib files are used for compression to .png file, which 
was a feature in the original uioCam. These files and all code mentionting
them was removed in uioCam v2.1. The yAstro files are used in the process of 
calculating the position (az and el) of the sun and the moon. It is possible
that many of these files could be excluded as well, but then the correct code
must also be removed. Without changing/removing any code, all files must be 
included to the project for it to run.

New files were added as well in uioCam v2.1.

The files mostly used and edited are listed below, with a short explanation
of each file:

    define.h ---------- Defines paths and filenames
    include.h --------- All global structures used, function definitions
			acts as header file for most of the .cpp files
    MyForm.h ---------- Sets up the form (GUI). Initialization happens in
			MyForm_Load(). Most of the action happens in 
			secTimer_Tick(), and some in minTimer_Tick(). All
			other functionality to do with the buttons etc. is
			also specified in this file.

    func.cpp ---------- Initialization of all global variables happens in
			InitiateUioCam(). The function reading params from
			the config textfile is also located here.
    modes.cpp --------- Handles initialization of the different modes.
    sequence.cpp ------ Reads time.txt, checks sun/moon conditions.
    smartMotorIo.cpp -- All functionality to do with the smartmotor.
    sonyCameraIo.cpp -- Communication with the camera (via Remote).
    photosIo
    uioCam_v2.0.cpp --- The main file of the project.

More information about the new funcionality in uioCam v2.0 can be found
in the work document by the summer interns at ASC 2018.

The complete list of files to be included to the VS project:
(the textfiles config.txt, intensity.txt, sunmoon.txt and time.txt
 must also exist outside the project) 

The complete list of files to be included to the VS project:
(the textfiles config.txt, intensity.txt, sunmoon.txt and time.txt
 must also exist outside the project) 

astroIo.cpp

astroIo.h

define.h

file.cpp

func.cpp

global.cpp

global.h

include.h

Isutil.h

modes.cpp

MyForm.cpp

MyForm.h

MyForm.resx

pngIo.cpp


sequence.cpp

smartMotorIo.cpp

sonyCamera.h

sonyCameraIo.cpp

stdafx.cpp

stdafx.h

strings.cpp

targetver.h

uioCam_v2.0.cpp

uioCam_v2.0.vcxproj

uioCam_v2.0.vcxproj.filters

uioCam_v2.0.vcxproj.user

yAstro_aa_hadec.cpp

yAstro_aberration.cpp

yAstro_actan.cpp

yAstro_anomaly.cpp

yAstro_ap_as.cpp

yAstro_astro.h

yAstro_auxil.cpp

yAstro_bdl.cpp

yAstro_bdl.h

yAstro_chap95.cpp

yAstro_chap95.h

yAstro_chap95_data.cpp

yAstro_circum.cpp

yAstro_comet.cpp

yAstro_deep.cpp

yAstro_deepconst.h

yAstro_deltat.cpp

yAstro_earthsat.cpp

yAstro_eq_ecl.cpp

yAstro_jupmoon.cpp

yAstro_marsmoon.cpp

yAstro_misc.cpp

yAstro_mjd.cpp

yAstro_moon.cpp

yAstro_nutation.cpp

yAstro_obliq.cpp

yAstro_parallactic.cpp

yAstro_parallax.cpp

yAstro_plans.cpp

yAstro_plmoon.cpp

yAstro_plshadow.cpp

yAstro_precess.cpp

yAstro_preferences.h

yAstro_reduce.cpp

yAstro_refract.cpp

yAstro_rings.cpp

yAstro_satlib.h

yAstro_satmoon.cpp

yAstro_satspec.h

yAstro_sattypes.h

yAstro_sdp4.cpp

yAstro_sgp4.cpp

yAstro_sphcart.cpp

yAstro_sun.cpp

yAstro_thetag.cpp

yAstro_twobody.cpp

yAstro_umoon.cpp

yAstro_utc_gst.cpp

yAstro_vector.h

yAstro_vsop87.cpp

yAstro_vsop87.h

yAstro_vsop87_data.cpp

zlib_adler32.cpp

zlib_crc32.cpp

zlib_crc32.h

zlib_deflate.cpp

zlib_deflate.h

zlib_trees.cpp

zlib_trees.h

zlib_zconf.h

zlib_zlib.h

zlib_zpipe.cpp

zlib_zutil.cpp

zlib_zutil.h
