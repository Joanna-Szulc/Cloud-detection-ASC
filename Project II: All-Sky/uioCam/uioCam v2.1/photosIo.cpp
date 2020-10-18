/* --------------------------------------------------- */
/*                                                     */
/*               P H O T O S I O . C                   */
/*                                                     */
/*    Image manipulation for the uioCam program        */
/* --------------------------------------------------- */
#include "MyForm.h"
#include "include.h"
#include "global.h"

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include <iomanip>
#include <exiv2/exiv2.hpp>
#include <cassert>
#include <fstream>

using namespace std;
using namespace boost::filesystem;
using namespace System;
using namespace System::Diagnostics;
using namespace System::Threading;
using namespace System::Windows::Forms;

int printMetadata(System::Windows::Forms::TextBox^ outTextBox)
{
	string imagePath;
	// First function - find the latest jpg in the directory
	if (cam->intensity_control == 0)
		imagePath = IMAGEPATHLAST; // path to the folder where Remote saves the photos
	if (cam->intensity_control == 1)
		imagePath = IMAGEPATHRAW; // path to the folder where ICE saves the correct photos
	path p(imagePath);
	string image_name;
	time_t latest_time = 0; // Used later to compare the latest modification times of files
	string latest_file = ""; // Used later to find the latest file

	char qwa[1024];

	if (cam->intensity_control == 0)
	{
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
					const char* pathFile = latest_file.c_str();
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
	}

	if (cam->intensity_control == 1)
	{
		try
		{
			if (exists(p))
			{
				if (is_directory(p))
				{
					for (directory_entry& x : directory_iterator(p))
					{
						image_name = x.path().string(); // get directory entry and convert it to string
						string arw = "arw"; // it sees a difference between upper and lower cases
						string ARW = "ARW";
						size_t tmp_1 = image_name.find(arw, 0); // look for jpg or JPG in the path
						size_t tmp_2 = image_name.find(ARW, 0); // return npos if no match is found, npos is max value of size_t
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
					const char* pathFile = latest_file.c_str();
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
	}

	if (exists(latest_file))
	{
		// Second function - extract and show in the output the exiv metadata from the latest jpg
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

		// It's not pretty, but it works
		ostringstream stream1;
		string str1;
		const char* keyDate = "Exif.Image.DateTime";
		stream1 << exifData[keyDate] << endl; // find DateTime through exiv key, convert through stream to const char*
		str1 = stream1.str();
		const char* Date = str1.c_str();

		sprintf_s(qwa, 64, "Date and time was: %s", Date);
		WriteMessage(outTextBox, qwa);

		ostringstream stream2;
		string str2;
		const char* keyExposure = "Exif.Photo.ExposureTime";
		stream2 << exifData[keyExposure] << endl;
		str2 = stream2.str();
		const char* Exposure = str2.c_str();

		sprintf_s(qwa, 64, "Exposure time was: %s", Exposure);
		WriteMessage(outTextBox, qwa);

		ostringstream stream3;
		string str3;
		const char* keyISO = "Exif.Photo.ISOSpeedRatings";
		stream3 << exifData[keyISO] << endl;
		str3 = stream3.str();
		const char* ISO = str3.c_str();

		sprintf_s(qwa, 64, "ISO was: %s", ISO);
		WriteMessage(outTextBox, qwa);

		ostringstream stream4;
		string str4;
		const char* keyProgram = "Exif.Photo.ExposureProgram";
		stream4 << exifData[keyProgram] << endl;
		str4 = stream4.str();
		const char* Program = str4.c_str();

		sprintf_s(qwa, 64, "Program was: %s", Program);
		WriteMessage(outTextBox, qwa);
	}

	return 0;
}

void runICE(System::Windows::Forms::TextBox^ outTextBox, System::Diagnostics::Process^ myProcess)
{
	char qwa[1024];
	myProcess->Start(ICE_EXE_NAME);					// Open program
	Thread::Sleep(1000);						   	// Wait for program to open and run exposure check
	sprintf_s(qwa, 64, "Running ICE.exe.");
	WriteMessage(outTextBox, qwa);
}