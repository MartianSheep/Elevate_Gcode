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
	CNC_Stepper X_Stepper(X_Stepper_Period,
						X_Stepper_Step_Pin,
						X_Stepper_Dir_Pin,
						X_Stepper_Enable_Pin);

	CNC_Stepper Y_Stepper(Y_Stepper_Period,
						Y_Stepper_Step_Pin,
						Y_Stepper_Dir_Pin,
						Y_Stepper_Enable_Pin);

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
		float now_X = X_Stepper.get_pos();
		float now_Y = Y_Stepper.get_pos();
	}

	void Move_Stepper_Circular_R(bool dir, float X, float Y, float R){
		// TODO
	}

	void Move_Stepper_Circular_IJ(bool dir, float X, float Y, float I, float J){
		// TODO
	}
/**************** Stepper Moving end ****************/

/**************** Stepper Enable start ****************/
	void Enable_Stepper_X(bool enable){
		if(enable)	X_Stepper.enable();
		else 		X_Stepper.disable();
	}

	void Enable_Stepper_Y(bool enable){
		if(enable)	Y_Stepper.enable();
		else		Y_Stepper.disable();
	}

	bool Get_Enable_X() { return X_Stepper.get_enable(); }
	bool Get_Enable_Y() { return Y_Stepper.get_enable(); }
/**************** Stepper Enable end ****************/

/**************** Homing start ****************/
	void X_homing() { X_Stepper.homing(); }
	void Y_homing() { Y_Stepper.homing(); }
/**************** Homing end ****************/

/**************** Coordinate start ****************/
	// TODO
	float X_coordinate() { return (float)X_Stepper.get_pos()*Milis_Per_Step_X; }
	float Y_coordinate() { return (float)Y_Stepper.get_pos()*Miliss_Per_Step_Y; }
/**************** Coordinate end ****************/

/**************** Kill / Halt start ****************/
	// TODO

/**************** Kill / Halt end ****************/
