/**************************************************************************
	FileName		[ motor_driver.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Motor Driver for the NTUEE CNC Drawing Machine ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#pragma once

#include "configuration.h"

#include <Servo.h>
#include "cnc_stepper.h"

/**************** Macro Definitions of Motors start ****************/
	Stepper X_Stepper(X_StepsPerRevolution, X_Stepper_Step_Pin, X_Stepper_Dir_Pin);
	Stepper Y_Stepper(Y_StepsPerRevolution, Y_Stepper_Step_Pin, Y_Stepper_Dir_Pin);

	Servo Pen_Servo;
/**************** Macro Definitions of Motors end ****************/

/**************** Servo Moving start ****************/
	void Move_Pen(bool down){
		if(down)
			Pen_Servo.write(Servo_Pen_Down_Angle);
		else
			Pen_Servo.write(Servo_Pen_Up_Angle);

		return;
	}
/**************** Servo Moving end ****************/

/**************** Stepper Moving start ****************/
	void Move_Stepper_Linear(float X, float Y){
		// TODO
	}

	void Move_Stepper_Circular_R(bool dir, float X, float Y, float R){
		// TODO
	}

	void Move_Stepper_Circular_IJ(bool dir, float X, float Y, float I, float J){
		// TODO
	}
/**************** Stepper Moving end ****************/

/**************** Stepper Enable start ****************/
	bool X_Enabled = false;
	bool Y_Enabled = false;

	void Enable_Stepper_X(bool enable){
		if(enable){
			X_Enabled = true;
			digitalWrite(X_Stepper_Enable_Pin, HIGH);
		}
		else{
			X_Enabled = false;
			digitalWrite(X_Stepper_Enable_Pin, LOW);
		}
	}

	void Enable_Stepper_Y(bool enable){
		if(enable){
			Y_Enabled = true;
			digitalWrite(Y_Stepper_Enable_Pin, HIGH);
		}
		else{
			Y_Enabled = false;
			digitalWrite(Y_Stepper_Enable_Pin, LOW);
		}
	}

	bool Get_Enable_X() { return X_Enabled; }
	bool Get_Enable_Y() { return Y_Enabled; }
/**************** Stepper Enable end ****************/

/**************** Homing start ****************/
/**************** Homing end ****************/

/**************** Coordinate start ****************/
/**************** Coordinate end ****************/

/**************** Kill / Halt start ****************/
/**************** Kill / Halt end ****************/
