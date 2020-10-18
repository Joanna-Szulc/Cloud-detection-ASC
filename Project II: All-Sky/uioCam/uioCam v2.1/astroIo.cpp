/* --------------------------------------------------- */
/*                                                     */
/*         A S T R O I O . C                           */
/*                                                     */
/*     Astro functions for the uioCam program          */
/* --------------------------------------------------- */

#include "stdafx.h"
#include "include.h"
#include "MyForm.h"
#include <String.h>
#include <stdio.h>
#include <stdlib.h>
#include "yAstro_astro.h"
#include "Isutil.h"
#include "astroIo.h"


/* Global variables in this file */

ASTROLOCSITE astroSite;
ASTROSTATE astroState;

// From astro.h :: float co_az;  azimuth, >0 e of n, rads 
//                 i.e. the co_az below is azimuth 'East of North' in radians

// From astro.h     float co_alt;  altitude above topocentric horizon, rads
//                  i.e. the co_alt is yje altitude above (topocentric) horizon in radians

void AstroComputeObject(ASTROLOCSITE *site, ASTROSTATE *state, CAMASTRO *astro)
{
	Now now;
	Obj obj;
	ASTROLOCSUN msun;
	ASTROLOCMOON moon;
	//ASTROLOCSUN jupiter;
	//ASTROLOCSUN mars;
	//ASTROLOCSUN venus;
	double f;
	int i;
	double beta;

	f = (double)site->cal.second + (double)site->cal.ns / 1.0e+09;

	for (i = 0; i < 2; i++) /* 0: sun, 1: moon, 2: jupiter, 3: mars, 4: venus */
	{                       /* it crashes on Jupiter, Mars and Venus therefore the 'i < 2' in the line above */
							/* later when Jupiter, Mars and Venus works it will be 'i < 5'                  */


		now.n_mjd = site->julian;
		now.n_lat = site->lat_r;
		now.n_lng = site->long_r;

		now.n_tz = 0.0; /* all in UTC time*/
		now.n_temp = site->temperature;
		now.n_pressure = site->apressure;

		now.n_elev = site->reRe;

		now.n_dip = site->twilight_r;

		now.n_epoch = EOD;
		strcpy_s(now.n_tznm, 8, "CET");

		if ((i == 0) && (state->psun)) /* sun .............................................. */
		{
			obj.o_type = PLANET; /* we want the SUN */
			obj.pl_code = SUN;

			obj_cir(&now, &obj);

			msun.azimuth = /* 180.0 - */ obj.any.co_az  * 180.0 / M_PI; /* Eastern azimuth, deg */
			msun.elevation = obj.any.co_alt * 180.0 / M_PI; /* Elevation above topocentric horizon,deg */

			if (state->ehoriz == 1)
			{
				beta = (M_PI / 2.0 + obj.any.co_alt - asin(1.0 / (1.0 + site->reRe))) * 180.0 / M_PI;
			}

			// We have state->ehoriz = 0
			astro->sun_elevation = (float)msun.elevation;
			astro->sun_azimuth = (float)msun.azimuth;
		}

		else if ((i == 1) && (state->pmoon))  /* moon .......................................*/
		{
			obj.o_type = PLANET; /* we want the MOON */
			obj.pl_code = MOON;

			obj_cir(&now, &obj);

			moon.azimuth = /* 180.0 - */ obj.any.co_az * 180 / M_PI; /* Eastern azimuth, deg */
			moon.elevation = obj.any.co_alt * 180 / M_PI; /* Elevation above topocentric horizon,deg */
			moon.phase = obj.pl.so_phase; /* phase in degrees */

			astro->moon_elevation = (float)moon.elevation;
			astro->moon_azimuth = (float)moon.azimuth;
			astro->moon_phase = (float)moon.phase;

		}
	}
}


int AstroInitSolar(ASTROLOCSITE *site, ASTROSTATE *state)
{
	/* Set default values */

	site->rekm = 0.0; /* sea level */
	site->reRe = 0.0;
	site->temperature = 0.0; /* 0 deg Celcius */
	site->apressure = 1013.2; /* 1013.2 milliBar */
	site->twilight_dip = 0.0;
	site->twilight_r = 0.0;

	state->mode = 0;
	state->psun = 1;
	state->pmoon = 0;
	//state->pjupiter = 0;
	//state->pmars = 0;
	//state->pvenus = 0;
	state->ehoriz = 0;  // This is 0
	strcpy_s(state->file_name, 64, "");
	state->stepn = 1; /* default is one step */
	state->gaps = 1;
	state->millisec = 0;
	state->header = 1;
	state->short_clmn = 0;
	strcpy_s(state->banner, 64, "");
	strcpy_s(state->comment, 64, "");

	return(0);
}


int AstroUpdate(int year, int month, int day, int hour, int min, int sec)
{
	CAMASTRO astro;
	int retno;

	retno = 0;

	AstroInitSolar(&astroSite, &astroState);
	astroState.pmoon = 1; /* also compute for moon */

	astroSite.cal.year = year;
	astroSite.cal.month = month;
	astroSite.cal.day = day;
	astroSite.cal.hour = hour;
	astroSite.cal.minute = min;
	astroSite.cal.second = sec;
	astroSite.cal.ns = 0;

	astroSite.year = year;
	astroSite.month = month;
	astroSite.day = day;
	astroSite.hour = hour;
	astroSite.minute = min;
	astroSite.sec_f = (double)sec;

	astroSite.day_f = (double)astroSite.day + (double)astroSite.hour / 24.0 + (double)astroSite.minute / 1440.0
		+ astroSite.sec_f / 86400.0;

	astroSite.latitude = cam->info.latitude;
	astroSite.longitude = cam->info.longitude;

	astroSite.lat_r = astroSite.latitude * M_PI / 180.0;
	astroSite.long_r = astroSite.longitude * M_PI / 180.0;

	astroSite.rekm = cam->info.altitude / 1000.0;  // in km
	astroSite.reRe = astroSite.rekm / REARTH;

	cal_mjd(astroSite.month, astroSite.day_f, astroSite.year, &astroSite.julian); /* compute the modified Julian date */

	AstroComputeObject(&astroSite, &astroState, &astro);

	cam->astro.sun_elevation = astro.sun_elevation;
	cam->astro.sun_azimuth = astro.sun_azimuth;
	cam->astro.moon_elevation = astro.moon_elevation;
	cam->astro.moon_azimuth = astro.moon_azimuth;
	cam->astro.moon_phase = astro.moon_phase;

	return(retno);
}




