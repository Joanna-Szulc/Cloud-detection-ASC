#include "stdafx.h"
#include "MyForm.h"

/* This application was originally made for the University of Oslo (UiO).
   The system was then used for observation of the aurora.
   It was modified to be used for daytime operation and cloud observation
   in 2018 for Andøya Space Center (ASC).
   It was further modified to version 2.1 in 2020 for daytime and nighttime
   cloud observation and detection for Andoya Space Center (ASC) as part of
   the All-Sky system. More information in the manual of the All-Sky system
   and internship journal from 2020.*/

using namespace uioCamv20;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Application::Run(gcnew MyForm());
	return 0;
}