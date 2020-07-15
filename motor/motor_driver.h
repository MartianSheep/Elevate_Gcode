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

/**************** Servo start ****************/
	void Pen_init(unsigned int pin){
		Pen_Servo.attach(pin);
		Pen_Servo.write(Servo_Pen_Up_Angle);
		delay(Pen_Delay_Time);
	}

	void Pen_Degree(int degree){
		#ifdef DEBUG
			Serial.print("Servo: moving to ");
			Serial.print(degree);
			Serial.println(" degree.");
		#endif

		Pen_Servo.write(degree);
		delay(Pen_Delay_Time);
	}

	void Move_Pen(bool down){
		if(down){
			#ifdef DEBUG
				Serial.println("Servo: Pen down");
			#endif
			Pen_Degree(Servo_Pen_Down_Angle);
		}
		else{
			#ifdef DEBUG
				Serial.println("Servo: Pen up");
			#endif
			Pen_Degree(Servo_Pen_Up_Angle);
		}
		return;
	}
/**************** Servo end ****************/

/**************** Stepper Moving start ****************/
	void Move_Stepper_Linear(float X, float Y){
		#ifdef DEBUG
			Serial.println("Linear moving...");
		#endif
		
		long now_X = X_Stepper.get_pos();
		long now_Y = Y_Stepper.get_pos();

		long next_X = X/X_Milis_Per_Step;
		long next_Y = Y/Y_Milis_Per_Step;

		#ifdef DEBUG
			Serial.print("X/X_Milis_Per_Step: ");
			Serial.println(X/X_Milis_Per_Step);
			Serial.print("next_X: ");
			Serial.println(next_X);

			Serial.print("Y/Y_Milis_Per_Step: ");
			Serial.println(Y/Y_Milis_Per_Step);
			Serial.print("next_Y: ");
			Serial.println(next_Y);
		#endif

		long X_steps = next_X - now_X;
		long Y_steps = next_Y - now_Y;
		
		float m = 0;
		if(X_steps!=0) m = Y_steps/X_steps;

		// Stepper_Smallest_Step is "1" in configuration.h
		int X_one_step = -Stepper_Smallest_Step;
		if(X_steps > 0) X_one_step = Stepper_Smallest_Step;
		int Y_one_step = -Stepper_Smallest_Step;
		if(Y_steps > 0) Y_one_step = Stepper_Smallest_Step;

		if(abs(X_steps)>=abs(Y_steps)){
			while(X_steps != 0){
				X_Stepper.step(X_one_step);
				X_steps -= X_one_step;
				int Y_should_go = X_Stepper.get_pos()*m - Y_Stepper.get_pos();
				if(Y_should_go!=0){
					Y_Stepper.step(Y_should_go);
				}
			}

			Y_Stepper.step(next_Y - Y_Stepper.get_pos());
		}

		else{
			while(Y_steps != 0){
				Y_Stepper.step(Y_one_step);
				Y_steps -= Y_one_step;
				int X_should_go = X_Stepper.get_pos()*m - Y_Stepper.get_pos();
				if(X_should_go!=0){
					X_Stepper.step(X_should_go);
				}
			}

			X_Stepper.step(next_X - X_Stepper.get_pos());
		}

		#ifdef DEBUG
			Serial.println("End Move");
		#endif
	}

	//	Not going to implement in this version
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

	void set_X_coordinate(float new_pos){
		// TODO
	}
	void set_Y_coordinate(float new_pos){
		// TODO
	}
	
/**************** Coordinate end ****************/

/**************** Kill / Halt start ****************/
	// TODO
	// Not going to implement in this version
	// Please directly shut down the machine
	// to kill the system
/**************** Kill / Halt end ****************/
