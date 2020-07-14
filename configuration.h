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

/**************** Stepper Controller A4988 start ****************/
	#define X_Stepper_MS1			true
	#define X_Stepper_MS2			true
	#define X_Stepper_MS3			true

	#define Y_Stepper_MS1			true
	#define Y_Stepper_MS2			true
	#define Y_Stepper_MS3			true
/**************** Stepper Controller A4988 end ****************/

/**************** Stepper Motor start ****************/
	#define X_Stepper_Step_Pin		3
	#define X_Stepper_Dir_Pin		4
	#define X_Stepper_Enable_Pin	8

	#define Y_Stepper_Step_Pin		5
	#define Y_Stepper_Dir_Pin		6
	#define Y_Stepper_Enable_Pin	9

	// please insert the original offset
	#define X_Steps_Per_Rev_Origin	20
	// please insert the original offset
	#define Y_Steps_Per_Rev_Origin	20
	#define X_Mili_Per_Revolution	3.2
	#define Y_Mili_Per_Revolution	3.2

	// consider feedrate unit
	#define X_Milis_Per_Second		1.0
	#define Y_Milis_Per_Second		1.0

	#define X_Stepper_Invert		false
	#define Y_Stepper_Invert		false
/**************** Stepper Motor end ****************/

/**************** Stepper Motor Advanced start ****************/
	#define Stepper_Smallest_Step	1
	#define Step_Delay_Time			0
	#define	Line_Delay_Time			50

	// X micro steps
		#if (X_Stepper_MS1 && X_Stepper_MS2 && X_Stepper_MS3)
			#define X_Steps_Multi		16
		#elif (X_Stepper_MS1 && X_Stepper_MS2)
			#define X_Steps_Multi		8
		#elif X_Stepper_MS2
			#define X_Steps_Multi		4
		#elif X_Stepper_MS1
			#define X_Steps_Multi		2
		#else
			#define X_Steps_Multi		1
		#endif
		// redefine X_Steps_Per_Revolution
		#define X_Steps_Per_Revolution	X_Steps_Per_Rev_Origin*X_Steps_Multi

	// Y micro steps
		#if (Y_Stepper_MS1 && Y_Stepper_MS2 && Y_Stepper_MS3)
			#define Y_Steps_Multi		16
		#elif (Y_Stepper_MS1 && Y_Stepper_MS2)
			#define Y_Steps_Multi		8
		#elif Y_Stepper_MS2
			#define Y_Steps_Multi		4
		#elif Y_Stepper_MS1
			#define Y_Steps_Multi		2
		#else
			#define Y_Steps_Multi		1
		#endif
		// redefine Y_Steps_Per_Revolution
		#define Y_Steps_Per_Revolution	Y_Steps_Per_Rev_Origin*Y_Steps_Multi

	#define X_Milis_Per_Step		X_Mili_Per_Revolution/X_Steps_Per_Revolution
	#define Y_Milis_Per_Step		Y_Mili_Per_Revolution/Y_Steps_Per_Revolution
	
	#define X_Stepper_Period		X_Milis_Per_Step/X_Milis_Per_Second
	#define Y_Stepper_Period		Y_Milis_Per_Step/Y_Milis_Per_Second
	// unit is seconds

/**************** Stepper Motor Advanced end ****************/

/**************** Endstops start ****************/
	#define X_Endstop_Pin			10
	#define X_Endstop_Invert		false
	// endstop_invert: if false,
	// this means that endstop returns false while NOT touched

	// #define X_Min_Endstop_Pin		10
	// #define X_Min_Endstop_Invert	false
	// #define X_Max_Endstop_Pin
	// #define X_Max_Endstop_Invert	false

	#define Y_Endstop_Pin			10
	#define Y_Endstop_Invert		false
	// endstop_invert: if false,
	// this means that endstop returns false while NOT touched

	// #define Y_Min_Endstop_Pin		11
	// #define Y_Min_Endstop_Invert	false
	// #define Y_Max_Endstop_Pin
	// #define Y_Max_Endstop_Invert	false
/**************** Endstops end ****************/

/**************** Servo Motor start ****************/
	#define Servo_Pin				7

	#define Servo_Pen_Up_Angle		90
	#define Servo_Pen_Down_Angle	45

	#define Pen_Delay_Time			100
/**************** Servo Motor end ****************/

/**************** Bed Settings start ****************/
	#define Bed_X_Min				0
	#define Bed_X_Max				500
	#define Bed_Y_Min				0
	#define Bed_Y_Max				500
/**************** Bed Settings end ****************/
