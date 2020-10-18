/* ---------------------------------------- */
/*                                          */
/*            M O D E S . C P P             */
/*                                          */
/*         Different running modes          */
/* ---------------------------------------- */

#include "stdafx.h"
#include "MyForm.h"
#include "include.h"

int initNormalMode(MY_FORM_ARG_VAR) {
	int retVal;
	char qwa[1024];

	// Update values
	cam->interval = cam->modes.normal_interval;
	cam->filter = cam->modes.normal_filter;
	cam->intensity_control = cam->modes.normal_intensity_control;
	cam->post_process = cam->modes.normal_post_process;

	sprintf_s(qwa, 256, "NORMAL MODE: filter %d, interval time: %d s", 
		cam->filter, cam->interval);
	WriteMessage(outTextBox, qwa);

	if (cam->intensity_control == 0)
	{
		sprintf_s(qwa, 256, "NORMAL MODE: Camera program should be on AUTO when intensity control is OFF");
		WriteMessage(outTextBox, qwa);
	}

	if (cam->intensity_control == 1)
	{
		sprintf_s(qwa, 256, "NORMAL MODE: Camera program should be on MANUAL when intensity control is ON");
		WriteMessage(outTextBox, qwa);
	}

	// OK return
	retVal = 0;

	return(retVal);
}

int initCloudMode(MY_FORM_ARG_VAR) {
	int retVal;
	char qwa[1024];

	// Update values
	cam->interval = cam->modes.cloud_interval;
	cam->filter = cam->modes.cloud_filter;
	cam->intensity_control = cam->modes.cloud_intensity_control;
	cam->post_process = cam->modes.cloud_post_process;

	sprintf_s(qwa, 256, "CLOUD DETECTION MODE: filter %d, interval time: %d s.", cam->filter, cam->interval);
	WriteMessage(outTextBox, qwa);

	if (cam->intensity_control == 0)
	{
		sprintf_s(qwa, 256, "CLOUD DETECTION MODE: Camera program should be on AUTO when intensity control is OFF");
		WriteMessage(outTextBox, qwa);
	}

	if (cam->intensity_control == 1)
	{
		sprintf_s(qwa, 256, "CLOUD DETECTION MODE: Camera program should be on MANUAL when intensity control is ON");
		WriteMessage(outTextBox, qwa);
	}

	// OK return
	retVal = 0;

	return(retVal);
}

/*int initPolMode(MY_FORM_ARG_VAR) {
	int retVal;
	char qwa[1024];

	// Update values
	cam->interval = cam->modes.pol_interval;
	cam->filter = cam->modes.pol_filter;
	cam->intensity.max_intensity = cam->modes.pol_max_intensity;
	cam->intensity.min_intensity = cam->modes.pol_min_intensity;
	cam->intensity_control = cam->modes.pol_intensity_control;
	cam->sys.sun_elevation_max = cam->modes.normal_sun_elev_max;
	cam->sys.moon_elevation_max = cam->modes.normal_moon_elev_max;

	sprintf_s(qwa, 256, "POLARIZATION MODE: filter %d, interval time: %d s.", cam->filter, cam->interval);
	WriteMessage(outTextBox, qwa);

	// OK return
	retVal = 0;

	return(retVal);
}*/

/*int initNightMode(MY_FORM_ARG_VAR) {
	int retVal;
	char qwa[1024];
	char degt[10];

	// degree symbol
	strcpy_s(degt, "1");
	degt[0] = (char)176;

	// Update values
	cam->interval = cam->modes.night_interval;
	cam->filter = cam->modes.night_filter;
	cam->intensity.max_intensity = cam->modes.night_max_intensity;
	cam->intensity.min_intensity = cam->modes.night_min_intensity;
	cam->intensity_control = cam->modes.night_intensity_control;
	cam->sys.sun_elevation_max = cam->modes.night_sun_elev_max;
	cam->sys.moon_elevation_max = cam->modes.night_moon_elev_max;

	sprintf_s(qwa, 256, "NIGHT MODE: filter %d, interval time: %d s, sun eleveation max: %.2f%s, moon elevation max: %.2f%s. ", 
		cam->filter, cam->interval, cam->sys.sun_elevation_max, degt, cam->sys.moon_elevation_max, degt);
	WriteMessage(outTextBox, qwa);

	// OK return
	retVal = 0;

	return(retVal);
}*/