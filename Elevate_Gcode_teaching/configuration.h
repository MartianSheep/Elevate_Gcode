/**************************************************************************
	FileName		[ configuration.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Configurations of the NTUEE CNC Drawing Machine ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#pragma once

/**************** Basic Settings start ****************/
	#define Baudrate 				9600
	#define MAX_BUF					100
	#define ACTION_TIME				100

	#define PCB_F1					true
/**************** Basic Settings end ****************/

/**************** Stepper Motor start ****************/
	#define Stepper_Enable_Pin		10

	#define X_Stepper_Step_Pin		2
	#define X_Stepper_Dir_Pin		4
	
	#define Y_Stepper_Step_Pin		3
	#define Y_Stepper_Dir_Pin		5

	// please insert the original offset
	#define Steps_Per_Rev_Origin	20
	#define Stepper_Mili_Per_Rev	3.0

	// consider feedrate unit
	#define X_Milis_Per_Second		15.0
	#define Y_Milis_Per_Second		15.0

	// step to step delay Time
	#define motor_delay_time		50 
/**************** Stepper Motor end ****************/

/**************** Stepper Motor Advanced start ****************/
	#if PCB_F1
		#define Steps_Per_Rev		(Steps_Per_Rev_Origin*16)
	#else
		#define Steps_Per_Rev		(Steps_Per_Rev_Origin*8)
	#endif

	#define Milis_Per_Step			(Stepper_Mili_Per_Rev/Steps_Per_Rev)
	
	#define X_Stepper_Period		(1000*Milis_Per_Step/X_Milis_Per_Second)
	#define Y_Stepper_Period		(1000*Milis_Per_Step/Y_Milis_Per_Second)
	// unit is miliseconds

/**************** Stepper Motor Advanced end ****************/

/**************** Endstops start ****************/
	#define X_Endstop_Pin			11
	#define Y_Endstop_Pin			12

	#define Homing_Delay			500
/**************** Endstops end ****************/

/**************** Servo Motor start ****************/
	#define Servo_Pin				9
	#define Servo_Pen_Up_Angle		15
	#define Servo_Pen_Limit_Angle	30

	#define Pen_Delay_Time			100
/**************** Servo Motor end ****************/