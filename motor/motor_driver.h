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
		Serial.println("Linear moving...");
//		for(int i = 0; i < 1000; ++i)
//			X_Stepper.step(1);
		
		long now_X = X_Stepper.get_pos();
		long now_Y = Y_Stepper.get_pos();

		long next_X = X/X_Milis_Per_Step;
		long next_Y = Y/Y_Milis_Per_Step;

		long X_steps = next_X - now_X;
		long Y_steps = next_Y - now_Y;
		
//		Serial.println(X_steps);
//		Serial.println(Y_steps);
		
		float m = 0;
		if(X_steps!=0) m = Y_steps/X_steps;

		int X_one_step = -1;
		if(X_steps > 0) X_one_step = 1;
		int Y_one_step = -1;
		if(Y_steps > 0) Y_one_step = 1;

		if(abs(X_steps)>=abs(Y_steps)){
			while(X_steps != 0){
//				Serial.println("wtf");
				X_Stepper.step(X_one_step);
				X_steps -= X_one_step;
				int Y_should_go = X_Stepper.get_pos()*m - Y_Stepper.get_pos();
				// Serial.println(X_steps);
				if(Y_should_go!=0){
					Y_Stepper.step(Y_should_go);
				}
			}

			Y_Stepper.step(next_Y - Y_Stepper.get_pos());
		}

		else{
			while(Y_steps != 0){
				//Serial.println("wtff");
				Y_Stepper.step(Y_one_step);
				Y_steps -= Y_one_step;
				int X_should_go = X_Stepper.get_pos()*m - Y_Stepper.get_pos();
				if(X_should_go!=0){
					X_Stepper.step(X_should_go);
				}
			}

			X_Stepper.step(next_X - X_Stepper.get_pos());
		}

		Serial.println("End Move");
		
	}

//	void Move_Stepper_Circular_R(bool dir, float X, float Y, float R){
//		// TODO
//	}
//
//	void Move_Stepper_Circular_IJ(bool dir, float X, float Y, float I, float J){
//		// TODO
//	}
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

	float X_coordinate() { return (float)X_Stepper.get_pos()*X_Milis_Per_Step; }
	float Y_coordinate() { return (float)Y_Stepper.get_pos()*Y_Milis_Per_Step; }
	
/**************** Coordinate end ****************/

/**************** Kill / Halt start ****************/
	// TODO

/**************** Kill / Halt end ****************/
