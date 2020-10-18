/*
* ######################################################################
* #                                                                    #
* #                                                                    #
* #                  A S T R O I O  . H                                #
* #                                                                    #
* #      This is the include file for the astroIo.cpp file             #
* #                                                                    #
* ######################################################################
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Isutil.h"

#define REARTH 6371.2 
#define ARGSTRLEN 2048

struct ASTROLOCSITE  /*  properties of the observers site */
{
	IsTime istime;  /* current time in Isdat time format */
	IsCalendar cal; /* current time in Isdat calendar format */
	int year;       /* year */
	int month;      /* month */
	int day;        /* day   */
	int hour;       /* hour  */
	int minute;     /* minute */
	double sec_f;   /* second */
	double day_f;   /* day float i.e. day + hour/24 + sec_f/86400  */
	double julian; /* Modified Julian date (number of days elapsed since 1900 jan 0.5) */
	double latitude; /* latitude of observer, degrees */
	double longitude; /* longitude of observer, degrees */
	double lat_r;     /* latitude of observer, radians  */
	double long_r;    /* longitude of observer, radians */
	double rekm;      /* altitude above sea level in km */
	double reRe;       /* altitude above sea level in Re */
	double temperature; /* temperature in degrees Celcius */
	double apressure;  /* atmospheric pressure in millibar */
	double twilight_dip; /* dip of sun below horizon at twilight in degrees */
	double twilight_r;   /* dip of sun below horizon at twilight in radians */
};


struct ASTROLOCSUN
{
	double azimuth; /* Eastern azimuth, deg */
	double elevation; /* Elevation above topocentric horizon,deg */
};

struct  ASTROLOCMOON
{
	double azimuth; /* Eastern azimuth, deg */
	double elevation; /* Elevation above topocentric horizon,deg */
	double phase;    /* phase in % */
}
LocMoon;


struct ASTROSTATE
{
	int mode; /* 0: Not defined  */
			  /* 1: Read command from arguments */
			  /* 2: Read command from ascii file */

	int psun;     /* 1: Print sun location (default), else 0 */
	int pmoon;    /* 1: Print moon location ,    else 0 (default) */
	int pjupiter; /* 1: Print Jupiter location , else 0 (default) */
	int pmars;    /* 1: Print Mars location ,    else 0 (default) */
	int pvenus;   /* 1: Print Venus location ,   else 0 (default) */

	int ehoriz;  /*  1: Print sun elevation in deg above true horzion, else 0 (default) */

	char file_name[256]; /* command from ascii file */

	int stepn; /* number of steps */
	int gaps;  /* gap between each step in integer seconds */

	int millisec; /* 1: add milli sec to time output, else 0  (default) */
	int header;   /* 1: print comment header at the top of the file (default), else 0 */

	int short_clmn;  /* 1: do only print time & data columns, else 0 (default) */

	char banner[256]; /* top banner */
	char myargstr[ARGSTRLEN]; /* input arguments */
	char comment[1024]; /* comment text */
};

// functions
void AstroComputeObject(ASTROLOCSITE, ASTROSTATE, CAMASTRO);
int AstroInitSolar(ASTROLOCSITE, ASTROSTATE);
int AstroUpdate(int, int, int, int, int, int);