/* --------------------------------------------------- */
/*                                                     */
/*            F I L E . C P P                          */
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
#include <direct.h>
#include <errno.h>
#include "include.h"
#include "global.h"
#include "define.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CreateNewImageName(no,camtime)
//
// camtime is time when exposure start (UT)
//
// The function creates a new image file name 
// The current image path is stored in cam->curr.imagepath  , i.e. the full path
// The current image file name is stored in cam->curr.imagename , i.e. only file name
//
// If the directories does not exist  \YYYY\SSS_YYYYMMDD\uthh\ , this function creates those

bool CamCreateNewImageName(int no, CAMTIME camtime)
{
	bool retVal;
	char path[256];
	char qwa[256];
	char qwb[256];
	int filter;

	retVal = true;

	sprintf_s(path, 256, "%s", CAM_DATADIR);

	sprintf_s(qwa, 256, "\\%04d", camtime.year);
	strcat_s(path, 256, qwa);
	if (!CamDirExist(path))
	{
		_mkdir(path);
	}

	sprintf_s(qwa, 256, "\\%s_%04d%02d%02d", cam->info.code, camtime.year, camtime.month, camtime.day);
	strcat_s(path, 256, qwa);
	if (!CamDirExist(path))
	{
		_mkdir(path);
	}

	sprintf_s(qwa, 256, "\\ut%02d", camtime.hour);
	strcat_s(path, 256, qwa);
	if (!CamDirExist(path))
	{
		_mkdir(path);
	}

	// 2010-07-22_122231_6300_NYA.img

	strcpy_s(qwb, 256, "1234");
	filter = cam->filter;
	if (filter < 1) filter = 1;
	else if (filter > 5) filter = 5;

	qwb[0] = cam->info.filtername[filter - 1][0]; // '630.0' => '6300'
	qwb[1] = cam->info.filtername[filter - 1][1];
	qwb[2] = cam->info.filtername[filter - 1][2];
	qwb[3] = cam->info.filtername[filter - 1][4];

	sprintf_s(qwa, 256, "%s%d_%04d%02d%02d_%02d%02d%02d_%s.png",
		cam->info.code,
		cam->info.cameranumber,
		camtime.year,
		camtime.month,
		camtime.day,
		camtime.hour,
		camtime.min,
		camtime.sec,
		qwb);

	strcat_s(path, 256, "\\");
	strcat_s(path, 256, qwa);

	strcpy_s(cam->curr.imagepath, path); // Current image path
	strcpy_s(cam->curr.imagename, qwa);  // Current image name

	return(retVal);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CreateNewLogName(camtime)
//
// camtime is the current UT time
//
// The function creates a new log file name 
// The current log path is stored in cam->curr.logpath  , i.e. the full path
// The current log file name is stored in cam->curr.logname , i.e. only file name
//
// If the directories does not exist  \YYYY\MM\DD\ , this function creates those



bool CamCreateNewLogName(CAMTIME camtime)
{
	bool retVal;
	char path[256];
	char qwa[256];

	retVal = true;

	sprintf_s(path, 256, "%s", CAM_LOGDIR);

	sprintf_s(qwa, 256, "\\%04d", camtime.year);
	strcat_s(path, 256, qwa);
	if (!CamDirExist(path))
	{
		_mkdir(path);
	}

	sprintf_s(qwa, 256, "\\%02d", camtime.month);
	strcat_s(path, 256, qwa);
	if (!CamDirExist(path))
	{
		_mkdir(path);
	}

	sprintf_s(qwa, 256, "\\%02d", camtime.day);
	strcat_s(path, 256, qwa);
	if (!CamDirExist(path))
	{
		_mkdir(path);
	}

	sprintf_s(qwa, 256, "LOG_%s_%04d%02d%02d_%02d%02d%02d.txt",
		cam->info.code,
		camtime.year,
		camtime.month,
		camtime.day,
		camtime.hour,
		camtime.min,
		camtime.sec);

	strcat_s(path, 256, "\\");
	strcat_s(path, 256, qwa);

	strcpy_s(cam->curr.logpath, path); // Current log path
	strcpy_s(cam->curr.logname, qwa);  // Current log name

	return(retVal);
}

////////////////////////////////////////////////

bool CamOpenNewLogFile(MY_FORM_ARG_VAR, CAMTIME camtime)
{
	bool retIt;
	errno_t myErrno;
	char qwa[1024];
	char c;
	float f;

	retIt = CamCreateNewLogName(camtime);
	c = (char)176;
	f = (float)CAM_VERSION;

	myErrno = fopen_s(&cam->curr.log_fptr, cam->curr.logpath, "w");
	if (myErrno != 0)
	{
		cam->curr.logIsOpen = false;
		retIt = false;
		sprintf_s(qwa, 256, "ERROR open logfile '%s'", cam->curr.logpath);
		WriteMessage(outTextBox, qwa);
	}
	else
	{
		cam->curr.logIsOpen = true;
		retIt = true;

		fprintf(cam->curr.log_fptr, "LOG FILE FOR ALL SKY CAMERA:\r\n");
		fprintf(cam->curr.log_fptr, "================================\r\n");

		sprintf_s(qwa, 1024, "CAMERA: %s    SOFTWARE: uioCam version %.2f with %s",
			cam->info.cameraname, f, cam->info.library);
		fprintf(cam->curr.log_fptr, "%s\r\n", qwa);

		sprintf_s(qwa, 1024, "STATION: %s    CODE: %s    LATITUDE: %.2f%c N    LONGITUDE %.2f%c E",
			cam->info.station_long, cam->info.code, cam->info.latitude, c, cam->info.longitude, c);
		fprintf(cam->curr.log_fptr, "%s\r\n", qwa);


		sprintf_s(qwa, 256, "Open logfile '%s'", cam->curr.logpath);
		if (cam->sys.debug_on) WriteMessage(outTextBox, qwa);


	}

	return(retIt);
}

//////////////////////////////////////////////////////////////////

bool CamOpenInfoFile()
{
	bool retIt;
	errno_t myErrno;

	myErrno = fopen_s(&cam->curr.info_fptr, CAM_INFO_PATH, "w");
	if (myErrno != 0)
	{
		cam->curr.infoIsOpen = false;
		retIt = false;
	}
	else
	{
		cam->curr.infoIsOpen = true;
		retIt = true;
	}

	return(retIt);
}

///////////////////////////////////////////////////////////////////////////



