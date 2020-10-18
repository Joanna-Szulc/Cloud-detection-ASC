#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <wchar.h>
#include "include.h"
#include "global.h"
#include <Windows.h>

// debug
#include <iostream>
#include <string> 
using namespace std;

namespace uioCamv20 {

	using namespace System;
	using namespace System::Globalization;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  shutterGroup;
	protected:
	private: System::Windows::Forms::RadioButton^  closeShutter;
	private: System::Windows::Forms::RadioButton^  openShutter;

	private: System::Windows::Forms::Button^  homeButton;

	private: System::Windows::Forms::GroupBox^  filterGroup;
	private: System::Windows::Forms::RadioButton^  filter5;
	private: System::Windows::Forms::RadioButton^  filter4;
	private: System::Windows::Forms::RadioButton^  filter3;
	private: System::Windows::Forms::RadioButton^  filter2;
	private: System::Windows::Forms::RadioButton^  filter1;

	private: System::Windows::Forms::Button^  openSmartmtrButton;
	private: System::Windows::Forms::Button^  closeSmartmtrButton;
	private: System::Windows::Forms::GroupBox^  groupSmartmtr;
	public: System::IO::Ports::SerialPort^  serialPort1;

	public: System::Windows::Forms::TextBox^  outputText;

	private: System::Windows::Forms::Button^  endButton;

	private: System::Windows::Forms::GroupBox^  groupCamera;
	private: System::Windows::Forms::Button^  initCameraButton;
	private: System::Windows::Forms::Button^  acquireButton;
	private: System::Windows::Forms::Button^  exivButton;


	private: System::Windows::Forms::Label^  currentTimeLabel;
	private: System::Windows::Forms::Timer^  secTimer;
	private: System::Windows::Forms::Timer^  minTimer;

	private: System::Windows::Forms::Label^  statusLabel;



	private: System::Windows::Forms::Label^  astroLabel;

	public: System::Windows::Forms::TextBox^  setupText;

	private: System::Windows::Forms::GroupBox^  debugGroup;
	private: System::Windows::Forms::RadioButton^  debugOff;
	private: System::Windows::Forms::RadioButton^  debugOn;

	private: System::Windows::Forms::GroupBox^  logGroup;
	private: System::Windows::Forms::RadioButton^  logOff;
	private: System::Windows::Forms::RadioButton^  logOn;

	private: System::Windows::Forms::Button^  readConfigButton;
	private: System::Windows::Forms::Timer^  endTimer;

	private: System::Windows::Forms::GroupBox^  manualGroup;
	private: System::Windows::Forms::RadioButton^  manualButton;
	private: System::Windows::Forms::RadioButton^  autoButton;

	private: System::Windows::Forms::Button^  closeCameraButton;

	private: System::Windows::Forms::Timer^  cameraShutdownTimer;

	private: System::Windows::Forms::GroupBox^  infoGroup;
	private: System::Windows::Forms::RadioButton^  infoOff;
	private: System::Windows::Forms::RadioButton^  infoOn;
	private: System::Windows::Forms::Button^  fullTurn;

	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Button^  editConfig;
	private: System::Windows::Forms::Button^  editTime;
	private: System::Windows::Forms::Button^  openReadMe;
	private: System::Windows::Forms::GroupBox^  intensityGroup;
	private: System::Windows::Forms::RadioButton^  intensityOff;
	private: System::Windows::Forms::RadioButton^  intensityOn;
	private: System::Windows::Forms::GroupBox^  postprocessGroup;
	private: System::Windows::Forms::RadioButton^  postprocessOff;
	private: System::Windows::Forms::RadioButton^  postprocessOn;
	private: System::Windows::Forms::GroupBox^  modeGroup;
	private: System::Windows::Forms::RadioButton^  cloudMode;
	private: System::Windows::Forms::RadioButton^  normalMode;


	// ver. 2.1 has only two modes: Normal and Cloud Detection
	// but Cloud Detection automatically changes settings between
	// daytime and nightime. All code concerning Polarisation and
	// Night mode are commented instead of deleted.
	//private: System::Windows::Forms::RadioButton^  polMode;
	//private: System::Windows::Forms::RadioButton^  nightMode;


	public: System::Diagnostics::Process^ process;

#pragma region Windows Form Designer generated code

			void InitializeComponent(void)
			{
				this->components = (gcnew System::ComponentModel::Container());
				this->shutterGroup = (gcnew System::Windows::Forms::GroupBox());
				this->closeShutter = (gcnew System::Windows::Forms::RadioButton());
				this->openShutter = (gcnew System::Windows::Forms::RadioButton());
				this->homeButton = (gcnew System::Windows::Forms::Button());
				this->filterGroup = (gcnew System::Windows::Forms::GroupBox());
				this->filter5 = (gcnew System::Windows::Forms::RadioButton());
				this->filter4 = (gcnew System::Windows::Forms::RadioButton());
				this->filter3 = (gcnew System::Windows::Forms::RadioButton());
				this->filter2 = (gcnew System::Windows::Forms::RadioButton());
				this->filter1 = (gcnew System::Windows::Forms::RadioButton());
				this->openSmartmtrButton = (gcnew System::Windows::Forms::Button());
				this->closeSmartmtrButton = (gcnew System::Windows::Forms::Button());
				this->groupSmartmtr = (gcnew System::Windows::Forms::GroupBox());
				this->fullTurn = (gcnew System::Windows::Forms::Button());
				this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
				this->outputText = (gcnew System::Windows::Forms::TextBox());
				this->endButton = (gcnew System::Windows::Forms::Button());
				this->groupCamera = (gcnew System::Windows::Forms::GroupBox());
				this->exivButton = (gcnew System::Windows::Forms::Button());
				this->modeGroup = (gcnew System::Windows::Forms::GroupBox());
				this->cloudMode = (gcnew System::Windows::Forms::RadioButton());
				this->normalMode = (gcnew System::Windows::Forms::RadioButton());
				this->closeCameraButton = (gcnew System::Windows::Forms::Button());
				this->acquireButton = (gcnew System::Windows::Forms::Button());
				this->initCameraButton = (gcnew System::Windows::Forms::Button());
				this->currentTimeLabel = (gcnew System::Windows::Forms::Label());
				this->secTimer = (gcnew System::Windows::Forms::Timer(this->components));
				this->minTimer = (gcnew System::Windows::Forms::Timer(this->components));
				this->statusLabel = (gcnew System::Windows::Forms::Label());
				this->astroLabel = (gcnew System::Windows::Forms::Label());
				this->setupText = (gcnew System::Windows::Forms::TextBox());
				this->debugGroup = (gcnew System::Windows::Forms::GroupBox());
				this->debugOff = (gcnew System::Windows::Forms::RadioButton());
				this->debugOn = (gcnew System::Windows::Forms::RadioButton());
				this->logGroup = (gcnew System::Windows::Forms::GroupBox());
				this->logOff = (gcnew System::Windows::Forms::RadioButton());
				this->logOn = (gcnew System::Windows::Forms::RadioButton());
				this->readConfigButton = (gcnew System::Windows::Forms::Button());
				this->endTimer = (gcnew System::Windows::Forms::Timer(this->components));
				this->manualGroup = (gcnew System::Windows::Forms::GroupBox());
				this->manualButton = (gcnew System::Windows::Forms::RadioButton());
				this->autoButton = (gcnew System::Windows::Forms::RadioButton());
				this->cameraShutdownTimer = (gcnew System::Windows::Forms::Timer(this->components));
				this->infoGroup = (gcnew System::Windows::Forms::GroupBox());
				this->infoOff = (gcnew System::Windows::Forms::RadioButton());
				this->infoOn = (gcnew System::Windows::Forms::RadioButton());
				this->editConfig = (gcnew System::Windows::Forms::Button());
				this->editTime = (gcnew System::Windows::Forms::Button());
				this->openReadMe = (gcnew System::Windows::Forms::Button());
				this->intensityGroup = (gcnew System::Windows::Forms::GroupBox());
				this->intensityOff = (gcnew System::Windows::Forms::RadioButton());
				this->intensityOn = (gcnew System::Windows::Forms::RadioButton());
				this->postprocessGroup = (gcnew System::Windows::Forms::GroupBox());
				this->postprocessOff = (gcnew System::Windows::Forms::RadioButton());
				this->postprocessOn = (gcnew System::Windows::Forms::RadioButton());
				this->shutterGroup->SuspendLayout();
				this->filterGroup->SuspendLayout();
				this->groupSmartmtr->SuspendLayout();
				this->groupCamera->SuspendLayout();
				this->modeGroup->SuspendLayout();
				this->debugGroup->SuspendLayout();
				this->logGroup->SuspendLayout();
				this->manualGroup->SuspendLayout();
				this->infoGroup->SuspendLayout();
				this->intensityGroup->SuspendLayout();
				this->postprocessGroup->SuspendLayout();
				this->SuspendLayout();
				// 
				// shutterGroup
				// 
				this->shutterGroup->Controls->Add(this->closeShutter);
				this->shutterGroup->Controls->Add(this->openShutter);
				this->shutterGroup->Enabled = false;
				this->shutterGroup->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->shutterGroup->Location = System::Drawing::Point(11, 29);
				this->shutterGroup->Margin = System::Windows::Forms::Padding(4);
				this->shutterGroup->Name = L"shutterGroup";
				this->shutterGroup->Padding = System::Windows::Forms::Padding(4);
				this->shutterGroup->Size = System::Drawing::Size(101, 76);
				this->shutterGroup->TabIndex = 5;
				this->shutterGroup->TabStop = false;
				this->shutterGroup->Text = L"Shutter";
				// 
				// closeShutter
				// 
				this->closeShutter->AutoSize = true;
				this->closeShutter->Checked = true;
				this->closeShutter->Location = System::Drawing::Point(8, 44);
				this->closeShutter->Margin = System::Windows::Forms::Padding(4);
				this->closeShutter->Name = L"closeShutter";
				this->closeShutter->Size = System::Drawing::Size(73, 22);
				this->closeShutter->TabIndex = 1;
				this->closeShutter->TabStop = true;
				this->closeShutter->Text = L"Close";
				this->closeShutter->UseVisualStyleBackColor = true;
				this->closeShutter->CheckedChanged += gcnew System::EventHandler(this, &MyForm::closeShutter_CheckedChanged);
				// 
				// openShutter
				// 
				this->openShutter->AutoSize = true;
				this->openShutter->Location = System::Drawing::Point(7, 22);
				this->openShutter->Margin = System::Windows::Forms::Padding(4);
				this->openShutter->Name = L"openShutter";
				this->openShutter->Size = System::Drawing::Size(69, 22);
				this->openShutter->TabIndex = 0;
				this->openShutter->Text = L"Open";
				this->openShutter->UseVisualStyleBackColor = true;
				this->openShutter->CheckedChanged += gcnew System::EventHandler(this, &MyForm::openShutter_CheckedChanged);
				// 
				// homeButton
				// 
				this->homeButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				this->homeButton->Enabled = false;
				this->homeButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->homeButton->Location = System::Drawing::Point(11, 150);
				this->homeButton->Margin = System::Windows::Forms::Padding(4);
				this->homeButton->Name = L"homeButton";
				this->homeButton->Size = System::Drawing::Size(101, 30);
				this->homeButton->TabIndex = 7;
				this->homeButton->Text = L"Home";
				this->homeButton->UseVisualStyleBackColor = true;
				this->homeButton->Click += gcnew System::EventHandler(this, &MyForm::homeButton_Click);
				// 
				// filterGroup
				// 
				this->filterGroup->Controls->Add(this->filter5);
				this->filterGroup->Controls->Add(this->filter4);
				this->filterGroup->Controls->Add(this->filter3);
				this->filterGroup->Controls->Add(this->filter2);
				this->filterGroup->Controls->Add(this->filter1);
				this->filterGroup->Enabled = false;
				this->filterGroup->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->filterGroup->Location = System::Drawing::Point(119, 29);
				this->filterGroup->Margin = System::Windows::Forms::Padding(4);
				this->filterGroup->Name = L"filterGroup";
				this->filterGroup->Padding = System::Windows::Forms::Padding(4);
				this->filterGroup->Size = System::Drawing::Size(100, 149);
				this->filterGroup->TabIndex = 8;
				this->filterGroup->TabStop = false;
				this->filterGroup->Text = L"Filter";
				// 
				// filter5
				// 
				this->filter5->AutoSize = true;
				this->filter5->Location = System::Drawing::Point(14, 121);
				this->filter5->Margin = System::Windows::Forms::Padding(4);
				this->filter5->Name = L"filter5";
				this->filter5->Size = System::Drawing::Size(38, 22);
				this->filter5->TabIndex = 4;
				this->filter5->TabStop = true;
				this->filter5->Text = L"5";
				this->filter5->UseVisualStyleBackColor = true;
				this->filter5->CheckedChanged += gcnew System::EventHandler(this, &MyForm::filter5_CheckedChanged);
				// 
				// filter4
				// 
				this->filter4->AutoSize = true;
				this->filter4->Location = System::Drawing::Point(14, 96);
				this->filter4->Margin = System::Windows::Forms::Padding(4);
				this->filter4->Name = L"filter4";
				this->filter4->Size = System::Drawing::Size(38, 22);
				this->filter4->TabIndex = 3;
				this->filter4->TabStop = true;
				this->filter4->Text = L"4";
				this->filter4->UseVisualStyleBackColor = true;
				this->filter4->CheckedChanged += gcnew System::EventHandler(this, &MyForm::filter4_CheckedChanged);
				// 
				// filter3
				// 
				this->filter3->AutoSize = true;
				this->filter3->Location = System::Drawing::Point(14, 71);
				this->filter3->Margin = System::Windows::Forms::Padding(4);
				this->filter3->Name = L"filter3";
				this->filter3->Size = System::Drawing::Size(38, 22);
				this->filter3->TabIndex = 2;
				this->filter3->TabStop = true;
				this->filter3->Text = L"3";
				this->filter3->UseVisualStyleBackColor = true;
				this->filter3->CheckedChanged += gcnew System::EventHandler(this, &MyForm::filter3_CheckedChanged);
				// 
				// filter2
				// 
				this->filter2->AutoSize = true;
				this->filter2->Location = System::Drawing::Point(14, 46);
				this->filter2->Margin = System::Windows::Forms::Padding(4);
				this->filter2->Name = L"filter2";
				this->filter2->Size = System::Drawing::Size(38, 22);
				this->filter2->TabIndex = 1;
				this->filter2->TabStop = true;
				this->filter2->Text = L"2";
				this->filter2->UseVisualStyleBackColor = true;
				this->filter2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::filter2_CheckedChanged);
				// 
				// filter1
				// 
				this->filter1->AutoSize = true;
				this->filter1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->filter1->Location = System::Drawing::Point(14, 20);
				this->filter1->Margin = System::Windows::Forms::Padding(4);
				this->filter1->Name = L"filter1";
				this->filter1->Size = System::Drawing::Size(40, 24);
				this->filter1->TabIndex = 0;
				this->filter1->TabStop = true;
				this->filter1->Text = L"1";
				this->filter1->UseVisualStyleBackColor = true;
				this->filter1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::filter1_CheckedChanged);
				// 
				// openSmartmtrButton
				// 
				this->openSmartmtrButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->openSmartmtrButton->Location = System::Drawing::Point(11, 115);
				this->openSmartmtrButton->Margin = System::Windows::Forms::Padding(4);
				this->openSmartmtrButton->Name = L"openSmartmtrButton";
				this->openSmartmtrButton->Size = System::Drawing::Size(101, 30);
				this->openSmartmtrButton->TabIndex = 9;
				this->openSmartmtrButton->Text = L" Open";
				this->openSmartmtrButton->UseVisualStyleBackColor = true;
				this->openSmartmtrButton->Click += gcnew System::EventHandler(this, &MyForm::openSmartmtrButton_Click);
				// 
				// closeSmartmtrButton
				// 
				this->closeSmartmtrButton->Enabled = false;
				this->closeSmartmtrButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
					System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				this->closeSmartmtrButton->Location = System::Drawing::Point(11, 183);
				this->closeSmartmtrButton->Margin = System::Windows::Forms::Padding(4);
				this->closeSmartmtrButton->Name = L"closeSmartmtrButton";
				this->closeSmartmtrButton->Size = System::Drawing::Size(101, 30);
				this->closeSmartmtrButton->TabIndex = 10;
				this->closeSmartmtrButton->Text = L"Close";
				this->closeSmartmtrButton->UseVisualStyleBackColor = true;
				this->closeSmartmtrButton->Click += gcnew System::EventHandler(this, &MyForm::closeSmartmtrButton_Click);
				// 
				// groupSmartmtr
				// 
				this->groupSmartmtr->Controls->Add(this->fullTurn);
				this->groupSmartmtr->Controls->Add(this->filterGroup);
				this->groupSmartmtr->Controls->Add(this->closeSmartmtrButton);
				this->groupSmartmtr->Controls->Add(this->shutterGroup);
				this->groupSmartmtr->Controls->Add(this->openSmartmtrButton);
				this->groupSmartmtr->Controls->Add(this->homeButton);
				this->groupSmartmtr->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->groupSmartmtr->Location = System::Drawing::Point(15, 465);
				this->groupSmartmtr->Margin = System::Windows::Forms::Padding(4);
				this->groupSmartmtr->Name = L"groupSmartmtr";
				this->groupSmartmtr->Padding = System::Windows::Forms::Padding(4);
				this->groupSmartmtr->Size = System::Drawing::Size(238, 222);
				this->groupSmartmtr->TabIndex = 11;
				this->groupSmartmtr->TabStop = false;
				this->groupSmartmtr->Text = L"SMARTMOTOR";
				this->groupSmartmtr->Enter += gcnew System::EventHandler(this, &MyForm::groupSmartmtr_Enter);
				// 
				// fullTurn
				// 
				this->fullTurn->Enabled = false;
				this->fullTurn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->fullTurn->Location = System::Drawing::Point(118, 183);
				this->fullTurn->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				this->fullTurn->Name = L"fullTurn";
				this->fullTurn->Size = System::Drawing::Size(101, 30);
				this->fullTurn->TabIndex = 11;
				this->fullTurn->Text = L"Full turn";
				this->fullTurn->UseVisualStyleBackColor = true;
				this->fullTurn->Click += gcnew System::EventHandler(this, &MyForm::fullTurn_Click);
				// 
				// serialPort1
				// 
				this->serialPort1->PortName = L"COM2";
				// 
				// outputText
				// 
				this->outputText->Location = System::Drawing::Point(8, 187);
				this->outputText->Margin = System::Windows::Forms::Padding(4);
				this->outputText->MaxLength = 256000;
				this->outputText->Multiline = true;
				this->outputText->Name = L"outputText";
				this->outputText->ScrollBars = System::Windows::Forms::ScrollBars::Both;
				this->outputText->Size = System::Drawing::Size(833, 271);
				this->outputText->TabIndex = 12;
				this->outputText->TextChanged += gcnew System::EventHandler(this, &MyForm::outputText_TextChanged);
				// 
				// endButton
				// 
				this->endButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				this->endButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->endButton->Location = System::Drawing::Point(682, 641);
				this->endButton->Margin = System::Windows::Forms::Padding(4);
				this->endButton->Name = L"endButton";
				this->endButton->Size = System::Drawing::Size(133, 46);
				this->endButton->TabIndex = 13;
				this->endButton->Text = L"End";
				this->endButton->UseVisualStyleBackColor = true;
				this->endButton->Click += gcnew System::EventHandler(this, &MyForm::endButton_Click);
				// 
				// groupCamera
				// 
				this->groupCamera->Controls->Add(this->exivButton);
				this->groupCamera->Controls->Add(this->modeGroup);
				this->groupCamera->Controls->Add(this->closeCameraButton);
				this->groupCamera->Controls->Add(this->acquireButton);
				this->groupCamera->Controls->Add(this->initCameraButton);
				this->groupCamera->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->groupCamera->Location = System::Drawing::Point(260, 465);
				this->groupCamera->Margin = System::Windows::Forms::Padding(4);
				this->groupCamera->Name = L"groupCamera";
				this->groupCamera->Padding = System::Windows::Forms::Padding(4);
				this->groupCamera->Size = System::Drawing::Size(390, 225);
				this->groupCamera->TabIndex = 14;
				this->groupCamera->TabStop = false;
				this->groupCamera->Text = L"CAMERA";
				this->groupCamera->Enter += gcnew System::EventHandler(this, &MyForm::groupCamera_Enter);
				// 
				// exivButton
				// 
				this->exivButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->exivButton->Location = System::Drawing::Point(189, 164);
				this->exivButton->Margin = System::Windows::Forms::Padding(4);
				this->exivButton->Name = L"exivButton";
				this->exivButton->Size = System::Drawing::Size(178, 35);
				this->exivButton->TabIndex = 31;
				this->exivButton->Text = L"Last image info";
				this->exivButton->UseVisualStyleBackColor = true;
				this->exivButton->Click += gcnew System::EventHandler(this, &MyForm::exivButton_Click);
				// 
				// modeGroup
				// 
				this->modeGroup->Controls->Add(this->cloudMode);
				this->modeGroup->Controls->Add(this->normalMode);
				this->modeGroup->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->modeGroup->Location = System::Drawing::Point(189, 38);
				this->modeGroup->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				this->modeGroup->Name = L"modeGroup";
				this->modeGroup->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
				this->modeGroup->Size = System::Drawing::Size(178, 98);
				this->modeGroup->TabIndex = 30;
				this->modeGroup->TabStop = false;
				this->modeGroup->Text = L"Modes";
				// 
				// cloudMode
				// 
				this->cloudMode->AutoSize = true;
				this->cloudMode->Location = System::Drawing::Point(10, 64);
				this->cloudMode->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				this->cloudMode->Name = L"cloudMode";
				this->cloudMode->Size = System::Drawing::Size(147, 22);
				this->cloudMode->TabIndex = 1;
				this->cloudMode->TabStop = true;
				this->cloudMode->Text = L"Cloud detection";
				this->cloudMode->UseVisualStyleBackColor = true;
				this->cloudMode->CheckedChanged += gcnew System::EventHandler(this, &MyForm::cloudMode_CheckedChanged);
				// 
				// normalMode
				// 
				this->normalMode->AutoSize = true;
				this->normalMode->Location = System::Drawing::Point(10, 32);
				this->normalMode->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				this->normalMode->Name = L"normalMode";
				this->normalMode->Size = System::Drawing::Size(84, 22);
				this->normalMode->TabIndex = 0;
				this->normalMode->TabStop = true;
				this->normalMode->Text = L"Normal";
				this->normalMode->UseVisualStyleBackColor = true;
				this->normalMode->CheckedChanged += gcnew System::EventHandler(this, &MyForm::normalMode_CheckedChanged);
				// 
				// closeCameraButton
				// 
				this->closeCameraButton->Enabled = false;
				this->closeCameraButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->closeCameraButton->Location = System::Drawing::Point(12, 83);
				this->closeCameraButton->Margin = System::Windows::Forms::Padding(4);
				this->closeCameraButton->Name = L"closeCameraButton";
				this->closeCameraButton->Size = System::Drawing::Size(158, 35);
				this->closeCameraButton->TabIndex = 24;
				this->closeCameraButton->Text = L"Close Remote";
				this->closeCameraButton->UseVisualStyleBackColor = true;
				this->closeCameraButton->Click += gcnew System::EventHandler(this, &MyForm::closeCameraButton_Click);
				// 
				// acquireButton
				// 
				this->acquireButton->Enabled = false;
				this->acquireButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->acquireButton->Location = System::Drawing::Point(12, 148);
				this->acquireButton->Margin = System::Windows::Forms::Padding(4);
				this->acquireButton->Name = L"acquireButton";
				this->acquireButton->Size = System::Drawing::Size(158, 35);
				this->acquireButton->TabIndex = 1;
				this->acquireButton->Text = L"Get image";
				this->acquireButton->UseVisualStyleBackColor = true;
				this->acquireButton->Click += gcnew System::EventHandler(this, &MyForm::acquireButton_Click);
				// 
				// initCameraButton
				// 
				this->initCameraButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->initCameraButton->Location = System::Drawing::Point(12, 38);
				this->initCameraButton->Margin = System::Windows::Forms::Padding(4);
				this->initCameraButton->Name = L"initCameraButton";
				this->initCameraButton->Size = System::Drawing::Size(158, 35);
				this->initCameraButton->TabIndex = 0;
				this->initCameraButton->Text = L"Open Remote";
				this->initCameraButton->UseVisualStyleBackColor = true;
				this->initCameraButton->Click += gcnew System::EventHandler(this, &MyForm::initCameraButton_Click);
				// 
				// currentTimeLabel
				// 
				this->currentTimeLabel->AutoSize = true;
				this->currentTimeLabel->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->currentTimeLabel->Location = System::Drawing::Point(11, 2);
				this->currentTimeLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				this->currentTimeLabel->Name = L"currentTimeLabel";
				this->currentTimeLabel->Size = System::Drawing::Size(185, 23);
				this->currentTimeLabel->TabIndex = 16;
				this->currentTimeLabel->Text = L"2000-01-01 00:00:00 UT";
				this->currentTimeLabel->Click += gcnew System::EventHandler(this, &MyForm::currentTimeLabel_Click);
				// 
				// secTimer
				// 
				this->secTimer->Enabled = true;
				this->secTimer->Interval = 1000;
				this->secTimer->Tick += gcnew System::EventHandler(this, &MyForm::secTimer_Tick);
				// 
				// minTimer
				// 
				this->minTimer->Interval = 60000;
				this->minTimer->Tick += gcnew System::EventHandler(this, &MyForm::minTimer_Tick);
				// 
				// statusLabel
				// 
				this->statusLabel->AutoSize = true;
				this->statusLabel->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->statusLabel->ForeColor = System::Drawing::Color::Black;
				this->statusLabel->Location = System::Drawing::Point(201, 2);
				this->statusLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				this->statusLabel->Name = L"statusLabel";
				this->statusLabel->Size = System::Drawing::Size(340, 23);
				this->statusLabel->TabIndex = 17;
				this->statusLabel->Text = L"program is waiting on next minute to initiate";
				this->statusLabel->Click += gcnew System::EventHandler(this, &MyForm::statusLabel_Click);
				// 
				// astroLabel
				// 
				this->astroLabel->AutoSize = true;
				this->astroLabel->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->astroLabel->ForeColor = System::Drawing::Color::Black;
				this->astroLabel->Location = System::Drawing::Point(11, 26);
				this->astroLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				this->astroLabel->Name = L"astroLabel";
				this->astroLabel->Size = System::Drawing::Size(259, 23);
				this->astroLabel->TabIndex = 18;
				this->astroLabel->Text = L"current SUN and MOON elevation";
				// 
				// setupText
				// 
				this->setupText->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
					static_cast<System::Int32>(static_cast<System::Byte>(224)));
				this->setupText->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->setupText->ForeColor = System::Drawing::Color::DimGray;
				this->setupText->Location = System::Drawing::Point(8, 51);
				this->setupText->Margin = System::Windows::Forms::Padding(4);
				this->setupText->Multiline = true;
				this->setupText->Name = L"setupText";
				this->setupText->ReadOnly = true;
				this->setupText->Size = System::Drawing::Size(833, 128);
				this->setupText->TabIndex = 19;
				this->setupText->TextChanged += gcnew System::EventHandler(this, &MyForm::setupText_TextChanged);
				// 
				// debugGroup
				// 
				this->debugGroup->Controls->Add(this->debugOff);
				this->debugGroup->Controls->Add(this->debugOn);
				this->debugGroup->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->debugGroup->Location = System::Drawing::Point(125, 696);
				this->debugGroup->Margin = System::Windows::Forms::Padding(4);
				this->debugGroup->Name = L"debugGroup";
				this->debugGroup->Padding = System::Windows::Forms::Padding(4);
				this->debugGroup->Size = System::Drawing::Size(93, 76);
				this->debugGroup->TabIndex = 20;
				this->debugGroup->TabStop = false;
				this->debugGroup->Text = L"Debug";
				// 
				// debugOff
				// 
				this->debugOff->AutoSize = true;
				this->debugOff->Location = System::Drawing::Point(7, 46);
				this->debugOff->Margin = System::Windows::Forms::Padding(4);
				this->debugOff->Name = L"debugOff";
				this->debugOff->Size = System::Drawing::Size(49, 22);
				this->debugOff->TabIndex = 1;
				this->debugOff->TabStop = true;
				this->debugOff->Text = L"off\r\n";
				this->debugOff->UseVisualStyleBackColor = true;
				this->debugOff->CheckedChanged += gcnew System::EventHandler(this, &MyForm::debugOff_CheckedChanged);
				// 
				// debugOn
				// 
				this->debugOn->AutoSize = true;
				this->debugOn->Location = System::Drawing::Point(7, 22);
				this->debugOn->Margin = System::Windows::Forms::Padding(4);
				this->debugOn->Name = L"debugOn";
				this->debugOn->Size = System::Drawing::Size(48, 22);
				this->debugOn->TabIndex = 0;
				this->debugOn->TabStop = true;
				this->debugOn->Text = L"on\r\n";
				this->debugOn->UseVisualStyleBackColor = true;
				this->debugOn->CheckedChanged += gcnew System::EventHandler(this, &MyForm::debugOn_CheckedChanged);
				// 
				// logGroup
				// 
				this->logGroup->Controls->Add(this->logOff);
				this->logGroup->Controls->Add(this->logOn);
				this->logGroup->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->logGroup->Location = System::Drawing::Point(226, 696);
				this->logGroup->Margin = System::Windows::Forms::Padding(4);
				this->logGroup->Name = L"logGroup";
				this->logGroup->Padding = System::Windows::Forms::Padding(4);
				this->logGroup->Size = System::Drawing::Size(91, 76);
				this->logGroup->TabIndex = 21;
				this->logGroup->TabStop = false;
				this->logGroup->Text = L"Log";
				// 
				// logOff
				// 
				this->logOff->AutoSize = true;
				this->logOff->Location = System::Drawing::Point(5, 46);
				this->logOff->Margin = System::Windows::Forms::Padding(4);
				this->logOff->Name = L"logOff";
				this->logOff->Size = System::Drawing::Size(49, 22);
				this->logOff->TabIndex = 1;
				this->logOff->TabStop = true;
				this->logOff->Text = L"off";
				this->logOff->UseVisualStyleBackColor = true;
				this->logOff->CheckedChanged += gcnew System::EventHandler(this, &MyForm::logOff_CheckedChanged);
				// 
				// logOn
				// 
				this->logOn->AutoSize = true;
				this->logOn->Location = System::Drawing::Point(5, 22);
				this->logOn->Margin = System::Windows::Forms::Padding(4);
				this->logOn->Name = L"logOn";
				this->logOn->Size = System::Drawing::Size(48, 22);
				this->logOn->TabIndex = 0;
				this->logOn->TabStop = true;
				this->logOn->Text = L"on";
				this->logOn->UseVisualStyleBackColor = true;
				this->logOn->CheckedChanged += gcnew System::EventHandler(this, &MyForm::logOn_CheckedChanged);
				// 
				// readConfigButton
				// 
				this->readConfigButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->readConfigButton->Location = System::Drawing::Point(682, 590);
				this->readConfigButton->Margin = System::Windows::Forms::Padding(4);
				this->readConfigButton->Name = L"readConfigButton";
				this->readConfigButton->Size = System::Drawing::Size(133, 34);
				this->readConfigButton->TabIndex = 23;
				this->readConfigButton->Text = L"Read config";
				this->readConfigButton->UseVisualStyleBackColor = true;
				this->readConfigButton->Click += gcnew System::EventHandler(this, &MyForm::readConfigButton_Click);
				// 
				// endTimer
				// 
				this->endTimer->Interval = 1000;
				this->endTimer->Tick += gcnew System::EventHandler(this, &MyForm::endTimer_Tick);
				// 
				// manualGroup
				// 
				this->manualGroup->Controls->Add(this->manualButton);
				this->manualGroup->Controls->Add(this->autoButton);
				this->manualGroup->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->manualGroup->Location = System::Drawing::Point(15, 696);
				this->manualGroup->Margin = System::Windows::Forms::Padding(4);
				this->manualGroup->Name = L"manualGroup";
				this->manualGroup->Padding = System::Windows::Forms::Padding(4);
				this->manualGroup->Size = System::Drawing::Size(103, 75);
				this->manualGroup->TabIndex = 24;
				this->manualGroup->TabStop = false;
				this->manualGroup->Text = L"Manual";
				// 
				// manualButton
				// 
				this->manualButton->AutoSize = true;
				this->manualButton->Location = System::Drawing::Point(9, 46);
				this->manualButton->Margin = System::Windows::Forms::Padding(4);
				this->manualButton->Name = L"manualButton";
				this->manualButton->Size = System::Drawing::Size(61, 22);
				this->manualButton->TabIndex = 1;
				this->manualButton->TabStop = true;
				this->manualButton->Text = L"man";
				this->manualButton->UseVisualStyleBackColor = true;
				this->manualButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::manualButton_CheckedChanged);
				// 
				// autoButton
				// 
				this->autoButton->AutoSize = true;
				this->autoButton->Location = System::Drawing::Point(9, 22);
				this->autoButton->Margin = System::Windows::Forms::Padding(4);
				this->autoButton->Name = L"autoButton";
				this->autoButton->Size = System::Drawing::Size(62, 22);
				this->autoButton->TabIndex = 0;
				this->autoButton->TabStop = true;
				this->autoButton->Text = L"auto";
				this->autoButton->UseVisualStyleBackColor = true;
				this->autoButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::autoButton_CheckedChanged);
				// 
				// cameraShutdownTimer
				// 
				this->cameraShutdownTimer->Interval = 10000;
				this->cameraShutdownTimer->Tick += gcnew System::EventHandler(this, &MyForm::cameraShutdownTimer_Tick);
				// 
				// infoGroup
				// 
				this->infoGroup->Controls->Add(this->infoOff);
				this->infoGroup->Controls->Add(this->infoOn);
				this->infoGroup->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->infoGroup->Location = System::Drawing::Point(324, 695);
				this->infoGroup->Margin = System::Windows::Forms::Padding(4);
				this->infoGroup->Name = L"infoGroup";
				this->infoGroup->Padding = System::Windows::Forms::Padding(4);
				this->infoGroup->Size = System::Drawing::Size(86, 77);
				this->infoGroup->TabIndex = 25;
				this->infoGroup->TabStop = false;
				this->infoGroup->Text = L"Info";
				// 
				// infoOff
				// 
				this->infoOff->AutoSize = true;
				this->infoOff->Location = System::Drawing::Point(7, 47);
				this->infoOff->Margin = System::Windows::Forms::Padding(4);
				this->infoOff->Name = L"infoOff";
				this->infoOff->Size = System::Drawing::Size(49, 22);
				this->infoOff->TabIndex = 1;
				this->infoOff->TabStop = true;
				this->infoOff->Text = L"off";
				this->infoOff->UseVisualStyleBackColor = true;
				this->infoOff->CheckedChanged += gcnew System::EventHandler(this, &MyForm::infoOff_CheckedChanged);
				// 
				// infoOn
				// 
				this->infoOn->AutoSize = true;
				this->infoOn->Location = System::Drawing::Point(7, 22);
				this->infoOn->Margin = System::Windows::Forms::Padding(4);
				this->infoOn->Name = L"infoOn";
				this->infoOn->Size = System::Drawing::Size(48, 22);
				this->infoOn->TabIndex = 0;
				this->infoOn->TabStop = true;
				this->infoOn->Text = L"on";
				this->infoOn->UseVisualStyleBackColor = true;
				this->infoOn->CheckedChanged += gcnew System::EventHandler(this, &MyForm::infoOn_CheckedChanged);
				// 
				// editConfig
				// 
				this->editConfig->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->editConfig->Location = System::Drawing::Point(657, 475);
				this->editConfig->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				this->editConfig->Name = L"editConfig";
				this->editConfig->Size = System::Drawing::Size(183, 32);
				this->editConfig->TabIndex = 26;
				this->editConfig->Text = L"Edit config.txt";
				this->editConfig->UseVisualStyleBackColor = true;
				this->editConfig->Click += gcnew System::EventHandler(this, &MyForm::editConfig_Click);
				// 
				// editTime
				// 
				this->editTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->editTime->Location = System::Drawing::Point(657, 512);
				this->editTime->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				this->editTime->Name = L"editTime";
				this->editTime->Size = System::Drawing::Size(183, 32);
				this->editTime->TabIndex = 27;
				this->editTime->Text = L"Edit time.txt";
				this->editTime->UseVisualStyleBackColor = true;
				this->editTime->Click += gcnew System::EventHandler(this, &MyForm::editTime_Click);
				// 
				// openReadMe
				// 
				this->openReadMe->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->openReadMe->Location = System::Drawing::Point(657, 551);
				this->openReadMe->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				this->openReadMe->Name = L"openReadMe";
				this->openReadMe->Size = System::Drawing::Size(183, 32);
				this->openReadMe->TabIndex = 28;
				this->openReadMe->Text = L"Open ReadMe.txt";
				this->openReadMe->UseVisualStyleBackColor = true;
				this->openReadMe->Click += gcnew System::EventHandler(this, &MyForm::openReadMe_Click);
				// 
				// intensityGroup
				// 
				this->intensityGroup->Controls->Add(this->intensityOff);
				this->intensityGroup->Controls->Add(this->intensityOn);
				this->intensityGroup->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->intensityGroup->Location = System::Drawing::Point(416, 696);
				this->intensityGroup->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				this->intensityGroup->Name = L"intensityGroup";
				this->intensityGroup->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
				this->intensityGroup->Size = System::Drawing::Size(171, 76);
				this->intensityGroup->TabIndex = 29;
				this->intensityGroup->TabStop = false;
				this->intensityGroup->Text = L"Intensity control";
				// 
				// intensityOff
				// 
				this->intensityOff->AutoSize = true;
				this->intensityOff->Location = System::Drawing::Point(9, 47);
				this->intensityOff->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				this->intensityOff->Name = L"intensityOff";
				this->intensityOff->Size = System::Drawing::Size(49, 22);
				this->intensityOff->TabIndex = 1;
				this->intensityOff->TabStop = true;
				this->intensityOff->Text = L"off";
				this->intensityOff->UseVisualStyleBackColor = true;
				this->intensityOff->CheckedChanged += gcnew System::EventHandler(this, &MyForm::intensityOff_CheckedChanged);
				// 
				// intensityOn
				// 
				this->intensityOn->AutoSize = true;
				this->intensityOn->Location = System::Drawing::Point(9, 23);
				this->intensityOn->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				this->intensityOn->Name = L"intensityOn";
				this->intensityOn->Size = System::Drawing::Size(48, 22);
				this->intensityOn->TabIndex = 0;
				this->intensityOn->TabStop = true;
				this->intensityOn->Text = L"on";
				this->intensityOn->UseVisualStyleBackColor = true;
				this->intensityOn->CheckedChanged += gcnew System::EventHandler(this, &MyForm::intensityOn_CheckedChanged);
				// 
				// postprocessGroup
				// 
				this->postprocessGroup->Controls->Add(this->postprocessOff);
				this->postprocessGroup->Controls->Add(this->postprocessOn);
				this->postprocessGroup->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->postprocessGroup->Location = System::Drawing::Point(593, 696);
				this->postprocessGroup->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				this->postprocessGroup->Name = L"postprocessGroup";
				this->postprocessGroup->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
				this->postprocessGroup->Size = System::Drawing::Size(222, 76);
				this->postprocessGroup->TabIndex = 30;
				this->postprocessGroup->TabStop = false;
				this->postprocessGroup->Text = L"Postprocess";
				// 
				// postprocessOff
				// 
				this->postprocessOff->AutoSize = true;
				this->postprocessOff->Location = System::Drawing::Point(9, 47);
				this->postprocessOff->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				this->postprocessOff->Name = L"postprocessOff";
				this->postprocessOff->Size = System::Drawing::Size(49, 22);
				this->postprocessOff->TabIndex = 1;
				this->postprocessOff->TabStop = true;
				this->postprocessOff->Text = L"off";
				this->postprocessOff->UseVisualStyleBackColor = true;
				this->postprocessOff->CheckedChanged += gcnew System::EventHandler(this, &MyForm::postprocessOff_CheckedChanged);
				// 
				// postprocessOn
				// 
				this->postprocessOn->AutoSize = true;
				this->postprocessOn->Location = System::Drawing::Point(9, 23);
				this->postprocessOn->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				this->postprocessOn->Name = L"postprocessOn";
				this->postprocessOn->Size = System::Drawing::Size(48, 22);
				this->postprocessOn->TabIndex = 0;
				this->postprocessOn->TabStop = true;
				this->postprocessOn->Text = L"on";
				this->postprocessOn->UseVisualStyleBackColor = true;
				this->postprocessOn->CheckedChanged += gcnew System::EventHandler(this, &MyForm::postprocessOn_CheckedChanged);
				// 
				// MyForm
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(852, 794);
				this->Controls->Add(this->postprocessGroup);
				this->Controls->Add(this->intensityGroup);
				this->Controls->Add(this->openReadMe);
				this->Controls->Add(this->editTime);
				this->Controls->Add(this->editConfig);
				this->Controls->Add(this->infoGroup);
				this->Controls->Add(this->manualGroup);
				this->Controls->Add(this->readConfigButton);
				this->Controls->Add(this->logGroup);
				this->Controls->Add(this->debugGroup);
				this->Controls->Add(this->endButton);
				this->Controls->Add(this->setupText);
				this->Controls->Add(this->astroLabel);
				this->Controls->Add(this->statusLabel);
				this->Controls->Add(this->currentTimeLabel);
				this->Controls->Add(this->groupCamera);
				this->Controls->Add(this->outputText);
				this->Controls->Add(this->groupSmartmtr);
				this->Location = System::Drawing::Point(0, -4);
				this->Margin = System::Windows::Forms::Padding(4);
				this->Name = L"MyForm";
				this->Text = L"                                                          u i o C a m   v 2.1";
				this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
				this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
				this->shutterGroup->ResumeLayout(false);
				this->shutterGroup->PerformLayout();
				this->filterGroup->ResumeLayout(false);
				this->filterGroup->PerformLayout();
				this->groupSmartmtr->ResumeLayout(false);
				this->groupCamera->ResumeLayout(false);
				this->modeGroup->ResumeLayout(false);
				this->modeGroup->PerformLayout();
				this->debugGroup->ResumeLayout(false);
				this->debugGroup->PerformLayout();
				this->logGroup->ResumeLayout(false);
				this->logGroup->PerformLayout();
				this->manualGroup->ResumeLayout(false);
				this->manualGroup->PerformLayout();
				this->infoGroup->ResumeLayout(false);
				this->infoGroup->PerformLayout();
				this->intensityGroup->ResumeLayout(false);
				this->intensityGroup->PerformLayout();
				this->postprocessGroup->ResumeLayout(false);
				this->postprocessGroup->PerformLayout();
				this->ResumeLayout(false);
				this->PerformLayout();

			}
#pragma endregion

	private: System::Void openSmartmtrButton_Click(System::Object^  sender, System::EventArgs^  e) {
		// This function opens the RS232 connection to the Smartmotor
		// The read and write timeouts are set in the smartMototorOpenSerialPort1() function (in smartMotorIo.cpp file).
		//
		char argText[1024];
		int argValue;
		int result;

		strcpy_s(argText, "Open RS232");
		argValue = 0;

		if (cam->sys.run_smartmotor) { // True when "RUN_SMARTMOTOR: 1" is set in the ..\etc\config.txt" file
			result = smartMototorOpenSerialPort1(MY_FORM_ARG_CALL);
		}
		openSmartmtrButton->Enabled = false;
		closeSmartmtrButton->Enabled = true;
		homeButton->Enabled = true;
		fullTurn->Enabled = true;
		shutterGroup->Enabled = true;
		filterGroup->Enabled = true;
		// endButton->Enabled = false;

		cam->curr.smartmotorIsOpen = true;
	}

	private: System::Void closeShutter_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		// This function closes the shutter
		//
		char argText[1024];
		int argValue;
		int result;

		strcpy_s(argText, "Close Shutter");
		argValue = 0;

		if (closeShutter->Checked) {
			if (cam->sys.run_smartmotor && cam->curr.smartmotorIsOpen) { // True when "RUN_SMARTMOTOR: 1" is set in the D:\etc\camsetup.txt" file
				result = smartMotorCloseShutter(MY_FORM_ARG_CALL);
			}
			closeSmartmtrButton->Enabled = true;
			// if (cam->curr.manual) cam->curr.shutterIsOpen = false;
		}
		endButton->Enabled = true;
	}
	private: System::Void openShutter_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		// This function opens the shutter
		//
		char argText[1024];
		int argValue;
		int result;

		strcpy_s(argText, "Open Shutter");
		argValue = 0;

		if (openShutter->Checked) {
			if (cam->sys.run_smartmotor && cam->curr.smartmotorIsOpen) {  // True when "RUN_SMARTMOTOR: 1" is set in the D:\etc\camsetup.txt" file
				result = smartMotorOpenShutter(MY_FORM_ARG_CALL);
				closeSmartmtrButton->Enabled = false;
			}
			// if (cam->curr.manual) cam->curr.shutterIsOpen = true;
		}
		// endButton->Enabled = false;
	}

	private: System::Void closeSmartmtrButton_Click(System::Object^  sender, System::EventArgs^  e) {
		// This function closes the RS232 connection to the Smartmotor
		//
		char argText[1024];
		int argValue;
		int result;

		strcpy_s(argText, "Close RS232");
		argValue = 0;

		if (cam->sys.run_smartmotor) {  // True when "RUN_SMARTMOTOR: 1" is set in the ..\etc\config.txt" file

			closeShutter->Checked = true; // Close shutter
			cam->curr.shutterIsOpen = false;

			result = smartMototorCloseSerialPort1(MY_FORM_ARG_CALL);
		}
		cam->curr.smartmotorIsOpen = false;

		openSmartmtrButton->Enabled = true;
		closeSmartmtrButton->Enabled = false;
		homeButton->Enabled = false;
		fullTurn->Enabled = false;
		shutterGroup->Enabled = false;
		filterGroup->Enabled = false;
		endButton->Enabled = true;
	}

	private: System::Void homeButton_Click(System::Object^  sender, System::EventArgs^  e) {
		// This function moves the filter wheel to the HOME position
		// It usually takes from 5 to 10 seconds
		//
		char argText[1024];
		int argValue;
		int result;

		// First select filter 1 to make the HOME faster
		filter1->Checked = true;

		strcpy_s(argText, "Run HOME function on the filter wheel.");
		argValue = 0;
		if (cam->sys.run_smartmotor && cam->curr.smartmotorIsOpen) { // True when "RUN_SMARTMOTOR: 1" is set in the D:\etc\camsetup.txt" file	
			result = smartMotorHome(MY_FORM_ARG_CALL);
		}
		filter2->Checked = false;
		filter3->Checked = false;
		filter4->Checked = false;
		filter5->Checked = false;
	}

	private: System::Void filter1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		// This function selects filter 1
		//
		char argText[1024];
		int argValue;
		int result;

		sprintf_s(argText, 64, "Select Filter 1");
		argValue = 1; // Filter 1

		if (filter1->Checked) {
			if (cam->sys.run_smartmotor && cam->curr.smartmotorIsOpen) { // True when "RUN_SMARTMOTOR: 1" is set in the ..\etc\config.txt" file
				result = smartMotorSelectFilter(MY_FORM_ARG_CALL);
			}
		}
	}

	private: System::Void filter2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		// This function selects filter 2
		//
		char argText[1024];
		int argValue;
		int result;

		sprintf_s(argText, 64, "Select Filter 2");
		argValue = 2; // Filter 2

		if (filter2->Checked) {
			if (cam->sys.run_smartmotor && cam->curr.smartmotorIsOpen) { // True when "RUN_SMARTMOTOR: 1" is set in the D:\etc\camsetup.txt" file
				result = smartMotorSelectFilter(MY_FORM_ARG_CALL);
			}
		}
	}

	private: System::Void filter3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		// This function selects filter 3
		//
		char argText[1024];
		int argValue;
		int result;

		sprintf_s(argText, 64, "Select Filter 3");
		argValue = 3; // Filter 3

		if (filter3->Checked) {
			if (cam->sys.run_smartmotor && cam->curr.smartmotorIsOpen) { // True when "RUN_SMARTMOTOR: 1" is set in the D:\etc\camsetup.txt" file
				result = smartMotorSelectFilter(MY_FORM_ARG_CALL);
			}
		}
	}

	private: System::Void filter4_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		// This function selects filter 4
		//
		char argText[1024];
		int argValue;
		int result;

		sprintf_s(argText, 64, "Select Filter 4");
		argValue = 4; // Filter 4

		if (filter4->Checked) {
			if (cam->sys.run_smartmotor && cam->curr.smartmotorIsOpen) { // True when "RUN_SMARTMOTOR: 1" is set in the D:\etc\camsetup.txt" file
				result = smartMotorSelectFilter(MY_FORM_ARG_CALL);
			}
		}
	}

	private: System::Void filter5_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		// This function selects filter 5
		//
		char argText[1024];
		int argValue;
		int result;

		sprintf_s(argText, 64, "Select Filter 5");
		argValue = 5; // Filter 5

		if (filter5->Checked) {
			if (cam->sys.run_smartmotor && cam->curr.smartmotorIsOpen) { // True when "RUN_SMARTMOTOR: 1" is set in the D:\etc\camsetup.txt" file
				result = smartMotorSelectFilter(MY_FORM_ARG_CALL);
			}
		}
	}

	private: System::Void fullTurn_Click(System::Object^  sender, System::EventArgs^  e) {
		// This function makes the filter wheel do a full turn
		//
		char argText[1024];
		int argValue;
		int result;

		strcpy_s(argText, "Turn filter wheel a full turn.");
		if (cam->sys.run_smartmotor && cam->curr.smartmotorIsOpen)
		{ // True when "RUN_SMARTMOTOR: 1" is set in the ...\etc\config.txt" file	

			// First go to filter position 1
			argValue = 1;
			result = smartMotorSelectFilter(MY_FORM_ARG_CALL);
			filter1->Checked = true;
			filter2->Checked = false;
			filter3->Checked = false;
			filter4->Checked = false;
			filter5->Checked = false;

			// Then do a full turn
			result = smartMotorFullTurn(MY_FORM_ARG_CALL);
		}
	}

	private: System::Void endButton_Click(System::Object^  sender, System::EventArgs^  e) {
		// This function ends the program
		//
		// TBD it has to do some shudown
		// If the communication to the smartmotor is open and the shutter is open: "Close the shutter"
		// If the communication to the smartmotor is open: "Close the communication/RS232"
		//
		char argText[1024];
		int argValue;
		int result;
		char qwa[256];


		result = 0;
		argValue = 0;

		cam->curr.end = true; // End button pressed

		if (cam->curr.smartmotorIsOpen)  // should not run any more close down
		{
			closeShutter->Checked = true; // Close shutter
			cam->curr.shutterIsOpen = false;

			closeSmartmtrButton_Click(sender, e);
			cam->curr.smartmotorIsOpen = false;
		}

		if (cam->curr.cameraIsStarted)   // The camera has been started
		{
			result = closeCamera(MY_FORM_ARG_CALL_NEW);
			cam->curr.cameraIsStarted = false;
		}

		if (cameraShutdownTimer->Enabled)  // temperature is still negative
		{
			sprintf_s(qwa, 256, "Sorry not allowed to shut down the program. We are waiting for the camera to warm up.");
			WriteMessage(outputText, qwa);
		}
		else  // safe temperature to shut down
		{
			sprintf_s(qwa, 256, "Activate shutdown and terminate uioCam program in %d seconds ... ", (int)(endTimer->Interval / 1000));
			WriteMessage(outputText, qwa);

			result = shutdownCamera(MY_FORM_ARG_CALL_NEW);  // finally ShutDown() the Andor iXon camera, (dummy for PVCAM) 

			endTimer->Enabled = true;  // finally shut down the program, (after 10 seconds).
		}
	}

			 // -- Form_load -- //
			 //  BASICALLY INIT //

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		// The MyForm_Load() function is executed when the uioCam program starts
		//
		System::String^ myString;
		char myLine[1024];
		char argText[1024];
		char qwa[256];
		char qwb[256];
		char qwc[256];
		char degt[10];
		int argValue;
		float f;

		strcpy_s(degt, "1");
		degt[0] = (char)176;

		strcpy_s(argText, "Initiate UioCam");
		argValue = 0;
		InitiateUioCam(MY_FORM_ARG_CALL);  // Initiate uioCam program

		strcpy_s(argText, "Read setup files");
		argValue = 0;
		ReadEtcFilesUioCam(MY_FORM_ARG_CALL, statusLabel);  // Read setup files
															// Write the current settings into the setupText
		if (cam->sys.run_camera) {
			sprintf_s(qwa, 256, "Camera is OPERATIONAL, commands are sent to the %s",
				cam->info.cameraname);
		}
		else {
			sprintf_s(qwa, 256, "Camera commands are not sent. A syntetic image is created.");
		}

		if (cam->sys.run_smartmotor) {
			sprintf_s(qwb, 256, "Smartmotor is OPERATIONAL, commands are sent.");
		}
		else {
			sprintf_s(qwb, 256, "Smartmotor commands are not sent.");
		}

		if (cam->sys.shutter_stay_open) {
			sprintf_s(qwc, 256, "Shutter is OPEN ALL THE TIME.");
		}
		else {
			sprintf_s(qwc, 256, "Shutter is closed between each image.");
		}

		sprintf_s(myLine, 1024,
			"SETTING for the uioCam program:\r\n%s\r\n%s %s",
			qwa, qwb, qwc);
		myString = gcnew System::String(myLine);
		setupText->Text = myString;

		if (cam->sys.write_log && cam->curr.logIsOpen) { // Write to log file
			fprintf(cam->curr.log_fptr, "%s\r\n", myLine);
		}

		sprintf_s(myLine, 1024,
			"\r\n(NORMAL) SUN ELEVATION MAX: %.2f%s		(NORMAL) MOON ELEVATION MAX %.2f%s",
			cam->sys.sun_elevation_max, degt, cam->sys.moon_elevation_max, degt);
		myString = gcnew System::String(myLine);
		setupText->Text += myString;

		if (cam->sys.write_log && cam->curr.logIsOpen) { // Write to log file
			fprintf(cam->curr.log_fptr, "%s\r\n", myLine);
		}

		sprintf_s(myLine, 1024, "\r\nSTATION: %s    CODE: %s    LATITUDE: %.2f%s N    LONGITUDE %.2f%s E",
			cam->info.station_short, cam->info.code, cam->info.latitude, degt, cam->info.longitude, degt);
		myString = gcnew System::String(myLine);
		setupText->Text += myString;

		if (cam->sys.write_log && cam->curr.logIsOpen) { // Write to log file
			fprintf(cam->curr.log_fptr, "%s\r\n", myLine);
		}

		sprintf_s(qwa, 256, "Sony A7iii");

		//--f = (float)(CAM_VERSION);  // defined in include.h
		f = 256; //-- wild guess please change

		sprintf_s(myLine, 1024, "\r\nCAMERA%d: %s (%s) SOFTWARE: uioCam %.2f and %s",
			cam->info.cameranumber, cam->info.cameraname, qwa, f, cam->info.library);
		myString = gcnew System::String(myLine);
		setupText->Text += myString;

		if (cam->manual == 1)
		{
			autoButton->Checked = false;
			manualButton->Checked = true;
		}
		else
		{
			autoButton->Checked = true;
			manualButton->Checked = false;
		}

		if (cam->sys.write_log && cam->curr.logIsOpen) { // Write to log file
			fprintf(cam->curr.log_fptr, "%s\r\n", myLine);

			logOn->Checked = true;   // set the Log radio buttons
			logOff->Checked = false;
		}
		else {
			logOn->Checked = false;
			logOff->Checked = true;
		}

		if (cam->sys.write_info) {   // set the Info radio buttons
			infoOn->Checked = true;
			infoOff->Checked = false;
		}
		else {
			infoOn->Checked = false;
			infoOff->Checked = true;
		}

		if (cam->sys.debug_on) {   // set the Debug radio buttons
			debugOn->Checked = true;
			debugOff->Checked = false;
		}
		else {
			debugOn->Checked = false;
			debugOff->Checked = true;
		}

		// Set the RS-232 COM ports numbers for the smartmotor
		if ((!cam->curr.smartmotorIsOpen) && (cam->sys.smartmotor_port > 0)) // Can not set this on an open RS-232 port. 
		{                                                                    // And the port number has to be > 0 in config file (SMARTMOTOR_PORT:)
			sprintf_s(qwa, 64, "COM%d", cam->sys.smartmotor_port);
			serialPort1->PortName = gcnew System::String(qwa);
		}

		if (cam->intensity_control == 1) {
			intensityOff->Checked = false;
			intensityOn->Checked = true;
		}
		else {
			intensityOff->Checked = true;
			intensityOn->Checked = false;
		}

		if (cam->post_process == 1) {
			postprocessOff->Checked = false;
			postprocessOn->Checked = true;
		}
		else {
			postprocessOff->Checked = true;
			postprocessOn->Checked = false;
		}

		// Choose run mode
		if (cam->run_mode == 1)				// cloud mode
		{
			cloudMode->Checked = true;
		}
		//else if (cam->run_mode == 2)		// polarization mode
		//{
		//	polMode->Checked = true;
		//}
		//else if (cam->run_mode == 3)		// night mode
		//{
		//	nightMode->Checked = true;
		//}
		else                                // default: normal mode
		{
			normalMode->Checked = true;
		}
	}


	private: System::Void initCameraButton_Click(System::Object^  sender, System::EventArgs^  e) {
		// This function initiate and setup the camera in proper mode

		char argText[1024];
		int argValue;
		int result;

		strcpy_s(argText, "Initiate camera");
		argValue = 0;

		//-- Safeguard: if init doesn't work properly, buttons should not be enabled

		result = initiateCamera(MY_FORM_ARG_CALL_NEW);
		acquireButton->Enabled = true;
		closeCameraButton->Enabled = true;
		cam->curr.cameraIsStarted = true;
	}

	private: System::Void groupCamera_Enter(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void groupSmartmtr_Enter(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void acquireButton_Click(System::Object^  sender, System::EventArgs^  e) {
		// This function aquire one full image from the camera

		CAMTIME camtime;
		char argText[1024];
		int argValue;
		int result;
		int no;
		int i;
		int j = 0;
		int retVal;

		cam->intensity.exposureOk = 0;

		if (cam->intensity_control == 1)
		{
			while (!cam->intensity.exposureOk)
			{
				openShutter->Checked = true; // Open shutter
				cam->curr.shutterIsOpen = true;

				no = 0;
				i = 0;
				char qwa[1024];
				strcpy_s(argText, "Acquire image");
				argValue = 0;  // This will be i in the cam->seq[i]

				result = acquireImage(MY_FORM_ARG_CALL_NEW);
				Sleep(3500);				   	// Wait for Remote to transfer the photo

				closeShutter->Checked = true; // Close shutter
				cam->curr.shutterIsOpen = false;

				retVal = runIntensityControl(outputText, process);

				switch (cam->intensity.exposure) {
				case 1:
					cam->intensity.exposureOk = 1;
					break;
				case 0:
					makeShutterSpeedBrighter(1, outputText);
					break;
				case 2:
					makeShutterSpeedDarker(1, outputText);
					break;
				default:
					continue;
				}

				GetYearMonthDayHourMinSec(&camtime.year, &camtime.month, &camtime.day,
					&camtime.hour, &camtime.min, &camtime.sec);
			}
		}

		else
		{
			openShutter->Checked = true; // Open shutter
			cam->curr.shutterIsOpen = true;

			no = 0;
			i = 0;
			strcpy_s(argText, "Acquire image");
			argValue = 0;  // This will be i in the cam->seq[i]

			result = acquireImage(MY_FORM_ARG_CALL_NEW);

			closeShutter->Checked = true; // Close shutter
			cam->curr.shutterIsOpen = false;

			GetYearMonthDayHourMinSec(&camtime.year, &camtime.month, &camtime.day,
				&camtime.hour, &camtime.min, &camtime.sec);
		}
	}

	private: System::Void exivButton_Click(System::Object^  sender, System::EventArgs^  e) {
		//This function will print information on last photo
		int result;
		result = printMetadata(outputText);
	}

	private: System::Void secTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
		//////////////////////////////////////////////////////////////////////////
		//   ##### ######    #####          #####     #    #    #  ######  #####
		// ##      #       ##                 #       #    ##  ##  #       #    #
		//   ###   #####   #                  #       #    # ## #  #####   #    #
		//      ## #       #                  #       #    #    #  #       #####
		// #    ## #       ##                 #       #    #    #  #       #   #
		//  #####  ######    #####  #######   #       #    #    #  ######  #    #
		//////////////////////////////////////////////////////////////////////////
		// This is the main loop in the uioCam program
		// This timer updates every second

		char argText[1024];
		int argValue = 0;
		int year;
		int month;
		int day;
		int h;
		int m;
		int retVal;
		int s;   // second,  expose image, close shutter
		int s1;  // second + 1, one second ahead, open shutter

		GetYearMonthDayHourMinSec(&year, &month, &day, &h, &m, &s); // Get UT Date and Time 

		s1 = s + 1;
		if (s1 > 59) s1 -= 60;

		// To get minTimer up faster
		if (cam->curr.first_min) {
			cam->curr.first_min = false;
			minTimer->Interval = (59 - s) * 1000; // Want it to run minTimer_Tick once before 60s timer
			minTimer->Enabled = true;
		}

		// Syncronize on second=0 to enable the minute timer (minTimer)
		if (!cam->curr.minTimerEnabled) // The minTimer should start at sec=0
		{
			if (s == 0)
			{
				cam->curr.minTimerEnabled = true;
				minTimer->Interval = 60000;
				minTimer->Enabled = true;
			}
		}

		// Check start minute and start second
		if (cam->run_ok && cam->timeseq_ok && cam->sunmoon_ok && (!cam->curr.manual)) {
			if (!cam->min_ok)
			{
				if (cam->start_min == m || cam->start_min == -1)
				{
					cam->min_ok = true;
				}
			}
			if (cam->min_ok && !cam->sec_ok)
			{
				if (cam->start_sec == s1 || cam->start_sec == -1) // s+1 to have time to get ready
				{
					cam->sec_ok = true;
					cam->sec_since_img = cam->interval - 1;
				}
			}
		}

		if (cam->run_ok && cam->timeseq_ok && (!cam->curr.manual) && cam->sec_ok) // All is OK: In full run mode, and not manual mode
		{
			// ARMED AND RUNNING OK , ARMED AND RUNNING START ::::::::::::::  

			// START    #####   #    #  #    #  #    #     #    #    #   ####     START
			// START    #    #  #    #  ##   #  ##   #     #    ##   #  #    #    START
			// START    #    #  #    #  # #  #  # #  #     #    # #  #  #         START
			// START    #####   #    #  #  # #  #  # #     #    #  # #  #  ###    START
			// START    #   #   #    #  #   ##  #   ##     #    #   ##  #    #    START  
			// START    #    #   ####   #    #  #    #     #    #    #   ####     START

			// Go to correct filter position
			if (cam->filter != cam->curr.currentFilter)
			{
				switch (cam->filter)
				{
				case 1: filter1->Checked = true; break;  // Select  filter
				case 2: filter2->Checked = true; break;
				case 3: filter3->Checked = true; break;
				case 4: filter4->Checked = true; break;
				case 5: filter5->Checked = true; break;
				}
				cam->curr.currentFilter = cam->filter;  // Store current filter number
			}

			// :::: S E C O N D   O F  I M A G E ::::
			if (cam->sec_since_img == (cam->interval))
			{
				acquireButton_Click(sender, e);
				cam->sec_since_img = 1;
			}

			// :::: A N Y   O T H E R   S E C O N D ::::
			else
			{
				cam->sec_since_img = cam->sec_since_img + 1;
			}
			// END      #####   #    #  #    #  #    #     #    #    #   ####       END
			// END      #    #  #    #  ##   #  ##   #     #    ##   #  #    #      END 
			// END      #    #  #    #  # #  #  # #  #     #    # #  #  #           END
			// END      #####   #    #  #  # #  #  # #     #    #  # #  #  ###      END 
			// END      #   #   #    #  #   ##  #   ##     #    #   ##  #    #      END  
			// END      #    #   ####   #    #  #    #     #    #    #   ####       END 

		}   // ARMED AND RUNNING END :::::::::::::::::::::::::::::::::::::::::::::

		// Safeguard
		else if (cam->curr.shutterIsOpen) // Stopped running but not closed shutter ?
		{
			if (cam->curr.shutterIsOpen) {
				closeShutter->Checked = true; // Close shutter
				cam->curr.shutterIsOpen = false;
			}
		}

		// Update current UT time label
		currentTimeLabel->Text = GetDateString();

		// At last do every minute:
		//
		// Update Astro label
		if (s == 0) // Do every minute ::::::::::::::::::::::::::::::::::::::::::::::
		{
			AstroUpdate(year, month, day, h, m, s); // Calculate the SUN and MOON altitude and azimuth (astroIo.cpp file)
			astroLabel->Text = GetAstroString();    // Update the label, the function GetAstroString() also has an option to write to the log file
													// GetAstroString() is in func.cpp
													// NB: Nothing is written in the main text window

			if (m == 0)  // Do every hour :::::::::::::::::::::::::::::::::::::::::::::::
			{
				if (cam->sys.write_log && cam->curr.logIsOpen)  // Close last log file, and open a new one
				{
					logOff->Checked = true;
					logOn->Checked = true;
				}

				outputText->Text = " ";  // Reset output text every hour, if not it will be to large

				// Intensity control check every hour - deleted, intensity control run on every photo made when it is ON

				// Do a filter wheel HOME every midnight
				if (h == 0)
				{
					if (cam->run_ok && cam->timeseq_ok  && cam->sunmoon_ok && (!cam->curr.manual))
					{
						if (cam->sys.home) {  // only if HOME: 1 is set in configuration file
							homeButton_Click(sender, e); // Do a HOME on the filter wheel (the timeouts are set in the smartMototorOpenSerialPort1() function)
						}
					}
				}
			} // End do every hour :::::::::::::::::::::::::::::::::::::::::::::::::::::
		} // End do every minute :::::::::::::::::::::::::::::::::::::::::::::::::::
	}

	private: System::Void minTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
		//////////////////////////////////////////////////////////////////////////
		// #    #     #    #    #           #####     #    #    #  ######  #####
		// ##  ##     #    ##   #             #       #    ##  ##  #       #    #
		// # ## #     #    # #  #             #       #    # ## #  #####   #    #
		// #    #     #    #  # #             #       #    #    #  #       #####
		// #    #     #    #   ##             #       #    #    #  #       #   #
		// #    #     #    #    # #######     #       #    #    #  ######  #    #
		//////////////////////////////////////////////////////////////////////////
		// This is the timer executing every minute		 

		char argText[1024];
		int argValue;
		int result;

		argValue = 0;

		result = CheckSunMoon();  // Check the the SUN and the MOON 
		if (cam->sunmoon_ok) {
			astroLabel->ForeColor = System::Drawing::Color::Green;
		}
		else {
			astroLabel->ForeColor = System::Drawing::Color::DarkViolet;
		}

		result = CheckSeqTime(statusLabel); // Check the SEQUENCE TIME , (in sequence.cpp file)

		if (cam->run_ok && cam->timeseq_ok  && cam->sunmoon_ok && (!cam->curr.manual) && (!cam->curr.end)) // All is OK: In full run mode, (and not manual mode) , 
		{   // ########################  START A NEW INTERVAL ######################################       // and end button has not been pressed
			// ### STARTUP THE SYSTEM ##############################################################
			// #####################################################################################

			if (!cam->curr.buttons_enabled)
			{
				openSmartmtrButton->Enabled = true;
				initCameraButton->Enabled = true;
				acquireButton->Enabled = true;
				closeCameraButton->Enabled = true;

				cam->curr.buttons_enabled = true;
			}

			if (!cam->curr.smartmotorIsOpen)
			{
				openSmartmtrButton_Click(sender, e);

				if (cam->sys.home) // only if HOME: 1 is set in the configuration file
				{
					homeButton_Click(sender, e); // Do a HOME on the filter wheel (the timeouts are set in the smartMototorOpenSerialPort1() function)
				}
			}

			if ((!cam->curr.cameraIsStarted) && (cam->sys.run_camera))  // We should use the camera
			{                                                           // and we have not initiated it
				// INITIATE THE CAMERA SYSTEM 
				strcpy_s(argText, "Initiate camera");  // same as initCameraButton_Click()
				argValue = 0;
				result = initiateCamera(MY_FORM_ARG_CALL_NEW); // Initiate camera
				acquireButton->Enabled = true;

				cam->curr.cameraIsStarted = true;
			}
		}      // ##################################################################################
		else   // END OF INTERVAL AUTOMATIC SHUT OFF OF THE CAMERA #################################
		{      //###################################################################################

			if (cam->curr.smartmotorIsOpen && (!cam->curr.manual))  // should not run any more close down, (do nothing in manual mode)
			{
				if (cam->curr.shutterIsOpen) // stopped running but not closed shutter ??
				{
					closeShutter->Checked = true; // Close shutter
					cam->curr.shutterIsOpen = false;
				}
				closeSmartmtrButton_Click(sender, e);
				cam->curr.smartmotorIsOpen = false;
			}

			if (!cam->curr.manual) // not in manual mode
			{
				if (cam->curr.cameraIsStarted)
				{
					result = closeCamera(MY_FORM_ARG_CALL_NEW);
					cam->curr.cameraIsStarted = false;
				}

				if (cam->curr.buttons_enabled)
				{
					openSmartmtrButton->Enabled = false;
					initCameraButton->Enabled = false;
					acquireButton->Enabled = false;
					closeCameraButton->Enabled = false;

					cam->curr.buttons_enabled = false;
				}
			} // not in manual mode
		} // END OF INTERVAL ##################################################################
	}

	private: System::Void statusLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void currentTimeLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void uioCam_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void outputText_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void setupText_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void debugOn_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {  // DEBUG ON BUTTON
		if (!cam->sys.debug_on) cam->sys.debug_on = true;  // switch debug on
	}

	private: System::Void debugOff_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {  // DEBUG OFF BUTTON
		if (cam->sys.debug_on) cam->sys.debug_on = false;  // switch debug off
	}

	private: System::Void logOn_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {  // LOG ON BUTTON

		CAMTIME camtime;
		char argText[1024];
		int argValue;
		int result;

		strcpy_s(argText, "Open new log file");
		argValue = 0;

		if (!cam->sys.write_log) cam->sys.write_log = true;  // allowed to write log file

		if (!cam->curr.logIsOpen) // log file not open, open a new one
		{
			GetYearMonthDayHourMinSec(&camtime.year, &camtime.month, &camtime.day,
				&camtime.hour, &camtime.min, &camtime.sec);
			result = CamOpenNewLogFile(MY_FORM_ARG_CALL, camtime);
		}
	}

	private: System::Void logOff_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {  // LOG OFF BUTTON
		if (cam->sys.write_log && cam->curr.logIsOpen)  // Close last log file
		{
			fclose(cam->curr.log_fptr);
			cam->curr.logIsOpen = false;
		}

		if (cam->sys.write_log) cam->sys.write_log = false;  // NOT allowed to write log file
	}

	private: System::Void readConfigButton_Click(System::Object^  sender, System::EventArgs^  e) {
		// Refresh ETC config files

		char argText[1024];
		int argValue;

		if (cam->curr.smartmotorIsOpen)  // should not be open temporary close 
		{
			if (cam->curr.shutterIsOpen) { // stopped running but not close shutter ??
				closeShutter->Checked = true; // Close shutter
				cam->curr.shutterIsOpen = false;
			}

			closeSmartmtrButton_Click(sender, e);
			cam->curr.smartmotorIsOpen = false;
		}

		if (cam->sys.write_log && cam->curr.logIsOpen)  // Close last log file
		{
			logOff->Checked = true;
		}

		strcpy_s(argText, "Reset and Read Config Files");
		argValue = 0;
		WriteMessage(outputText, argText);

		// Init mode radiobuttons
		normalMode->Checked = false;
		cloudMode->Checked = false;
		//polMode->Checked = false;
		//nightMode->Checked = false;

		MyForm_Load(sender, e);  // Same as when program starts
	}

	private: System::Void endTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
		// This shut down the program
		WriteMessage(outputText, "The uioCam program ends now.");
		if (cam->sys.write_log && cam->curr.logIsOpen)  // Close last log file
		{
			fclose(cam->curr.log_fptr);
			cam->curr.logIsOpen = false;
		}
		exit(0);  // Shut down the program
	}

	private: System::Void autoButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		// Set auto mode
		cam->curr.manual = false;

		openSmartmtrButton->Enabled = false;
		initCameraButton->Enabled = false;
		acquireButton->Enabled = false;

		cam->curr.buttons_enabled = false;
	}

	private: System::Void manualButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		// Set manual mode
		cam->curr.manual = true;

		if (!cam->curr.buttons_enabled)
		{
			openSmartmtrButton->Enabled = true;
			initCameraButton->Enabled = true;
			// acquireButton->Enabled = true;
			// closeCameraButton->Enabled = true;

			cam->curr.buttons_enabled = true;
		}
	}

	private: System::Void MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		// This is activated when the [x] in the right upper window corner is activated
		// Do a controlled shutdown of the camera

		// Cancel the Closing event
		e->Cancel = true;

		endButton_Click(sender, e);  // activate the [End] button to execute the shutdown procedure
	}

	private: System::Void closeCameraButton_Click(System::Object^  sender, System::EventArgs^  e) {
		// This button stop the camera
		char argText[1024];
		int argValue;
		int result;

		argValue = 0;

		if (cam->curr.cameraIsStarted)
		{
			result = closeCamera(MY_FORM_ARG_CALL_NEW);
			cam->curr.cameraIsStarted = false;
		}
		closeCameraButton->Enabled = false;
		acquireButton->Enabled = false;
	}

	private: System::Void cameraShutdownTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
		// This timer reads the AndorIxon temperature and checks if it is above 0 degrees
		char argText[1024];
		char qwa[256];
		int argValue;
		int result;
		char c;

		argValue = 0;
		c = (char)176;

		strcpy_s(argText, "cameraShutdownTimer checks camera temperature");
		WriteMessage(outputText, argText);
		result = 0;

		//--if (cam->curr.temperature > 0)  // Safe to shut down camera
		{
			cameraShutdownTimer->Enabled = false;
			strcpy_s(argText, "cameraShutdownTimer has found positive camera temperature, it should be safe to shutdown camera now.");
			WriteMessage(outputText, argText);

			if (cam->curr.end)  // 'End' button has been pressed
			{
				strcpy_s(argText, "The End button was previously pressed and the uioCam program will now end.");
				WriteMessage(outputText, argText);

				endButton_Click(sender, e); // Activate the [End] button to execute the shutdown procedure
			}
			else // From the 'AUTOMATIC SHUTDOWN' procedure or when the 'CloseCamera' button was pressed
			{
				sprintf_s(qwa, 256, "Activate shudown of the Andor iXon camera");
				WriteMessage(outputText, qwa);

				result = shutdownCamera(MY_FORM_ARG_CALL_NEW);  // finally ShutDown() the Andor iXon camera, (dummy for PVCAM) 
			}
		}  // end safe to shut down the camera
	}

	private: System::Void getGainLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void infoOn_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		cam->sys.write_info = true;
	}

	private: System::Void infoOff_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		cam->sys.write_info = false;
	}

	private: System::Void editConfig_Click(System::Object^  sender, System::EventArgs^  e) {
		char argText[1024];
		int argValue = 0;

		openConfig(MY_FORM_ARG_CALL_NEW);
	}

	private: System::Void editTime_Click(System::Object^  sender, System::EventArgs^  e) {
		char argText[1024];
		int argValue = 0;

		openTime(MY_FORM_ARG_CALL_NEW);
	}

	private: System::Void openReadMe_Click(System::Object^  sender, System::EventArgs^  e) {
		char argText[1024];
		int argValue = 0;

		openReadMeFile(MY_FORM_ARG_CALL_NEW);
	}

	private: System::Void normalMode_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		char argText[1024];
		int argValue = 0;

		// Mode must be set when system is (re)started
		if (cam->first_mode_set == 0) { cam->run_mode = -1; }

		if (cam->run_mode != 0) {
			cam->run_mode = 0;
			if (cam->first_mode_set == 0) { cam->first_mode_set = 1; }

			// Get correct values
			initNormalMode(MY_FORM_ARG_CALL);

			// Go to correct filter position
			if (cam->filter != cam->curr.currentFilter)
			{
				switch (cam->filter)
				{
				case 1: filter1->Checked = true; break;  // Select  filter
				case 2: filter2->Checked = true; break;
				case 3: filter3->Checked = true; break;
				case 4: filter4->Checked = true; break;
				case 5: filter5->Checked = true; break;
				}
				cam->curr.currentFilter = cam->filter;  // Store current filter number
			}
			if (cam->intensity_control == 1) {
				intensityOff->Checked = false;
				intensityOn->Checked = true;
			}
			else {
				intensityOff->Checked = true;
				intensityOn->Checked = false;
			}

			if (cam->post_process == 1) {
				postprocessOff->Checked = false;
				postprocessOn->Checked = true;
			}
			else {
				postprocessOff->Checked = true;
				postprocessOn->Checked = false;
			}
		}
	}


	private: System::Void cloudMode_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		char argText[1024];
		int argValue = 0;

		// Mode must be set when system is (re)started
		if (cam->first_mode_set == 0) { cam->run_mode = -1; }

		if (cam->run_mode != 1) {
			cam->run_mode = 1;
			if (cam->first_mode_set == 0) { cam->first_mode_set = 1; }

			// Get correct values
			initCloudMode(MY_FORM_ARG_CALL);

			// Go to correct filter position
			if (cam->filter != cam->curr.currentFilter)
			{
				switch (cam->filter)
				{
				case 1: filter1->Checked = true; break;  // Select  filter
				case 2: filter2->Checked = true; break;
				case 3: filter3->Checked = true; break;
				case 4: filter4->Checked = true; break;
				case 5: filter5->Checked = true; break;
				}
				cam->curr.currentFilter = cam->filter;  // Store current filter number
			}
			if (cam->intensity_control == 1) {
				intensityOff->Checked = false;
				intensityOn->Checked = true;
			}
			else {
				intensityOff->Checked = true;
				intensityOn->Checked = false;
			}

			if (cam->post_process == 1) {
				postprocessOff->Checked = false;
				postprocessOn->Checked = true;
			}
			else {
				postprocessOff->Checked = true;
				postprocessOn->Checked = false;
			}
		}
	}

	/*private: System::Void polMode_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		char argText[1024];
		int argValue;

		// Mode must be set when system is (re)started
		if (cam->first_mode_set == 0) { cam->run_mode = -1; }

		if (cam->run_mode != 2) {
			cam->run_mode = 2;
			if (cam->first_mode_set == 0) { cam->first_mode_set = 1; }

			// Get correct values
			initPolMode(MY_FORM_ARG_CALL);

			// Go to correct filter position
			if (cam->filter != cam->curr.currentFilter)
			{
				switch (cam->filter)
				{
				case 1: filter1->Checked = true; break;  // Select  filter
				case 2: filter2->Checked = true; break;
				case 3: filter3->Checked = true; break;
				case 4: filter4->Checked = true; break;
				case 5: filter5->Checked = true; break;
				}
				cam->curr.currentFilter = cam->filter;  // Store current filter number
			}
		}
	}
	*/

	/*private: System::Void nightMode_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		char argText[1024];
		int argValue;

		// Mode must be set when system is (re)started
		if (cam->first_mode_set == 0) { cam->run_mode = -1; }

		if (cam->run_mode != 3)
		{
			cam->run_mode = 3;
			if (cam->first_mode_set == 0) { cam->first_mode_set = 1; }

			// Get correct values
			initNightMode(MY_FORM_ARG_CALL);

			// Go to correct filter position
			if (cam->filter != cam->curr.currentFilter)
			{
				switch (cam->filter)
				{
				case 1: filter1->Checked = true; break;  // Select  filter
				case 2: filter2->Checked = true; break;
				case 3: filter3->Checked = true; break;
				case 4: filter4->Checked = true; break;
				case 5: filter5->Checked = true; break;
				}
				cam->curr.currentFilter = cam->filter;  // Store current filter number
			}
		}
	}
	*/

	// Issue with intensityOff/On: For unknown reasons when radio button intensity control On is clicked
	// uioCam runs first anything inside intensityOff_CheckedChanged and then anything that is inside
	// intensityOn_CheckedChanged. When radio button Off is clicked similar issue appears: first uioCam
	// runs whatever is in intensityOff and then what is in intensityOn. To make sure that updateRemotstat
	// is run only when needed intensity_control_helper_troll is used. It works.
	private: System::Void intensityOff_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		cam->intensity_control = 0; // set intensity control flag to 0
		cam->intensity_control_helper_troll = 0; // make sure that updateRemotestat runs the next time that ON is clicked
	}

	private: System::Void intensityOn_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		cam->intensity_control = 1; // set intensity control flag to 1
		
		if (cam->intensity_control_helper_troll != 2) // make sure that updateRemostat is run only when ON is clicked
		{
			int result = 0;
			int result_2 = 0;
			int argValue = 0;
			char argText[1024];

			result = acquireImage(MY_FORM_ARG_CALL_NEW); // make a photo, shutter can be closed
			Sleep(4500);				   	// Wait for Remote to transfer the photo
			result_2 = updateRemotestat(outputText); // read ISO and shutter speed into PHOTOSTAT and remove the photo
		}

		cam->intensity_control_helper_troll = 2; // make sure that updateRemostat is not run when OFF is clicked
	}

	private: System::Void postprocessOff_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		cam->post_process = 0;
	}

	private: System::Void postprocessOn_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		cam->post_process = 1;
	}
};
};
