/* --------------------------------------------------- */
/*                                                     */
/*          S O N Y C A M E R A I O . C                */
/*                                                     */
/*     Camera functions for the uioCam program         */
/* --------------------------------------------------- */
 
#include "stdafx.h"
#include "MyForm.h"
#include "include.h"
#include "global.h"
#include <String.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <windows.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <boost/filesystem.hpp>
#include <iomanip>
#include <exiv2/exiv2.hpp>

#include "sonyCamera.h"

#include <iostream>
#include <iomanip>
#include <cassert>
#include <typeinfo>

using namespace boost::filesystem;
using namespace System;
using namespace System::Diagnostics;
using namespace System::Threading;
using namespace System::Windows::Forms;
using namespace std;

// array holding the relations between shutter speed actual values and int shutter_speed in uioCam
const string shutter_speed_array[55] = { "1/8000 s", "1/6400 s", "1/5000 s", "1/4000 s", "1/3200 s", "1/2500 s", "1/2000 s", "1/1600 s",
									"1/1250 s", "1/1000 s", "1/800 s", "1/640 s", "1/500 s", "1/400 s", "1/320 s", "1/250 s", "1/200 s",
									"1/160 s", "1/125 s", "1/100 s", "1/80 s", "1/60 s", "1/50 s", "1/40 s", "1/30 s", "1/25 s", "1/20 s",
									"1/15 s", "1/13 s", "1/10 s", "1/8 s", "1/6 s", "1/5 s", "1/4 s", "1/3 s", "0.4 s", "0.5 s", "0.6 s",
									"0.8 s", "1 s", "1.3 s", "1.6 s", "2 s", "2.5 s", "3.2 s", "4 s", "5 s", "6 s", "8 s", "10 s", "13 s",
									"15 s", "20 s", "25 s", "30 s" };
// array holding the relations between ISO actual values and int ISO in uioCam 
const string ISO_array[33] = { "50", "64", "80", "100", "125", "160", "200", "250", "320", "400", "500", "640", "800", "1000", "1250", "1600",
								"2000", "2500", "3200", "4000", "5000", "6400", "8000", "10000", "12800", "16000", "20000", "25600", "32000",
								"40000", "51200", "64000", "65535"};


void openConfig(MY_FORM_ARG_VAR_NEW)
{
	// Try to find window
	HWND hWnd = FindWindowA(NULL, CONFIG_WINDOW_NAME);

	if (hWnd == NULL)
	{
		// Open new process if window not found
		myProcess->Start("notepad.exe", CAM_CONFIG_FILE);
	}
	else
	{
		// Set window active
		SetForegroundWindow(hWnd);
	}
}
void openTime(MY_FORM_ARG_VAR_NEW)
{
	// Try to find window
	HWND hWnd = FindWindowA(NULL, TIME_WINDOW_NAME);

	if (hWnd == NULL)
	{
		// Open new process if window not found
		myProcess->Start("notepad.exe", CAM_TIME_FILE);
	}
	else
	{
		// Set window active
		SetForegroundWindow(hWnd);
	}
}
void openReadMeFile(MY_FORM_ARG_VAR_NEW)
{
	// Try to find window
	HWND hWnd = FindWindowA(NULL, README_WINDOW_NAME);		

	if (hWnd == NULL)
	{	
		// Open new process if window not found
		myProcess->Start("notepad.exe", CAM_README_FILE);
	}
	else
	{
		// Set window active
		SetForegroundWindow(hWnd);							
	}	
}
void openIntensity(MY_FORM_ARG_VAR_NEW)
{
	// Try to find window
	HWND hWnd = FindWindowA(NULL, EXPOSURE_WINDOW_NAME);

	if (hWnd == NULL)
	{
		// Open new process if window not found
		myProcess->Start("notepad.exe", CAM_EXPOSURE_FILE);
	}
	else
	{
		// Set window active
		SetForegroundWindow(hWnd);
	}
}

int initiateCamera(MY_FORM_ARG_VAR_NEW)
{
	int retVal;
	char qwa[1024];

	sprintf_s(qwa, 64, "Opening Remote.");
	if (cam->sys.debug_on) WriteMessage(outTextBox, qwa);

	myProcess->Start(APP_NAME);						// Open program
	Thread::Sleep(500);						   	// Wait for program to open
	// PgDn and Enter is needed only for a newer version of Remote, but it doesn't
	// influence the older version at all.
	SendKeys::Send("{PGDN}");						// Choose the first camera
	SendKeys::Send("{ENTER}");						// I guess it will be one click and it will be slow xD
	Thread::Sleep(2000);						   	// Wait for program to open
	SendKeys::Send(" ");							// Turn live view off

	//-- Safeguard: check that program is starting, camera is connected etc.

	// OK return
	retVal = 0;
	return(retVal);
}

int closeCamera(MY_FORM_ARG_VAR_NEW)
{
	int retVal;
	char qwa[1024];

	//-- Safeguard: make sure Remote is ready to be closed
	Thread::Sleep(1000);								

	HWND hWnd = FindWindowA(NULL, WINDOW_NAME);		    // Find window
	SetForegroundWindow(hWnd);							// Set window active

	sprintf_s(qwa, 64, "Closing Remote.");
	if (cam->sys.debug_on) WriteMessage(outTextBox, qwa);

	//-- Safeguard: if no Remote open, don't send this command (and close uioCam)

	SendKeys::Send("%{F4}");							// Exit program (Alt+F4)

	// OK return
	retVal = 0;
	return(retVal);
}

//-- dummy func
// Runs when "End" button is pressed
int shutdownCamera(MY_FORM_ARG_VAR_NEW)
{
	int retVal;

	// OK return
	retVal = 0;

	return(retVal);
}

int acquireImage(MY_FORM_ARG_VAR_NEW)
{
	int retVal;
	char qwa[1024];

	//-- Safeguard: check if window is open

	HWND hWnd = FindWindowA(NULL, WINDOW_NAME);		    // Find Remote window
	SetForegroundWindow(hWnd);							// Set window active

	sprintf_s(qwa, 64, "Taking picture.");
	if (cam->sys.debug_on) WriteMessage(outTextBox, qwa);

	SendKeys::Send("1");								// Take picture 
	Thread::Sleep(1000);								// Wait for picture to be taken

	return(retVal);
}

///////////////////////////////////////////////
////   I N T E N S I T Y   C O N T R O L   ////
///////////////////////////////////////////////
int updateRemotestat(System::Windows::Forms::TextBox^ outTextBox)
{
	// Find the path to the latest jpg in the directory - should be it's own function, but VS has problem with functions returning strings... unless a string would be a global value?
	path p(IMAGEPATHLAST); // path to the folder where Remote saves the photos
	string image_name;
	time_t latest_time = 0; // Used later to compare the latest modification times of files
	string latest_file = ""; // Used later to find the latest file

	char qwa[1024];

	sprintf_s(qwa, 400, "Updating ISO and shutter speed settings. Camera program has to be in MANUAL.");
	WriteMessage(outTextBox, qwa);

	try
	{
		if (exists(p))
		{
			if (is_directory(p))
			{
				for (directory_entry& x : directory_iterator(p))
				{
					image_name = x.path().string(); // get directory entry and convert it to string
					string jpg = "jpg"; // it sees a difference between upper and lower cases
					string JPG = "JPG";
					size_t tmp_1 = image_name.find(jpg, 0); // look for jpg or JPG in the path
					size_t tmp_2 = image_name.find(JPG, 0); // return npos if no match is found, npos is max value of size_t
					if (tmp_1 != std::string::npos || tmp_2 != std::string::npos) // if jpg or JPG is found
					{ // at this point image_name should only be .jpg found in dir IMAGEPATH
						time_t time = last_write_time(image_name); // see whe thhe file was last modified
						if (time > latest_time) // compare the time
						{
							latest_file = image_name; // if the last_write_time of the current file is higher than the previous one
							// we overwrite the latest_file path to find the path of the latest modified file
						}
					}
				}
				const char* pathFile = latest_file.c_str(); // convert to const char* just for sprintf_s
				sprintf_s(qwa, 400, "Accessing latest file: %s", pathFile);
				WriteMessage(outTextBox, qwa);
			}
			else
			{
				sprintf_s(qwa, 64, "Path exists, but is not a regular file or directory");
				WriteMessage(outTextBox, qwa);
			}
		}
		else
		{
			sprintf_s(qwa, 64, "Path does not exist. Check define.h and path in Remote.");
			WriteMessage(outTextBox, qwa);
		}
	}

	catch (const filesystem_error& ex)
	{
		sprintf_s(qwa, 64, ex.what());
		WriteMessage(outTextBox, qwa);
	}

	if (exists(latest_file))
	{
		// Extract ISO and shutter speed
		Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(latest_file);
		assert(image.get() != 0);
		image->readMetadata();
		Exiv2::ExifData &exifData = image->exifData();
		if (exifData.empty()) {
			string error("No Exif data found in file");
			throw Exiv2::Error(Exiv2::kerErrorMessage, error);
			sprintf_s(qwa, 64, "No Exif data found in file");
			WriteMessage(outTextBox, qwa);
		}
		ostringstream stream2;
		string exposureString;
		const char* keyExposure = "Exif.Photo.ExposureTime";
		stream2 << exifData[keyExposure];
		exposureString = stream2.str();
		//const char* Exposure = exposureString.c_str();

		//sprintf_s(qwa, 64, "Exposure time in Remote: %s", Exposure);
		//WriteMessage(outTextBox, qwa);

		ostringstream stream3;
		string ISOString;
		const char* keyISO = "Exif.Photo.ISOSpeedRatings";
		stream3 << exifData[keyISO];
		ISOString = stream3.str();
		//const char* ISO = ISOString.c_str();

		//sprintf_s(qwa, 64, "ISO in Remote: %s", ISO);
		//WriteMessage(outTextBox, qwa);

		// Compare to ISO and shutter speed array, set ISO and shutter speed values in uioCam
		// From 0.4 s I need to check if that's how actually it is in exiv file
		// BULB and AUTO setting show in exiv as the actual used value of ISO and shutter speed
		// so the value read from file is correctly recognized, but will wreac havoc with
		// makeBrighter() and makeDarker() functions unless I'll set some warnings/precautions
		// any ISO higher than 64000 creates problems, it's always 65535

		for (int i = 0; i < 55; i++)
		{
			if (exposureString == shutter_speed_array[i]) { // look for matching value
				cam->remote.shutter_speed = i;
			}
		}

		for (int i = 0; i < 33; i++)
		{
			if (ISOString == ISO_array[i]) // look for matching value
			{
				cam->remote.ISO = i;
			}
		}

		// Check the exposure program
		ostringstream stream4;
		string ProgramString;
		const char* keyProgram = "Exif.Photo.ExposureProgram";
		stream4 << exifData[keyProgram];
		ProgramString = stream4.str();
		const char* Program = ProgramString.c_str();

		if (ProgramString == "Auto" || ProgramString == "Manual")
		{
			if (ProgramString == "Auto")
			{
				cam->remote.MANUAL = FALSE;
			}
			if (ProgramString == "Manual")
			{
				cam->remote.MANUAL = TRUE;
			}
		}
		else
		{
			sprintf_s(qwa, 128, "Unrecognized exposure program. Check the camera.");
			WriteMessage(outTextBox, qwa);
		}

		//////////// JUST FOR TESTS //////////////////////
		/*sprintf_s(qwa, 64, "Exposure time in uioCam: %i", remote.shutter_speed);
		WriteMessage(outTextBox, qwa);

		const char* testExpo = shutter_speed_array[remote.shutter_speed].c_str();
		sprintf_s(qwa, 64, "Which means: %s", testExpo);
		WriteMessage(outTextBox, qwa);

		sprintf_s(qwa, 64, "ISO in uioCam is: %i", remote.ISO);
		WriteMessage(outTextBox, qwa);

		const char* testISO = ISO_array[remote.ISO].c_str();
		sprintf_s(qwa, 64, "Which means: %s", testISO);
		WriteMessage(outTextBox, qwa);*/
		///////////////// END TESTS ////////////////////////

		// Remove the uneccesary .jpg
		remove(latest_file);

	///////////// Set ISO for daytime and night time //////////////
	// If it's day, the variable cam->sunmoon_ok is set to true
	// If it's night the cam->sunmoon_ok is set to false
	string defaultShutterSpeed = "1/2000 s"; //shutter speed 1/2000 s just to have some default value to start with

	if (cam->sunmoon_ok)
		{
			// Sun above the horizon, set ISO to daytime
			int daytimeISO = 400; // adjust while testing
			setISO(daytimeISO); //setISO takes actual ISO value as int like 50, 64, 100...
			setShutterSpeed(defaultShutterSpeed, outTextBox);
		}
	else
		{
			// Sun below horizon, set ISO to night time
			int nighttimeISO = 640; // arbitrary value, someone needs to adjust when night time will be available
			setISO(nighttimeISO); //setISO takes actual ISO value as int like 50, 64, 100...
			setShutterSpeed(defaultShutterSpeed, outTextBox);
		}
	}

	// Remove uneccesary .arw, last so to make additionally sure that it's already transfered
	string latest_file_arw = latest_file.substr(0, latest_file.find_last_of('.')) + ".arw";

	if (exists(latest_file_arw))
	{
		remove(latest_file_arw);
	}

	sprintf_s(qwa, 64, "Update done, Intensity Control is now ON.");
	WriteMessage(outTextBox, qwa);
	return 0;
}

int setISO(int true_ISO_Value)
{
	char qwa[1024];
	int remote_ISO_new = 0; // variable to hold int equivalent of true_ISO_value
	int remote_ISO_current = cam->remote.ISO; // current int value of ISO in uioCam, updated everytime when Intensity Control is switched ON 

	stringstream ss;
	ss << true_ISO_Value;
	string true_ISO_Value_String = ss.str();

	for (int i = 0; i < 33; i++)
	{
		if (true_ISO_Value_String == ISO_array[i]) // look for matching value
		{
			remote_ISO_new = i;
		}
	}

	int ISO_difference = 0;
	ISO_difference = abs(remote_ISO_current - remote_ISO_new);

	if (remote_ISO_current > remote_ISO_new)
	{
		makeISODarker(ISO_difference);
	}
	if (remote_ISO_current < remote_ISO_new)
	{
		makeISOBrighter(ISO_difference);
	}
	return 0;
}

int makeISOBrighter(int ISO_difference) {
	// Makes picture brighter by
	// increasing ISO
	int retVal;

	HWND hWnd = FindWindowA(NULL, WINDOW_NAME);		    // Find window
	SetForegroundWindow(hWnd);							// Set window active

	for (int i = 0; i < ISO_difference; i++)
	{
		SendKeys::Send("i");	                        // ISO up
		cam->remote.ISO += 1;
		Thread::Sleep(300);										// wait just a moment so all keys will register
	}
	// OK return
	retVal = 0;

	return(retVal);
}

int makeISODarker(int ISO_difference) {
	// Makes picture darker by
	// decreasing ISO
	int retVal;
	HWND hWnd = FindWindowA(NULL, WINDOW_NAME);		    // Find window
	SetForegroundWindow(hWnd);							// Set window active

	for (int i = 0; i < ISO_difference; i++)
	{
		SendKeys::Send("+i");	                        // ISO down
		cam->remote.ISO -= 1;
		Thread::Sleep(300);										// wait just a moment so all keys will register
	}

	// OK return
	retVal = 0;

	return(retVal);
}

int setShutterSpeed(string true_Shutter_Speed_Value, System::Windows::Forms::TextBox^ outTextBox)
{
	char qwa[1024];
	int remote_Shutter_Speed_new = 0; // variable to hold int equivalent of true_ISO_value
	int remote_Shutter_Speed_current = cam->remote.shutter_speed; // current int value of ISO in uioCam, updated everytime when Intensity Control is switched ON 

	for (int i = 0; i < 55; i++)
	{
		if (true_Shutter_Speed_Value == shutter_speed_array[i]) // look for matching value
		{
			remote_Shutter_Speed_new = i;
		}
	}

	int shutter_speed_difference = 0;
	shutter_speed_difference = abs(remote_Shutter_Speed_current - remote_Shutter_Speed_new);

	if (remote_Shutter_Speed_current > remote_Shutter_Speed_new)
	{
		makeShutterSpeedDarker(shutter_speed_difference, outTextBox);
	}
	if (remote_Shutter_Speed_current < remote_Shutter_Speed_new)
	{
		makeShutterSpeedBrighter(shutter_speed_difference, outTextBox);
	}
	return 0;
}

int makeShutterSpeedBrighter(int shutter_speed_difference, System::Windows::Forms::TextBox^ outTextBox) {
	// Makes picture brighter by
	// increasing shutter speed
	int retVal;
	char qwa[1024];
	bool shutter_speedTooBright = 0;

	HWND hWnd = FindWindowA(NULL, WINDOW_NAME);		    // Find window
	SetForegroundWindow(hWnd);							// Set window active

	for (int i = 0; i < shutter_speed_difference; i++)
	{
		if (cam->remote.shutter_speed < 37)
		{
			SendKeys::Send("s");	                        // shutter speed up
			cam->remote.shutter_speed += 1;
			Thread::Sleep(300);								// wait just a moment so all keys will register
		}
		/*else if (cam->remote.shutter_speed >= 37)	// that needs to be done, but I have more time pressing things to test
		{
			makeISOBrighter(1);
			shutter_speedTooBright = 1;
		}*/
		else if (cam->remote.shutter_speed >= 37 && cam->remote.ISO >= 31)
		{
			sprintf_s(qwa, 128, "ISO and shutter speed out of bounds. Protect the camera from overexposure.");
			WriteMessage(outTextBox, qwa);
		}
	}
	// OK return
	retVal = 0;

	return(retVal);
}

int makeShutterSpeedDarker(int shutter_speed_difference, System::Windows::Forms::TextBox^ outTextBox) {
	// Makes picture darker by
	// decreasing shutter speed
	int retVal;
	char qwa[1024];

	HWND hWnd = FindWindowA(NULL, WINDOW_NAME);		    // Find window
	SetForegroundWindow(hWnd);							// Set window active

	for (int i = 0; i < shutter_speed_difference; i++)
	{
		if (cam->remote.shutter_speed > 0)
		{
			SendKeys::Send("+s");	                        // ISO down
			cam->remote.shutter_speed -= 1;
			Thread::Sleep(300);								// wait just a moment so all keys will register
		}
		/*else if (cam->remote.shutter_speed <= 0)		// needs to be done later
		{
			makeISODarker(1);
		}*/
		else if(cam->remote.shutter_speed <= 0 && cam->remote.ISO <= 0)
		{
			sprintf_s(qwa, 128, "ISO and shutter speed out of bounds. Check if shutter opens correctly.");
			WriteMessage(outTextBox, qwa);
		}
	}

	// OK return
	retVal = 0;

	return(retVal);
}

int runIntensityControl(System::Windows::Forms::TextBox^ myTextBox, System::Diagnostics::Process^ myProcess) {
	int retval = 0;
	runExe(myTextBox, myProcess);
	path p(CAM_EXPOSURE_FILE);

	while (!exists(p))
	{
		Thread::Sleep(10); //check if exposure file exists and sleep if not
	}
	readIntensityFile(myTextBox); //read the existing file
	remove(CAM_EXPOSURE_FILE);
	return(retval);
}

// This function opens, reads and interpret the ..\etc\exposure.txt
int readIntensityFile(System::Windows::Forms::TextBox^ myTextBox)
{
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
	int retval;
	char tmp[1024];

	strcpy_s(fipath, 128, CAM_EXPOSURE_FILE);  // CAM_EXPOSURE_FILE, see define.h for definition of name
	ok1 = true;
	ok2 = true;

	myErrno = fopen_s(&infptr, fipath, "r");
	if (myErrno != 0)
	{
		sprintf_s(tmp, 256, "ERROR: Can't open %s file.", fipath);
		WriteMessage(myTextBox, tmp);
		return(-1);
	}

	while (fgets(cLine, 1024, infptr) != NULL)
	{
		ok1 = true; 
		if (!ok1)
		{
			continue;
		}
		pos = 0;
		strcpy_s(qwa, 256, (char *)FirstWord(cLine));

		if (cLine[0] == '0')
		{
			cam->intensity.exposure = 0;
		}
		else if (cLine[0] == '1')
		{
			cam->intensity.exposure = 1;
		}
		else if (cLine[0] == '2')
		{
			cam->intensity.exposure = 2;
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

	retval = 0;
	return(retval);
}

int runExe(System::Windows::Forms::TextBox^ myTextBox, System::Diagnostics::Process^ myProcess)
{
	int retVal;

	char qwa[1024];
	myProcess->Start(ICE_EXE_NAME);					// Open program
	sprintf_s(qwa, 64, "Running ICE.exe.");
	WriteMessage(myTextBox, qwa);
	
	// OK return
	retVal = 0;

	return retVal;
}
