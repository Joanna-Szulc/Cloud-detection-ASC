/* --------------------------------------------------- */
/*                                                     */
/*          S M A R T M O T O R I O . C                */
/*                                                     */
/*     Smartmotor functions for the uioCam program     */
/* --------------------------------------------------- */

#include "stdafx.h"
#include "include.h"
#include "MyForm.h"
#include <String.h>
#include <stdio.h>
#include <stdlib.h>
//#include "include.h"

//#using <System.dll>

using namespace System;
using namespace System::IO::Ports;

// debug
#include <iostream>
using namespace std;




// ####################################
// smartMototorOpenSerialPort1()
//


int smartMototorOpenSerialPort1(MY_FORM_ARG_VAR)
{
	int retval;

	retval = 0;

	// Set the read/write timeouts to normal
	//comPort1->ReadTimeout = 5000;   // 5 seconds
	//comPort1->WriteTimeout = 5000;  //  5 seconds

	//comPort1->Open();
	WriteMessage(outTextBox, argLine);
	//if (cam->sys.debug_on) WriteMessage(outTextBox, argLine);

	return(retval);
}

// #######################################
// smartMototorCloseSerialPort1()
//

int smartMototorCloseSerialPort1(MY_FORM_ARG_VAR)
{
	int retval;
	retval = 0;

	//comPort1->Close();

	//if (cam->sys.debug_on) WriteMessage(outTextBox, argLine);

	WriteMessage(outTextBox, argLine);

	return(retval);
}

// ############################################
// smartMotorReadResponse()
//
// When the argVal is greater than 0 the function checks if
// the response from the smartmotor is the text in argLine[]
// It reads maximum 32 charcters from the RS-232

int smartMotorReadResponse(MY_FORM_ARG_VAR)
{
	char qwa[1024];
	char qwb[1024];
	int retval;
	bool finish;
	int k;
	int d;

	retval = 0;
	finish = false;
	k = 0;

	strcpy_s(qwa, "\''");

	while (!finish)
	{
		try {
			d = comPort1->ReadChar();
		}
		catch (TimeoutException ^) {
			WriteMessage(outTextBox, "Timeout (5 sec) on reading smartmotor");
			comPort1->DiscardInBuffer();  // clean the rest
			return(retval);
		}
		if (d == 13) {
			finish = true;
		}
		else {
			sprintf_s(qwb, "%c", d);
			strcat_s(qwa, qwb);
			k++;
			if (k > 64) break;
		}
	}

	strcat_s(qwa, "''");

	if (cam->sys.debug_on) WriteMessage(outTextBox, qwa);

	if ((argVal > 0) && (strcmp(qwa, argLine)))
	{
		sprintf_s(qwb, 128, "Unexpected '%s'response from the smartmotor expected '%s'\n",
			qwa, argLine);

		WriteMessage(outTextBox, qwa);
	}

	return(retval);
}

// #####################################
// smartMotorHome()
//

int smartMotorHome(MY_FORM_ARG_VAR)
{
	int retval;
	retval = 0;


	// Set the read/write timeouts longer because HOME the filter wheel is slow
	//comPort1->ReadTimeout = 25000;   // 25 seconds
	//comPort1->WriteTimeout = 15000;  //  |15 seconds

	//comPort1->WriteLine("GOSUB5\n");

	/*if (cam->sys.debug_on) WriteMessage(outTextBox, argLine);

	if (cam->sys.check_smartmotor) {
		strcpy_s(argLine, 32, "''HOME:1''");
		argVal = 1;
	}
	else {
		argVal = 0; // no check
	}

	retval = smartMotorReadResponse(MY_FORM_ARG_FUNC);
	comPort1->DiscardInBuffer(); // the SmartMotor HOME subrutine might give another line, we clear that line
								 // However the data might not be here now so we clear the comPort1 at each smartMotorCheckLightDetector() start

								 // Set the read/write timeouts back to normal
	comPort1->ReadTimeout = 5000;   // 5 seconds
	comPort1->WriteTimeout = 5000;  //  5 seconds
	*/

	WriteMessage(outTextBox, argLine);

	return(retval);
}


// #########################################
// smartMotorOpenShutter()
//

int smartMotorOpenShutter(MY_FORM_ARG_VAR)
{
	int retval;
	retval = 0;

	//comPort1->WriteLine("d=1\n");
	//comPort1->WriteLine("GOSUB1\n");

	//if (cam->sys.debug_on) WriteMessage(outTextBox, argLine);

	/*if (cam->sys.check_smartmotor) {
		strcpy_s(argLine, 32, "''SHTR:1''");
		argVal = 1;
	}
	else {
		argVal = 0; // no check
	}

	retval = smartMotorReadResponse(MY_FORM_ARG_FUNC);
	*/

	WriteMessage(outTextBox, argLine);

	return(retval);
}

// ########################################
// smartMotorCloseShutter
//

int smartMotorCloseShutter(MY_FORM_ARG_VAR)
{
	int retval;
	retval = 0;
	/*
	comPort1->WriteLine("d=0\n");
	comPort1->WriteLine("GOSUB1\n");

	if (cam->sys.debug_on) WriteMessage(outTextBox, argLine);

	if (cam->sys.check_smartmotor) {
		strcpy_s(argLine, 32, "''SHTR:0''");
		argVal = 1;
	}
	else {
		argVal = 0; // no check
	}


	retval = smartMotorReadResponse(MY_FORM_ARG_FUNC);
	*/

	WriteMessage(outTextBox, argLine);

	return(retval);
}

// #########################################
// smartMotorSelectFilter()
//

int smartMotorSelectFilter(MY_FORM_ARG_VAR)
{
	System::String^ myString;
	int retval;
	char qwa[1024];

	retval = 0;

	sprintf_s(qwa, 64, "g=%d\n", argVal);
	myString = gcnew System::String(qwa);
/*
	comPort1->WriteLine(myString);
	comPort1->WriteLine("GOSUB4\n");

	sprintf_s(qwa, 64, "Select filter %d  (%s)", argVal, cam->info.filtername[argVal - 1]);

	if (cam->sys.debug_on) WriteMessage(outTextBox, qwa);

	argVal = 0;

	retval = smartMotorReadResponse(MY_FORM_ARG_FUNC);
	*/

	WriteMessage(outTextBox, argLine);

	return(retval);
}

// #########################################
// smartMotorFullTurn()
//
int smartMotorFullTurn(MY_FORM_ARG_VAR)
{
	// Starting in filter pos 1, doing the trip 2, 3, 4, 5, 1
	// from there, making a full turn of the filter wheel.
	//-- (can be implemented smoother, but this is the easiest fix)

	System::String^ myString;
	int retval;
	char qwa[1024];
	int argTmp;

	retval = 0;
	/*
	sprintf_s(qwa, 64, "Turning filter wheel.");
	if (cam->sys.debug_on) WriteMessage(outTextBox, qwa);

	// Start the trip to filter pos 2
	argVal = 2;
	while (argVal <= 5)
	{
		argTmp = argVal;
		sprintf_s(qwa, 64, "g=%d\n", argVal);
		myString = gcnew System::String(qwa);

		comPort1->WriteLine(myString);
		comPort1->WriteLine("GOSUB4\n");

		argVal = 0;
		retval = smartMotorReadResponse(MY_FORM_ARG_FUNC);

		argVal = argTmp + 1;
	}

	// Go back to filter pos 1
	argVal = 1;
	sprintf_s(qwa, 64, "g=%d\n", argVal);
	myString = gcnew System::String(qwa);

	comPort1->WriteLine(myString);
	comPort1->WriteLine("GOSUB4\n");

	argVal = 0;
	retval = smartMotorReadResponse(MY_FORM_ARG_FUNC);
	*/

	WriteMessage(outTextBox, argLine);

	return(retval);
}
