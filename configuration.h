/**************************************************************************
	FileName		[ configuration.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Configurations of the NTUEE CNC Writing Project ]
	Author			[ Teaching Group, Elevate, NTUEE]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present EESA, NTUEE, NTU, Taiwan]
**************************************************************************/

#pragma once

/**************** Baudrate start ****************/
	#define Baudrate 				9600
/**************** Baudrate start ****************/

/**************** Stepper Motor start ****************/
	#define X_Stepper_Step_Pin		3
	#define X_Stepper_Dir_Pin		4
	#define X_Stepper_Enable_Pin	8

	#define Y_Stepper_Step_Pin		5
	#define Y_Stepper_Dir_Pin		6
	#define Y_Stepper_Enable_Pin	9

	#define StepsPerRevolution		200
	#define StepsPerMilimeter_X		6.0
	#define StepsPerMilimeter_Y		6.0

	#define X_Stepper_Speed			50
	#define Y_Stepper_Speed			50
/**************** Stepper Motor end ****************/

/**************** Endstops start ****************/
	#define X_Endstop				10
	#define Y_Endstop				11
/**************** Endstops end ****************/

/**************** Servo Motor start ****************/
	#define Servo_Pin				7

	#define Servo_Pen_Up_Angle		90
	#define Servo_Pen_Down_Angle	45
/**************** Servo Motor end ****************/

/**************** Bed Settings start ****************/
	#define Bed_X_Min				0
	#define Bed_X_Max				500
	#define Bed_Y_Min				0
	#define Bed_Y_Max				500
/**************** Bed Settings end ****************/
