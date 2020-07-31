/**************************************************************************
	FileName		[ motor_driver.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Motor Driver for the NTUEE CNC Drawing Machine ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#pragma once

#include "../configuration.h"

#include <Servo.h>
#include "cnc_stepper.h"

/**************** Macro Definitions of Motors start ****************/
	CNC_Stepper X_Stepper(X_Stepper_Step_Pin, X_Stepper_Dir_Pin);
	CNC_Stepper Y_Stepper(Y_Stepper_Step_Pin, Y_Stepper_Dir_Pin);

	Enable_Controller Enabler(Stepper_Enable_Pin);

	Servo Pen_Servo;
/**************** Macro Definitions of Motors end ****************/

/**************** Servo start ****************/
	void Pen_init(unsigned int pin){
		Pen_Servo.attach(pin);
		Pen_Servo.write(Servo_Pen_Up_Angle);
		delay(Pen_Delay_Time);
	}

	void Pen_Degree(int degree);
/**************** Servo end ****************/

/**************** Stepper Moving start ****************/
	void Move_Stepper_Linear(float X, float Y);
	void Move_to(float X, float Y){
		Move_Stepper_Linear(X,Y);
		Enabler.enable();
	}
/**************** Stepper Moving end ****************/

/**************** Coordinate start ****************/
	float X_coordinate() { return (float)X_Stepper.get_pos()*Milis_Per_Step; }
	float Y_coordinate() { return (float)Y_Stepper.get_pos()*Milis_Per_Step; }
/**************** Coordinate end ****************/