#pragma once

#include <string>
#include "define.h"

// --- GLOBAL structures ---

struct CAMTYPE {
	bool andor_ixon;
	bool princeton_pixis;
	bool photometrics;
	bool sony;
};

struct CAMASTRO {
	float sun_elevation;	// Elevation of the SUN above the horizon in degrees
	float sun_azimuth;		// Azimuth of the SUN east of north in degrees
	float moon_elevation;	// Elevation of the MOON above the horizon in degrees
	float moon_azimuth;		// Azimuth of the MOON east of north in degrees
	float moon_phase;		// MOONs phase in percent
};

struct CAMTIME { // Assumes UT time, YYYY:MM:DD
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
};

struct CAMINFO {
	char station_short[64]; // Short name, ex. 'Ny-Alesund'
	char station_long[256]; // Long name, ex. 'Ny-Alesund, Svalbard, Norway'
	char code[32]; // Three letter code, ex. NYA
	float latitude;
	float longitude;
	float altitude; // Above sea level [m]

	char cameraname[64]; // ex. 'HASI 1'
	int cameranumber; // When several cameras
	int sizeXY; // Size of CCD 
	int filtermax; // Number of filters in camera
	float wavelen[FILTER_MAX]; // Wavelengths [nm]
	char filtername[FILTER_MAX][32]; // filtername[current_filter-1][]

	int radius; // Radius of image [pixels]
	int r_center; // Centre of image in rows (origo is left upper corner)
	int c_center; // Centre of image in columns
	float lens_fov; // Lense field of view, ex. 180 deg 
	int flip_ud; // Flip whole image up/down
	float cam_roll; // Clockwise rotation of camera around camera X-axis (optical axis, back -> front)
	float cam_pitch; // Clockwise rotation of camera around camera Y-axis (left -> right)
	float cam_yaw; // Clockwise rotation of camera around camera Z-axis (down -> up)
	float mag_bearing; // Clockwise angle from geographic north to geomagnetic north
	char projection[256]; // Description of projection, e.g. R=f*theta ; R=2*f*sin(theta/2)
	char calib_filename[256]; // Calibration file name

	char library[64]; // Sofware library name, ex. 'Andor SDK 2.87'
	char comment[256]; // Comment string from comment in config.txt, written to .PNG files 
};

struct CAMSYS {
	bool manual; // False: Run in auto mode
	bool write_log;
	bool write_info;
	bool debug_on;
	bool check_smartmotor;

	float sun_elevation_max;
	float moon_elevation_max;

	//bool write_gamma; // True: Insert 'gamma' chunk in .PNG files (default)
	bool dump_bmp; // False: (default)
	bool home; // True: Do a HOME on the filter wheel at start and every midnight
	bool shutter_stay_open; // True: Shutter open at all times, False: (default)

	int smartmotor_port;  // RS-232 port number for the smart motor, 1 for COM1: , 2 for COM2: , etc.

	bool run_smartmotor; // False: (default),  True: Smartmotor commands are sent
	bool run_camera;   // False: (default), commands to the camera not sent, syntetic image created, True: camera commands sent, data read from camera
	bool run_temp_ctrl; // False: (default), no data read from temperature controller, True: Data read from temperature controller
};

struct CAMCURRENT {
	bool buttons_enabled; // True when buttons are enabled, set to true with man button, and false with auto button
	bool manual; // False: Run in automatic mode, True: Run in manual mode
	bool end; // True: 'End' button is pressed, system should not try to start it again

	FILE *log_fptr;  // File pointer for log file
	bool logIsOpen; // True log file is open, and can be written to

	FILE *info_fptr;  // File pointer for info file
	bool infoIsOpen; // True info file is open, and can be written to

	bool cameraIsStarted; // False: (default), the camera is not initiated  (initiateCamera() is not run)
						  // True: the camera is initiated  (initiateCamera() is run)

	bool smartmotorIsOpen; // True when smartmotor I/O is opened (independent of run_smartmotor)
						   // This means only that the open button is pressed
						   // The run_smartmotor has to be True if the commands should be sent to the smartmotor

	bool minTimerEnabled; // True when the minute timer is running
	bool first_min;

	bool shutterIsOpen;  // True when open_shutter (independent of run_smartmotor)
						 // This means only that the open_shutter button is pressed

	int currentFilter; // Filter #1 is 1, Filter #2 is 2, ...  (default -1)

	char imagename[256]; // Current image file name
	char imagepath[256]; // Current image file name, full path

	int sizeX;   // Current image size from camera CCD
	int sizeY;

	char logname[256]; // Current log file name
	char logpath[256]; // Current log file name, full path
};

struct CAMMODES {
	int normal_interval;
	int normal_filter;
	int normal_intensity_control;
	int normal_post_process;

	int cloud_interval;
	int cloud_filter;
	int cloud_intensity_control;
	int cloud_post_process;

	/*int pol_interval;
	int pol_filter;
	int pol_max_intensity;
	int pol_min_intensity;
	int pol_intensity_control;

	int night_interval;
	int night_filter;
	int night_max_intensity;
	int night_min_intensity;
	int night_intensity_control;
	int night_sun_elev_max;
	int night_moon_elev_max;*/
};

struct CAMINTENSITY { //it will probably go away once my function will work, or maye not
	int exposure; // 0 - underexposed, 1 - good exposure, 2 - overexposed
	bool exposureOk = 0;
};

////--- uioCam v2.1 ---////
struct REMOTESTAT {  // struct to keep information about camera/Remote settings
	int shutter_speed; // shutter speed as in Remote
	int ISO; // ISO as in Remote
	bool MANUAL; // exposure program on the Camera, set to TRUE when Manual, FALSE when Auto, other programs give of a warning
};

struct CAMSTAT {
	CAMTYPE type;
	CAMSYS  sys;
	CAMCURRENT curr;

	CAMINFO info;
	CAMASTRO astro;
	CAMMODES modes;
	CAMINTENSITY intensity;

	REMOTESTAT remote;

	int run_mode;
	int first_mode_set;
	int intensity_control;
	int intensity_control_helper_troll; // amazingly important helping variable that talks to trolls inside uioCam
	int post_process;

	int manual;

	int noTime; // Number of start & stop times startTime[noTime], endTime[noTime]
	CAMTIME *startTime; // Interval start times
	CAMTIME *endTime; // Interval end times

	//PNGCRC crc; // Used in CRC functions

	bool min_ok; // To check if exposure can start this minute
	bool sec_ok; // To check if exposure can start this second
	int start_sec; // Second in the minute to do first exposure
	int start_min; // Minute in the hour to do first exposure
	int interval;  // Number of seconds between each exposure
	int filter;    // Filter number
	int sec_since_img; // Counter, seconds since last image was taken

	//long *imageArray;  // Image array to hold one image from the camera


					   // These are the variables that defines if the camera is running or not
					   // 
	bool run_ok;     // False: (default) camera is not running, True: camera is running
	bool timeseq_ok; // False: (default) time is outside time sequences in d:\tmp\camtime.seq, True: time is inside ..
	bool sunmoon_ok; // False: (default) sun and/or moon are outside limits, True: sun and moon are inside limits
					 //
					 // The run_ok and timeseq_ok is set in the function CheckSeqTime(), (sequence.cpp)
					 // The run_ok can also be set to false in the SeqTimer_ function, light detector test
					 // The sunmoon_ok is set in the CheckSunMoon() function , (sequence.cpp)
};

// --- Function definitions ---

#define MY_FORM_ARG_DEF \
		System::IO::Ports::SerialPort^, \
		System::Windows::Forms::TextBox^, \
		int , \
		char *

// Function arguments in *.cpp files
#define MY_FORM_ARG_VAR \
	     System::IO::Ports::SerialPort^  comPort1, \
		 System::Windows::Forms::TextBox^ outTextBox, \
		 int argVal, \
		 char *argLine

// Secondary function call in *cpp files
#define MY_FORM_ARG_FUNC \
				 comPort1, \
			     outTextBox, \
				 argVal, \
				 argLine

// Function arguments in Form1.h 'control' functions 
// The text variable has to be defined as 'char argText[1024];' in the calling function
// The int argValue has to be defined in the calling function
#define MY_FORM_ARG_CALL \
	    serialPort1, \
		outputText, \
		argValue, \
		argText

////--- uioCam v2.0 ---////
// For controlling Sony Imaging Edge Remote

#define MY_FORM_ARG_DEF_NEW \
		System::IO::Ports::SerialPort^, \
		System::Windows::Forms::TextBox^, \
		int , \
		char *, \
		System::Diagnostics::Process^

// Function arguments in *.cpp files
#define MY_FORM_ARG_VAR_NEW \
	     System::IO::Ports::SerialPort^  comPort1, \
		 System::Windows::Forms::TextBox^ outTextBox, \
		 int argVal, \
		 char *argLine, \
		 System::Diagnostics::Process^ myProcess

// Secondary function call in *cpp files
#define MY_FORM_ARG_FUNC_NEW \
				 comPort1, \
			     outTextBox, \
				 argVal, \
				 argLine, \
				 myProcess

// Function arguments in Form1.h 'control' functions 
// The text variable has to be defined as 'char argText[1024];' in the calling function
// The int argValue has to be defined in the calling function
#define MY_FORM_ARG_CALL_NEW \
	    serialPort1, \
		outputText, \
		argValue, \
		argText, \
		process

// --- More function definitions ---

// in photosIo.cpp  ..............................
// here I'll put all functions from photosIo
int printMetadata(System::Windows::Forms::TextBox^ outTextBox); // those are two functions in one, because uioCam doesn't like strings..
//void runExe(System::Windows::Forms::TextBox^ outTextBox, System::Diagnostics::Process^ myProcess);

// in smartMotorIo.cpp ...........................
int smartMototorOpenSerialPort1(MY_FORM_ARG_DEF);
int smartMototorCloseSerialPort1(MY_FORM_ARG_DEF);
int smartMotorHome(MY_FORM_ARG_DEF);
int smartMotorOpenShutter(MY_FORM_ARG_DEF);
int smartMotorCloseShutter(MY_FORM_ARG_DEF);
int smartMotorSelectFilter(MY_FORM_ARG_DEF);
int smartMotorFullTurn(MY_FORM_ARG_DEF);

// in sonyCameraIo.cpp ...........................
void openConfig(MY_FORM_ARG_DEF_NEW);
void openTime(MY_FORM_ARG_DEF_NEW);
void openReadMeFile(MY_FORM_ARG_DEF_NEW);
void openIntensity(MY_FORM_ARG_DEF_NEW);
int updateRemotestat(System::Windows::Forms::TextBox^ outTextBox);
int initiateCamera(MY_FORM_ARG_DEF_NEW);
int closeCamera(MY_FORM_ARG_DEF_NEW);
int shutdownCamera(MY_FORM_ARG_DEF_NEW);
int acquireImage(MY_FORM_ARG_DEF_NEW);
int runIntensityControl(System::Windows::Forms::TextBox^ myTextBox, System::Diagnostics::Process^ myProcess);
int readIntensityFile(System::Windows::Forms::TextBox^ myTextBox);
int runExe(System::Windows::Forms::TextBox^ myTextBox, System::Diagnostics::Process^ myProcess);
int setISO(int true_ISO_Value); // true_ISO_Value like 50, 64, 100, 200
int setShutterSpeed(std::string true_Shutter_Speed_Value, System::Windows::Forms::TextBox^ outTextBox); // like "1/2000 s"
int makeISOBrighter(int ISO_difference);
int makeISODarker(int ISO_difference);
int makeShutterSpeedBrighter(int shutter_speed_difference, System::Windows::Forms::TextBox^ outTextBox);
int makeShutterSpeedDarker(int shutter_speed_difference, System::Windows::Forms::TextBox^ outTextBox);

// in file.cpp ....................................
bool CamCreateNewImageName(int, CAMTIME);
bool CamCreateNewLogName(CAMTIME);
bool CamOpenNewLogFile(MY_FORM_ARG_DEF, CAMTIME);
bool CamOpenInfoFile();

// in func.cpp ....................................
int InitiateUioCam(MY_FORM_ARG_VAR);
int ReadEtcFilesUioCam(MY_FORM_ARG_VAR, System::Windows::Forms::Label^ topText);
int ReadCamSetupFile(System::Windows::Forms::TextBox^);
System::String^ GetTimeString();
System::String^ GetDateString();
System::String^ GetAstroString();
void GetHourMinSec(int *, int *, int *);
void GetYearMonthDayHourMinSec(int *, int *, int *, int *, int *, int *);
void WriteMessage(System::Windows::Forms::TextBox^, char *);
void WriteTopText(System::Windows::Forms::Label^, char *);
int CheckTime(CAMTIME, CAMTIME);
//int AllocateImageBuffer(void);
//void FreeImageBuffer(void);
bool CamDirExist(char *path);

// in sequence.cpp .................................
int ReadCamTimeFile(System::Windows::Forms::TextBox^);
int CheckSeqTime(System::Windows::Forms::Label^);
int CheckSunMoon();
//--int ReadSequenceFileNew(System::Windows::Forms::TextBox^);
void ExposeImageSeqNew(MY_FORM_ARG_DEF);

// modes.cpp .......................................
int initNormalMode(MY_FORM_ARG_DEF);
int initCloudMode(MY_FORM_ARG_DEF);
//int initPolMode(MY_FORM_ARG_DEF);
//int initNightMode(MY_FORM_ARG_DEF);

// astroIo.cpp .....................................
int AstroUpdate(int, int, int, int, int, int);

// in strings.cpp ..................................
char *FirstWord(char *);
char *WordAfterN(char *, char *, int *);
char *LineAfterN(char *, char *, int *);