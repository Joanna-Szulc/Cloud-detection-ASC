/* --------------------------------------------------- */
/*                                                     */
/*             S E Q U E N C E . C P P                 */
/*                                                     */
/*           Not func.cpp \o/  ..or is it?             */
/* --------------------------------------------------- */

#include "stdafx.h"
#include "MyForm.h"
#include <String.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "include.h"
#include "global.h"
using namespace System::Diagnostics;

// debug
#include <iostream>
using namespace std;

//////////////////////////////////////////////////////////////////////////////////
//
//  #####     #    #    #  ######     #    #    #   #####  ######  #####   #    #
//    #       #    ##  ##  #          #    ##   #     #    #       #    #  #    #
//    #       #    # ## #  #####      #    # #  #     #    #####   #    #  #    #
//    #       #    #    #  #          #    #  # #     #    #       #####   #    #
//    #       #    #    #  #          #    #   ##     #    #       #   #    #  #
//    #       #    #    #  ######     #    #    #     #    ######  #    #    ##  #
//
///////////////////////////////////////////////////////////////////////////////////



// ################################################################
// ReadCamTimeFile()
// This function reads and interprets the file "D:\etc\camtime.txt" -> ..\etc\time.txt
//

int ReadCamTimeFile(System::Windows::Forms::TextBox^ myTextBox)
{
	// This function opens, reads and interpret the 
	// D:\etc\camtime.txt file -> ..\etc\time.txt

	FILE *infptr;
	char cLine[1024];
	char qwa[1024];
	char qwb[1024];
	char fipath[256];
	errno_t myErrno;
	bool ok;
	int pos;
	int i;

	strcpy_s(fipath, 128, CAM_TIME_FILE);  // Name defined in define.h, was 64
	ok = true;

	myErrno = fopen_s(&infptr, fipath, "r");
	if (myErrno != 0)
	{
		sprintf_s(qwa, 256, "ERROR: Can't open %s file.", fipath);
		WriteMessage(myTextBox, qwa);
		return(-1);
	}

	cam->noTime = 0;

	while (fgets(cLine, 1024, infptr) != NULL)
	{
		ok = true;
		if (cLine[0] == '#') ok = false; // # in first character pos => comment line
		if ((int)strlen(cLine) < 10) ok = false; // not a valid line 
		if (!ok)
		{
			ok = true;
			continue;
		}

		cam->noTime++;
	}

	cam->startTime = (CAMTIME *)malloc(cam->noTime * sizeof(CAMTIME));
	cam->endTime = (CAMTIME *)malloc(cam->noTime * sizeof(CAMTIME));
	rewind(infptr);

	i = 0;
	while (fgets(cLine, 1024, infptr) != NULL)
	{
		ok = true;
		if (cLine[0] == '#') ok = false; // # in first character pos => comment line
		if ((int)strlen(cLine) < 10) ok = false; // not a valid line 
		if (!ok)
		{
			ok = true;
			continue;
		}

		// WriteMessage(myTextBox,cLine);

		pos = 0;
		strcpy_s(qwa, 256, (char *)FirstWord(cLine));

		// 2010-10-07
		// 0123456789

		cam->startTime[i].year = (qwa[0] - '0') * 1000
			+ (qwa[1] - '0') * 100
			+ (qwa[2] - '0') * 10
			+ (qwa[3] - '0');

		cam->startTime[i].month = (qwa[5] - '0') * 10
			+ (qwa[6] - '0');

		cam->startTime[i].day = (qwa[8] - '0') * 10
			+ (qwa[9] - '0');


		strcpy_s(qwb, 256, WordAfterN(qwa, cLine, &pos));

		// 07:22:10
		// 01234567

		cam->startTime[i].hour = (qwb[0] - '0') * 10
			+ (qwb[1] - '0');

		cam->startTime[i].min = (qwb[3] - '0') * 10
			+ (qwb[4] - '0');

		cam->startTime[i].sec = (qwb[6] - '0') * 10
			+ (qwb[7] - '0');


		strcpy_s(qwa, 256, (char *)WordAfterN(qwb, cLine, &pos));

		// 2010-10-07
		// 0123456789

		cam->endTime[i].year = (qwa[0] - '0') * 1000
			+ (qwa[1] - '0') * 100
			+ (qwa[2] - '0') * 10
			+ (qwa[3] - '0');

		cam->endTime[i].month = (qwa[5] - '0') * 10
			+ (qwa[6] - '0');

		cam->endTime[i].day = (qwa[8] - '0') * 10
			+ (qwa[9] - '0');


		strcpy_s(qwb, 256, WordAfterN(qwa, cLine, &pos));

		// 07:22:10
		// 01234567

		cam->endTime[i].hour = (qwb[0] - '0') * 10
			+ (qwb[1] - '0');

		cam->endTime[i].min = (qwb[3] - '0') * 10
			+ (qwb[4] - '0');

		cam->endTime[i].sec = (qwb[6] - '0') * 10
			+ (qwb[7] - '0');


		i++;
		if (i >= cam->noTime) break;

	}

	if (ok)
	{
		sprintf_s(qwa, 256, "The file %s was successfully decoded.", fipath);
		WriteMessage(myTextBox, qwa);
	}

	fclose(infptr);

	return(0);
}


//////////////////////////////////////////////////////////
// int CheckSeqTime()
//
// This function checks if the system UT time is inside an interval defined in D:\tmp\camtime.txt 
//
// The variables: cam->run_ok = true/false     and      cam->timeseq_ok = true/false    are set
//
// The default return value is 0
// If the system is waiting on next interval it returns -1
// If the system is inside one time interval it returns 1
// If the system has passed all intervals it returns -2
//

int CheckSeqTime(System::Windows::Forms::Label^ myLabel)
{
	int retVal;
	struct tm newtime;
	time_t ltime;
	errno_t errt;
	int i;
	CAMTIME currentTime;
	int start;
	int end;
	char qwa[1024];
	char qwb[256];
	char smt_txt[64];
	char cam_txt[64];
	bool found;

	retVal = 0;
	found = false;  // state not found


	if (cam->sys.run_smartmotor) {
		sprintf_s(cam_txt, 64, "SMARTMTR ON");
	}
	else {
		sprintf_s(cam_txt, 64, "smartmtr off");
	}

	if (cam->sys.run_camera) {
		sprintf_s(smt_txt, 64, "CAMERA ON");
	}
	else {
		sprintf_s(smt_txt, 64, "camera off");
	}


	time(&ltime);
	errt = gmtime_s(&newtime, &ltime);

	currentTime.year = newtime.tm_year + 1900; // Year (current year minus 1900).
	currentTime.month = newtime.tm_mon + 1; // Month (0 – 11; January = 0).
	currentTime.day = newtime.tm_mday;
	currentTime.hour = newtime.tm_hour;
	currentTime.min = newtime.tm_min;
	currentTime.sec = newtime.tm_sec;

	i = 0;

	while (i < cam->noTime)
	{

		// CheckTime(a,b) returns  1 when a > b
		// CheckTime(a,b) returns  0 when a = b
		// CheckTime(a,b) returns -1 when a < b

		start = CheckTime(currentTime, cam->startTime[i]);
		end = CheckTime(currentTime, cam->endTime[i]);

		if ((start < 0) && (end < 0))   // CURRENT TIME IS BEFORE THIS TIME INTERVAL (i)
		{

			//   a) waiting on next interval
			//   currentTime   startTime[i]   endTime[i]  
			//            start<0       end<0

			found = true;
			sprintf_s(qwa, 100, "%s %s Wait on next start %04d-%02d-%02d %02d:%02d:%02d UT",
				cam_txt, smt_txt,
				cam->startTime[i].year,
				cam->startTime[i].month,
				cam->startTime[i].day,
				cam->startTime[i].hour,
				cam->startTime[i].min,
				cam->startTime[i].sec);
			myLabel->ForeColor = System::Drawing::Color::Blue;
			WriteTopText(myLabel, qwa);

			cam->run_ok = false;  // STOP CAMERA
			cam->timeseq_ok = false;

			retVal = -1;
			break;  // do not check next time interval

		}
		else if ((start >= 0) && (end < 0))  // CURRENT TIME IS INSISDE THIS TIME INTERVAL (i)
		{
			//   b) inside a time interval
			//   startTime[i]  currentTime  endTime[i]
			//    start >= 0        end<0

			if (cam->sunmoon_ok)  // All is OK
			{
				strcpy_s(qwb, 64, "is");
				myLabel->ForeColor = System::Drawing::Color::Green;
			}
			else    // Sorry time is OK but SUN or MOON is to high
			{
				strcpy_s(qwb, 64, "is NOT");
				myLabel->ForeColor = System::Drawing::Color::DarkViolet;
			}

			found = true;
			sprintf_s(qwa, 100, "%s %s Camera %s running until %04d-%02d-%02d %02d:%02d:%02d UT",
				cam_txt, smt_txt,
				qwb,
				cam->endTime[i].year,
				cam->endTime[i].month,
				cam->endTime[i].day,
				cam->endTime[i].hour,
				cam->endTime[i].min,
				cam->endTime[i].sec);

			WriteTopText(myLabel, qwa);

			cam->run_ok = true;   // RUN CAMERA
			cam->timeseq_ok = true;

			retVal = 1;
			break;

		}
		else if ((i == cam->noTime - 1) && (start > 0) && (end > 0)) // CURRENT TIME IS BEHIND LAST TIME INTERVAL
		{
			//   c) passed all intervals
			//   startTime[i]   endTime[i]  currentTime
			//   start>0         end>0

			found = true;
			sprintf_s(qwa, 100, "%s %s Camera has passed last interval %04d-%02d-%02d %02d:%02d:%02d UT",
				cam_txt, smt_txt,
				cam->endTime[i].year,
				cam->endTime[i].month,
				cam->endTime[i].day,
				cam->endTime[i].hour,
				cam->endTime[i].min,
				cam->endTime[i].sec);
			myLabel->ForeColor = System::Drawing::Color::DarkBlue;
			WriteTopText(myLabel, qwa);

			cam->run_ok = false; // STOP CAMERA
			cam->timeseq_ok = false;

			retVal = -2;
			break;

		}
		i++;
	} // next time interval


	if (!found)  // state not found ??
	{
		sprintf_s(qwa, 100, "%s %s  Camera time sequence state unknown ?",
			cam_txt, smt_txt);
		myLabel->ForeColor = System::Drawing::Color::Red;
		WriteTopText(myLabel, qwa);
	}



	return(retVal);
}

// #############################################
// CheckSunMoon()
// This function checks the if it's night or daytime
// If it's day, the variable cam->sunmoon_ok is set to true
// If it's night the cam->sunmoon_ok is set to false
// The run_ok is set to false only during the off-times set
// in the \etc\time.txt
// Day is simply the time that Sun is over the horizon.
//
// In the future - maybe adjust the ISO to the phase of the Moon as well
int CheckSunMoon()
{
	int retVal;
	retVal = 0;

	if (cam->astro.sun_elevation < 0.0)
	{
		cam->sunmoon_ok = false;
	}
	else
	{
		cam->sunmoon_ok = true;
	}
	return(retVal);
}


/////////////////////////////////////////////////////////////////////////
//
//  ####   ######   ####   #    #  ######  #    #   ####   ######   ####
// #       #       #    #  #    #  #       ##   #  #    #  #       #
//  ####   #####   #    #  #    #  #####   # #  #  #       #####    ####
//      #  #       #  # #  #    #  #       #  # #  #       #            #
// #    #  #       #   #   #    #  #       #   ##  #    #  #       #    #
//  ####   ######   ### #   ####   ######  #    #   ####   ######   ####
//
//////////////////////////////////////////////////////////////////////////


// #######################################################################
// ReadSequenceFileNew()
// 
// This function opens, reads and interpret the new sequence file etc\sequence.txt
// For the Sony camera, uioCam v2.0
//-- 

/*int ReadSequenceFileNew(System::Windows::Forms::TextBox^ myTextBox)
{
	FILE *infptr;
	char cLine[1024];
	char qwa[1024];
	char fipath[256];
	errno_t myErrno;
	bool ok;
	int pos;

	strcpy_s(fipath, 256, CAM_SEQUENCE_FILE_NEW);  // defined in define.h
	ok = true;

	myErrno = fopen_s(&infptr, fipath, "r");
	if (myErrno != 0)
	{
		sprintf_s(qwa, 256, "ERROR: Can't open %s file.", fipath);
		WriteMessage(myTextBox, qwa);
		return(-1);
	}

	while (fgets(cLine, 1024, infptr) != NULL)
	{
		ok = true;
		if (cLine[0] == '#') ok = false;        // # in first character pos => comment line
		if ((int)strlen(cLine) < 3) ok = false; // not a valid line
		if (!ok)
		{
			ok = true;
			continue;
		}

		pos = 0;
		strcpy_s(qwa, 256, (char *)FirstWord(cLine));

		if (!strcmp(qwa, "start_sec:"))
		{
			cam->start_sec = atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "start_min:"))
		{
			cam->start_min = atoi(WordAfterN(qwa, cLine, &pos));
		}
		else if (!strcmp(qwa, "interval:"))
		{
			cam->interval = atoi(WordAfterN(qwa, cLine, &pos));
			cam->modes.normal_interval = cam->interval;
		}
		else if (!strcmp(qwa, "filter:"))
		{
			cam->filter = atoi(WordAfterN(qwa, cLine, &pos));
			cam->modes.normal_filter = cam->filter;
		}
	}
	if (ok)
	{
		sprintf_s(qwa, 256, "The file %s was successfully decoded.", fipath);
		WriteMessage(myTextBox, qwa);
	}
	fclose(infptr);

	cam->min_ok = false;
	cam->sec_ok = false;

	return(0);
}
////////////////////////////////////*/


// ########################################################################
// ExposeImageSeqNew(MY_FORM_ARG_VAR)
// expose a new image with the settings from the entry [no] in sequence file
//
void ExposeImageSeqNew(MY_FORM_ARG_VAR)
{
	int start_sec;
	int start_min;
	int interval;
	int filter;
	char qwa[1024];
	CAMTIME camtime;
	int result;
	Process^ myProcess;

	GetYearMonthDayHourMinSec(&camtime.year, &camtime.month, &camtime.day,  // Get the time, this is used in the file name and
		&camtime.hour, &camtime.min, &camtime.sec); // written into the 'image file header'.

	if ((cam->curr.cameraIsStarted) && (cam->sys.run_camera))  // We should use the camera
	{
		result = acquireImage(MY_FORM_ARG_FUNC_NEW);  // Expose one image

		sprintf_s(qwa, 256, "expose filter; %d, start sec: %d, start min: %d, interval: %d s, file %s",
			cam->filter,
			cam->start_sec,
			cam->start_min,
			cam->interval,
			cam->curr.imagename);
	}
	else
	{
		sprintf_s(qwa, 256, "no expose because camera is not running");
	}

	WriteMessage(outTextBox, qwa);
}
/////////////////////////////////////////////////////////////////