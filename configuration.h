/**************************************************************************
	FileName		[ configuration.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Configurations of the NTUEE CNC Drawing Machine ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#pragma once

#define DEBUG false

/**************** Baudrate start ****************/
	#define Baudrate 				9600
/**************** Baudrate end ****************/

/**************** Stepper Motor start ****************/
	#define X_Stepper_Step_Pin		3
	#define X_Stepper_Dir_Pin		4
	#define X_Stepper_Enable_Pin	8

	#define Y_Stepper_Step_Pin		5
	#define Y_Stepper_Dir_Pin		6
	#define Y_Stepper_Enable_Pin	9

	#define X_Steps_Per_Revolution	20
	#define Y_Steps_Per_Revolution	20
	#define X_Mili_Per_Revolution	3.2
	#define Y_Mili_Per_Revolution	3.2
	#define Steps_Per_Mili_X		X_Mili_Per_Revolution/X_Steps_Per_Revolution
	#define Steps_Per_Mili_Y		Y_Mili_Per_Revolution/Y_Steps_Per_Revolution

	#define X_Stepper_Speed			50
	#define Y_Stepper_Speed			50

	// #define X_Feedrate				50
	// #define Y_Feedrate				50

	// #define X_Stepper_Speed_Slow	25
	// #define X_Stepper_Speed_Fast	50
	// #define Y_Stepper_Speed_Slow	25
	// #define	Y_Stepper_Speed_Fast	50

	#define X_Stepper_Invert		false
	#define Y_Stepper_Invert		false
/**************** Stepper Motor end ****************/

/**************** Stepper Motor Advanced start ****************/
	#define Stepper_Smallest_Step	1
	#define Step_Delay_Time			0
	#define	Line_Delay_Time			50
	#define Pen_Delay_Time			50
/**************** Stepper Motor Advanced end ****************/

/**************** Endstops start ****************/
	#define X_Min_Endstop_Pin		10
	#define X_Min_Endstop_Invert	false
	#define X_Max_Endstop_Pin
	#define X_Max_Endstop_Invert	false

	#define Y_Min_Endstop_Pin		11
	#define Y_Min_Endstop_Invert	false
	#define Y_Max_Endstop_Pin
	#define Y_Max_Endstop_Invert	false
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
