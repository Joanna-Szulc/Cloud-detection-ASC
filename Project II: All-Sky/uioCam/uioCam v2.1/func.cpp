/* --------------------------------------------------- */
/*                                                     */
/*             F U N C . C P P                         */
/*                                                     */
/*     Test functions for the visualCppTest program    */
/* --------------------------------------------------- */

#include "stdafx.h"
#include "MyForm.h"
#include <String.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wchar.h>
#include <io.h>   // For access().
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#include <errno.h>
#include "include.h"
#include "global.h"
#include <fstream>

// debug
#include <iostream>
using namespace std;

//############################################################################
// InitiateUioCam()
// This function intiates the variables used in the uioCam program
// This function is the first to be run when the program starts.

int InitiateUioCam(MY_FORM_ARG_VAR)
{
	int retval;
	int i;

	retval = 0;

	if (cam) { // Already malloced before
		free(cam);
	}
	cam = (CAMSTAT *)malloc(sizeof(CAMSTAT)); //I can choose one runtime error or the other... but I can't get rid of it
	//CAMSTAT* cam = new CAMSTAT;

	cam->type.andor_ixon = false;
	cam->type.princeton_pixis = false;
	cam->type.photometrics = false;
	cam->type.sony = false;

	cam->astro.sun_elevation = (float)(-999.999);
	cam->astro.sun_azimuth = (float)(-999.999);
	cam->astro.moon_elevation = (float)(-999.999);
	cam->astro.moon_azimuth = (float)(-999.999);
	cam->astro.moon_phase = (float)(-999.999); 

	strcpy_s(cam->info.library, 64, "Unknown Library");
	strcpy_s(cam->info.comment, 64, " ");
	strcpy_s(cam->info.station_short, 64, "Unknown Station");
	strcpy_s(cam->info.station_long, 64, "Unknown Station");
	strcpy_s(cam->info.code, 32, "XXX");
	cam->info.latitude = (float)(-999.999);
	cam->info.longitude = (float)(-999.999);
	cam->info.altitude = (float)(-999.999);
	strcpy_s(cam->info.cameraname, 64, "Unknown Camera name");
	cam->info.cameranumber = 0;
	cam->info.sizeXY = 1;
	cam->info.filtermax = 1;
	for (i = 0; i < FILTER_MAX; i++) {
		cam->info.wavelen[i] = (float)0.0;
		strcpy_s(cam->info.filtername[i], 32, "Unknown");
	}
	cam->info.radius = -1;
	cam->info.r_center = -1;
	cam->info.c_center = -1;
	cam->info.lens_fov = -1.0;
	cam->info.flip_ud = -1;
	cam->info.cam_roll = 999.0;
	cam->info.cam_pitch = 999.0;
	cam->info.cam_yaw = 999.0;
	cam->info.mag_bearing = 999.0;

	strcpy_s(cam->info.projection, 64, " ");  // Only one character
	strcpy_s(cam->info.calib_filename, 64, " ");  // Only one character

	cam->sys.manual = false; // Default is automatic mode
	cam->sys.write_log = true; // Default is to write to a log file
	cam->sys.write_info = true; // Default is to write to a info file
	cam->sys.debug_on = true; // Default is to write a lot of debug messages
	cam->sys.check_smartmotor = false; // Default is not to check return strings from SMARTMOTOR

	cam->sys.sun_elevation_max = 0.0; // Default value for maximum elevation of the SUN
	cam->sys.moon_elevation_max = 0.0; // Default value for maximum elevation of the MOON

	//cam->sys.write_gamma = true; // Default is to write the "gAMA" chunck in the PNG files
	cam->sys.dump_bmp = false; // Default do not write D:\tmp\last.bmp

	cam->sys.home = false; // A HOME is NOT done automatically with the filterwheel at start and midnight
	cam->sys.shutter_stay_open = false; // Close shutter after each image

	cam->sys.smartmotor_port = 1; // COM1: is default for the smartmotor RS-232 interface
	
	cam->sys.run_smartmotor = false; // Default is to send no commands to the smartmotor
	cam->sys.run_camera = false;   // Default is to send no commands to the camera
	cam->sys.run_temp_ctrl = false; // Default is not to read data from the temperature controller

	//cam->crc.crc_table_computed = false;

	cam->curr.buttons_enabled = true; // Default buttons are enabled at start
	cam->curr.manual = false; // Default is automatic mode
	cam->curr.end = false; // End button has not been pressed
	cam->curr.log_fptr = NULL;
	cam->curr.logIsOpen = false;
	cam->curr.info_fptr = NULL;
	cam->curr.infoIsOpen = false;

	cam->curr.cameraIsStarted = false;

	cam->curr.smartmotorIsOpen = false;

	cam->curr.minTimerEnabled = false;
	cam->curr.first_min = true;

	cam->curr.shutterIsOpen = false;
	cam->curr.currentFilter = -1;

	strcpy_s(cam->curr.imagepath, 128, IMAGEPATHLAST); // was 64

	cam->curr.sizeX = 1024;
	cam->curr.sizeY = 1024;

	strcpy_s(cam->curr.logpath, 128, LOGPATH); // was 64
	strcpy_s(cam->curr.logname, 128, LOGNAME); // was 64

	cam->noTime = 0;
	cam->startTime = NULL;
	cam->endTime = NULL;

	cam->run_mode = 0;
	cam->first_mode_set = 0;
	cam->intensity_control = 0;
	cam->post_process = 0;

	cam->manual = 0;

	cam->modes.normal_interval = 0;
	cam->modes.normal_filter = 0;
	cam->modes.cloud_interval = 0;
	cam->modes.cloud_filter = 0;
	/*cam->modes.pol_interval = 0;
	cam->modes.pol_filter = 0;
	cam->modes.pol_max_intensity = 0;
	cam->modes.pol_min_intensity = 0;
	cam->modes.night_interval = 0;
	cam->modes.night_filter = 0;
	cam->modes.night_max_intensity = 0;
	cam->modes.night_min_intensity = 0;
	cam->modes.night_sun_elev_max = 0.0;
	cam->modes.night_moon_elev_max = 0.0;*/

	cam->intensity.exposureOk = false;
	cam->intensity.exposure = 0;

	cam->min_ok = false;
	cam->sec_ok = false;
	cam->start_sec = 0;
	cam->start_min = 0;
	cam->interval = 5;
	cam->filter = 0;
	cam->sec_since_img = 0;

	cam->run_ok = false;
	cam->timeseq_ok = false;
	cam->sunmoon_ok = false;

	//////////////// Initialize REMOTESTAT /////////////////
	cam->remote.ISO = 0;
	cam->remote.shutter_speed = 0;
	cam->remote.MANUAL = false;

	return retval;
}

//############################################################################
// ReadEtcFilesUioCam()
// This function the read the setup files used in the uioCam program
// This function is the second to be run when the program starts.

int ReadEtcFilesUioCam(MY_FORM_ARG_VAR, System::Windows::Forms::Label^ topText)
{
	CAMTIME camtime;
	int retval;
	char qwa[1024];
	char smt_txt[64];
	char cam_txt[64];
	int result;

	retval = 0;

	//////////////////////////////////////////////////////
	// READ THE SETUP FILES ::::::::::::::::::::::::::::::::::::::::
	ReadCamSetupFile(outTextBox);                // read and interpret config.txt

	if (cam->sys.write_log)
	{
		GetYearMonthDayHourMinSec(&camtime.year, &camtime.month, &camtime.day,
			&camtime.hour, &camtime.min, &camtime.sec);
		result = CamOpenNewLogFile(MY_FORM_ARG_FUNC, camtime);
	}

	ReadCamTimeFile(outTextBox);  // read and interpret CAM_TIME_FILE

	//////////////////////////////////////////////////////
	// Write messages in the graphic window

	strcpy_s(qwa, 256, "Software is properly started");
	WriteMessage(outTextBox, qwa);

	if (cam->sys.run_smartmotor) {
		sprintf_s(cam_txt, 64, "SMARTMOTOR ON");
	}
	else {
		sprintf_s(cam_txt, 64, "smartmotor off");
	}

	if (cam->sys.run_camera) {
		sprintf_s(smt_txt, 64, "CAMERA ON");
	}
	else {
		sprintf_s(smt_txt, 64, "camera off");
	}

	sprintf_s(qwa, 1024, "%s, %s, program is waiting on next minute to start", cam_txt, smt_txt);

	WriteTopText(topText, qwa);

	return(retval);
}


//################################################################################
// ReadCamSetupFile()
// This function reads and interprets the camera setup file: config.txt 
// The function is called from the end of the InitiateUioCam() function
//

int ReadCamSetupFile(System::Windows::Forms::TextBox^ myTextBox)
{
	// This function opens, reads and interpret the 
	// ..\etc\config.txt
	// (The keys in the file must be exact or they will not be interpreted.)

	FILE *infptr;
	char cLine[1024];
	char qwa[1024];
	char qwb[1024];
	char fipath[256];
	errno_t myErrno;
	bool ok1;
	bool ok2;
	int pos;
	int d;

	strcpy_s(fipath, 128, CAM_CONFIG_FILE);  // CAMERA SETUP FILE, see define.h for definition of name
	ok1 = true;
	ok2 = true;

	myErrno = fopen_s(&infptr, fipath, "r");
	if (myErrno != 0)
	{
		sprintf_s(qwa, 256, "ERROR: Can't open %s file.", fipath);
		WriteMessage(myTextBox, qwa);
		return(-1);
	}

	while (fgets(cLine, 1024, infptr) != NULL)
	{
		ok1 = true;
		if (cLine[0] == '#') ok1 = false; // comment line
		if ((int)strlen(cLine) < 3) ok1 = false; // not a valid line 
		if (!ok1)
		{
			continue;
		}

		pos = 0;
		strcpy_s(qwa, 256, (char *)FirstWord(cLine));

		if (!strcmp(qwa, "WRITE_LOG:"))
		{
			d = atoi(WordAfterN(qwa, cLine, &pos));
			if (d == 1) {
				cam->sys.write_log = true;
			}
			else {
				cam->sys.write_log = false;
			}

		}
		else if (!strcmp(qwa, "WRITE_INFO:"))
		{
			d = atoi(WordAfterN(qwa, cLine, &pos));
			if (d == 1) {
				cam->sys.write_info = true;
			}
			else {
				cam->sys.write_info = false;
			}

		}
		else if (!strcmp(qwa, "DEBUG_ON:"))
		{
			d = atoi(WordAfterN(qwa, cLine, &pos));
			if (d == 1) {
				cam->sys.debug_on = true;
			}
			else {
				cam->sys.debug_on = false;
			}

		}
		else if (!strcmp(qwa, "CHECK_SMARTMOTOR:"))
		{
			d = atoi(WordAfterN(qwa, cLine, &pos));
			if (d == 1) {
				cam->sys.check_smartmotor = true;
			}
			else {
				cam->sys.check_smartmotor = false;
			}
		}
		else if (!strcmp(qwa, "LIBRARY:"))
		{
			strcpy_s(cam->info.library, 64, LineAfterN(qwa, cLine, &pos)); // 64 is the length of the text variable
		}
		else if (!strcmp(qwa, "COMMENT:"))
		{
			strcpy_s(cam->info.comment, 256, LineAfterN(qwa, cLine, &pos)); // 256 is the length of the text variable
		}
		else if (!strcmp(qwa, "STATION_SHORT:"))
		{
			strcpy_s(cam->info.station_short, 64, LineAfterN(qwa, cLine, &pos)); // 64 is the length of the text variable
		}
		else if (!strcmp(qwa, "STATION_LONG:"))
		{
			strcpy_s(cam->info.station_long, 256, LineAfterN(qwa, cLine, &pos)); // 256 is the length of the text variable
		}
		else if (!strcmp(qwa, "CODE:"))
		{
			strcpy_s(cam->info.code, 32, LineAfterN(qwa, cLine, &pos)); // 32 is the length of the text variable
		}
		else if (!strcmp(qwa, "LAT:"))
		{
			cam->info.latitude = (float)atof(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "LONG:"))
		{
			cam->info.longitude = (float)atof(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "ALT:"))
		{
			cam->info.altitude = (float)atof(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "CAMERANAME:"))
		{
			strcpy_s(cam->info.cameraname, 64, LineAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "CAMERANUMBER:"))
		{
			cam->info.cameranumber = atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "SIZEXY:"))
		{
			cam->info.sizeXY = atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "FILTERNO:"))
		{
			cam->info.filtermax = atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "FILTER1:"))
		{
			strcpy_s(cam->info.filtername[0], 32, LineAfterN(qwa, cLine, &pos)); // MARK: 32 is the length of the text
		}                                                                    // do not exceed that
		else if (!strcmp(qwa, "FILTER2:"))                                    // or you get memory problems
		{
			strcpy_s(cam->info.filtername[1], 32, LineAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "FILTER3:"))
		{
			strcpy_s(cam->info.filtername[2], 32, LineAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "FILTER4:"))
		{
			strcpy_s(cam->info.filtername[3], 32, LineAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "FILTER5:"))
		{
			strcpy_s(cam->info.filtername[4], 32, LineAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "WAVELEN1:"))
		{
			cam->info.wavelen[0] = (float)atof(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "WAVELEN2:"))
		{
			cam->info.wavelen[1] = (float)atof(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "WAVELEN3:"))
		{
			cam->info.wavelen[2] = (float)atof(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "WAVELEN4:"))
		{
			cam->info.wavelen[3] = (float)atof(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "WAVELEN5:"))
		{
			cam->info.wavelen[4] = (float)atof(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "RADIUS:"))
		{
			cam->info.radius = atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "R_CENTER:"))
		{
			cam->info.r_center = atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "C_CENTER:"))
		{
			cam->info.c_center = atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "LENS_FOV:"))
		{
			cam->info.lens_fov = (float)atof(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "FLIP_UD:"))
		{
			cam->info.flip_ud = atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "CAM_ROLL:"))
		{
			cam->info.cam_roll = (float)atof(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "CAM_PITCH:"))
		{
			cam->info.cam_pitch = (float)atof(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "CAM_YAW:"))
		{
			cam->info.cam_yaw = (float)atof(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "MAG_BEARING:"))
		{
			cam->info.mag_bearing = (float)atof(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "PROJECTION:"))
		{
			strcpy_s(cam->info.projection, 256, LineAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "CALIB_FILENAME:"))
		{
			strcpy_s(cam->info.calib_filename, 256, LineAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "HOME:"))
		{
			d = atoi(WordAfterN(qwa, cLine, &pos));
			if (d == 1) {
				cam->sys.home = true;
			}
			else {
				cam->sys.home = false;
			}
		}
		else if (!strcmp(qwa, "SHUTTER_STAY_OPEN:"))
		{
			d = atoi(WordAfterN(qwa, cLine, &pos));
			if (d == 1) {
				cam->sys.shutter_stay_open = true;
			}
			else {
				cam->sys.shutter_stay_open = false;
			}
		}
		else if (!strcmp(qwa, "DUMP_BMP:"))
		{
			d = atoi(WordAfterN(qwa, cLine, &pos));
			if (d == 1) {
				cam->sys.dump_bmp = true;
			}
			else {
				cam->sys.dump_bmp = false;
			}
		}
		else if (!strcmp(qwa, "SMARTMOTOR_PORT:"))
		{
			cam->sys.smartmotor_port = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "RUN_SMARTMOTOR:"))
		{
			d = atoi(WordAfterN(qwa, cLine, &pos));
			if (d == 1) {
				cam->sys.run_smartmotor = true;
			}
			else {
				cam->sys.run_smartmotor = false;
			}
		}
		else if (!strcmp(qwa, "RUN_CAMERA:"))
		{
			d = atoi(WordAfterN(qwa, cLine, &pos));
			if (d == 1) {
				cam->sys.run_camera = true;
			}
			else {
				cam->sys.run_camera = false;
			}
		}
		else if (!strcmp(qwa, "RUN_TEMP_CTRL:"))
		{
			d = atoi(WordAfterN(qwa, cLine, &pos));
			if (d == 1) {
				cam->sys.run_temp_ctrl = true;
			}
			else {
				cam->sys.run_temp_ctrl = false;
			}
		}
		else if (!strcmp(qwa, "START_SEC:"))
		{
			cam->start_sec = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "START_MIN:"))
		{
			cam->start_min = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "RUN_MODE:"))
		{
			cam->run_mode = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "INTERVAL:"))
		{
			cam->interval = atoi(WordAfterN(qwa, cLine, &pos));
			cam->modes.normal_interval = cam->interval;
		}
		else if (!strcmp(qwa, "FILTER:"))
		{
			cam->filter = atoi(WordAfterN(qwa, cLine, &pos));
			cam->modes.normal_filter = cam->filter;
		}
		else if (!strcmp(qwa, "INTENSITY_CONTROL:"))
		{
			cam->modes.normal_intensity_control = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "POST_PROCESS:"))
		{
		cam->modes.normal_post_process = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "CLOUD_INTERVAL:"))
		{
			cam->modes.cloud_interval = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "CLOUD_FILTER:"))
		{
			cam->modes.cloud_filter = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "CLOUD_INTENSITY_CONTROL:"))
		{
			cam->modes.cloud_intensity_control = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "CLOUD_POST_PROCESS:"))
		{
		cam->modes.cloud_post_process = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		/*else if (!strcmp(qwa, "POL_INTERVAL:"))
		{
			cam->modes.pol_interval = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "POL_FILTER:"))
		{
			cam->modes.pol_filter = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "POL_MAX_INTENSITY:"))
		{
			cam->modes.pol_max_intensity = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "POL_MIN_INTENSITY:"))
		{
			cam->modes.pol_min_intensity = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "POL_INTENSITY_CONTROL:"))
		{
			cam->modes.pol_intensity_control = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}*/
		/*else if (!strcmp(qwa, "NIGHT_INTERVAL:"))
		{
			cam->modes.night_interval = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "NIGHT_FILTER:"))
		{
			cam->modes.night_filter = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "NIGHT_MAX_INTENSITY:"))
		{
			cam->modes.night_max_intensity = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "NIGHT_MIN_INTENSITY:"))
		{
			cam->modes.night_min_intensity = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "NIGHT_INTENSITY_CONTROL:"))
		{
			cam->modes.night_intensity_control = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "NIGHT_SUN_ELEVATION_MAX:"))
		{
			cam->modes.night_sun_elev_max = (float)atof(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "NIGHT_MOON_ELEVATION_MAX:"))
		{
			cam->modes.night_moon_elev_max = (float)atof(WordAfterN(qwa, cLine, &pos));
		}*/
		else if (!strcmp(qwa, "MANUAL:"))
		{
			cam->manual = (int)atoi(WordAfterN(qwa, cLine, &pos));
		}
		else
		{
			strcpy_s(qwb, 256, qwa);
			sprintf_s(qwa, 256, "ERROR: Can't decode '%s' from %s", qwb, CAM_CONFIG_FILE);
			WriteMessage(myTextBox, qwa);
			ok2 = false;
		}
	}

	if (ok2)
	{
		sprintf_s(qwa, 256, "The file %s was successfully decoded.", fipath);
		WriteMessage(myTextBox, qwa);
	}

	fclose(infptr);

	return(0);
}



// ############################################################
// WriteMessage()
// Add a new text (mytext) to the top of the Message Text Area
// It add a hh:mm:ss to the start of the message
// It adds a \r\n to the previous text
// As an option the text is also written to the log file

void WriteMessage(System::Windows::Forms::TextBox^ locTextBox, char *mytext)
{
	locTextBox->Text = GetTimeString() + gcnew System::String(mytext) + "\r\n" + locTextBox->Text;

	if (cam->sys.write_log && cam->curr.logIsOpen)  // Write to log file
	{
		fprintf(cam->curr.log_fptr, "%s %s\r\n", GetTimeString(), mytext);
	}
}


// ############################################################
// WriteTopText()
// Write mytext to the top label
// As an option the text is also written to the log file

void WriteTopText(System::Windows::Forms::Label^ locLabel, char *mytext)
{
	locLabel->Text = gcnew System::String(mytext);

	if (cam->sys.write_log && cam->curr.logIsOpen)  // Write to log file
	{
		fprintf(cam->curr.log_fptr, "%s\r\n", mytext);
	}
}



// ##############################################################
// GetTimeString
// This function returns with the time string "hh:mm:ss"

System::String^ GetTimeString()
{
	System::String^ retString;
	struct tm newtime;
	time_t ltime;
	errno_t errt;
	char qwa[1024];

	time(&ltime);
	errt = gmtime_s(&newtime, &ltime);

	sprintf_s(qwa, 64, "%02d:%02d:%02d ",
		newtime.tm_hour,
		newtime.tm_min,
		newtime.tm_sec);

	retString = gcnew System::String(qwa);

	return(retString);
}

// ################################################################
// GetHourMinSec()
// This function returns with hour, min, second UT
//
void GetHourMinSec(int *h, int *m, int *s)
{
	struct tm newtime;
	time_t ltime;
	errno_t errt;

	time(&ltime);
	errt = gmtime_s(&newtime, &ltime);

	*h = newtime.tm_hour;
	*m = newtime.tm_min;
	*s = newtime.tm_sec;
}

// ##################################################################
// GetYearMonthSayHourMinSec()
// This function returns with year, month, day hour, min, second UT
//
void GetYearMonthDayHourMinSec(int *year, int *month, int *day, int *h, int *m, int *s)
{
	struct tm newtime;
	time_t ltime;
	errno_t errt;

	time(&ltime);
	errt = gmtime_s(&newtime, &ltime);

	*year = newtime.tm_year + 1900; // current year minus 1900
	*month = newtime.tm_mon + 1; //  January = 0
	*day = newtime.tm_mday;
	*h = newtime.tm_hour;
	*m = newtime.tm_min;
	*s = newtime.tm_sec;
}

// ########################################################################
// GetDateString()
// This function returns with the time string "yyyy:mm:dd hh:mm:ss UT"

System::String^ GetDateString()
{
	System::String^ retString;
	struct tm newtime;
	time_t ltime;
	errno_t errt;
	char qwa[1024];

	time(&ltime);
	errt = gmtime_s(&newtime, &ltime);

	sprintf_s(qwa, 64, "%04d-%02d-%02d %02d:%02d:%02d UT",
		newtime.tm_year + 1900, // current year minus 1900
		newtime.tm_mon + 1, //  January = 0
		newtime.tm_mday,
		newtime.tm_hour,
		newtime.tm_min,
		newtime.tm_sec);

	retString = gcnew System::String(qwa);

	return(retString);
}

// #################################################################
// GetAstroString()
// This function returns with the string "SUN lat long MOOON lat long phase"
// As an option it writes the string to the log file

System::String^ GetAstroString()
{
	System::String^ retString;
	struct tm newtime;
	time_t ltime;
	errno_t errt;
	char qwa[1024];
	char qwb[256];
	char qwc[64];
	bool already_got_time;
	int result;

	already_got_time = false;

	strcpy_s(qwb, 64, "O");
	qwb[0] = (unsigned char)176;
	strcpy_s(qwc, 64, "O");
	qwc[0] = (unsigned char)37;

	sprintf_s(qwa, 256,
		"SUN elevation %.2f %s azimuth %.2f %s MOON elevation %.2f %s azimuth %.2f %s phase %.2f %s",
		cam->astro.sun_elevation, qwb,
		cam->astro.sun_azimuth, qwb,
		cam->astro.moon_elevation, qwb, 
		cam->astro.moon_azimuth, qwb, 
		cam->astro.moon_phase, qwb);

	// Write to file, for sun- and moonblock in other applications
	ofstream myfile;
	myfile.open(SUNMOON_FILE);
	myfile << qwa;
	myfile.close();

	retString = gcnew System::String(qwa);

	if (cam->sys.write_log && cam->curr.logIsOpen)  // Write to log file
	{
		time(&ltime);
		errt = gmtime_s(&newtime, &ltime);
		already_got_time = true;

		fprintf(cam->curr.log_fptr, "%04d-%02d-%02d %02d:%02d:%02d %s\r\n",
			newtime.tm_year + 1900, // current year minus 1900
			newtime.tm_mon + 1, //  January = 0
			newtime.tm_mday,
			newtime.tm_hour,
			newtime.tm_min,
			newtime.tm_sec,
			qwa);
	}

	// Then write to INFO file, in order for other programs to read it we have to open and close it every time

	if (cam->sys.write_info)
	{
		result = CamOpenInfoFile(); // OPEN INFO FILE EVERY TIME
	}

	if (cam->sys.write_info && cam->curr.infoIsOpen)  // Write to info file
	{
		if (!already_got_time) {
			time(&ltime);
			errt = gmtime_s(&newtime, &ltime);
		}

		fprintf(cam->curr.info_fptr,
			"<table border=\"1\" align=\"center\"> <tr><td> %04d-%02d-%02d %02d:%02d UT <td> Elevation <b> &deg; </b> <td> Azimuth <b> &deg; </b> <td> Phase %s </td>\r\n",
			newtime.tm_year + 1900, // current year minus 1900
			newtime.tm_mon + 1, //  January = 0
			newtime.tm_mday,
			newtime.tm_hour,
			newtime.tm_min,
			qwc);

		fprintf(cam->curr.info_fptr,
			"<tr><td> <b> Sun </b> <td> <b> %.2f </b> <td> %.2f <td> &nbsp; </td> <tr><td> <b> Moon </b> <td> <b> %.2f </b> <td> %.2f <td> %.2f </td> </tr>\r\n",
			cam->astro.sun_elevation,
			cam->astro.sun_azimuth,
			cam->astro.moon_elevation,
			cam->astro.moon_azimuth,
			cam->astro.moon_phase);

		fclose(cam->curr.info_fptr); // CLOSE INFO FILE EVERY TIME
		cam->curr.infoIsOpen = false;
	}

	return(retString);
}



// ######################################################################
// CheckTime(a,b)
//
// CheckTime returns  1 when a > b
// CheckTime returns  0 when a = b
// CheckTime returns -1 when a < b
//
int CheckTime(CAMTIME a, CAMTIME b)
{
	int retVal;
	int first;
	int last;
	int i;

	retVal = 0; // assumes both times are equal

	for (i = 0; i < 6; i++)
	{
		if (retVal != 0) continue;

		switch (i)
		{
		case 0: first = a.year;  last = b.year;  break;
		case 1: first = a.month; last = b.month; break;
		case 2: first = a.day;   last = b.day;   break;
		case 3: first = a.hour;  last = b.hour;  break;
		case 4: first = a.min;   last = b.min;   break;
		case 5: first = a.sec;   last = b.sec;   break;
		}

		if (first > last)
		{
			retVal = 1;
		}
		else if (first < last)
		{
			retVal = -1;
		}
	}

	return(retVal);
}

// ##############################################################
// CamDirExist(path)
// This function returns true if the directory (path) exists,
// else it returns false.

bool CamDirExist(char *path)
{
	bool retVal;

	if (_access(path, 0) == 0)
	{
		struct stat status;
		stat(path, &status);
		if (status.st_mode & S_IFDIR)
		{
			retVal = true; // "The directory exists." 
		}
		else
		{
			retVal = false; // "The path you entered is a file."
		}
	}
	else
	{
		retVal = false; // "Path doesn't exist." <
	}

	return(retVal);
}

// ############################################################# 
