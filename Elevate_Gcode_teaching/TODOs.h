/**************************************************************************
	FileName		[ TODOs.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ TODOs for students ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#pragma once

#include "configuration.h"
#include "gcode/gcode_translators.h"
#include "motor/motor_driver.h"

void CNC_Stepper::homing(){
	// keep going on one single direction until hit endstop
	// and set that position as 0
	now_pos = 0;
	digitalWrite(direction_pin, HIGH);

	while(!digitalRead(endstop_pin)){
		// TODO

		/***** Answers start *****/
			digitalWrite(step_pin, LOW);
			delayMicroseconds(Homing_Delay);
			digitalWrite(step_pin, HIGH);
		/***** Answers end *****/
	}
}

void Pen_Degree(int degree){
	// TODO

	/***** Answer start *****/
		if(degree > Servo_Pen_Limit_Angle)
			degree = Servo_Pen_Limit_Angle;

		Pen_Servo.write(degree);
		delay(Pen_Delay_Time);

		if(degree >= Servo_Pen_Up_Angle)
			Enabler.enable();
		else
			Enabler.disable();
	/***** Answer end *****/
}

void Gcode_Index_Switcher(int gcode_index, float X, float Y){
	switch(gcode_index){
		case 0:
			// TODO

			/***** Answer start *****/
				Move_to(X,Y);
			/***** Answer end *****/
			break;
		case 1:
			// TODO

			/***** Answer start *****/
				Move_Stepper_Linear(X,Y);
			/***** Answer end *****/
			break;
		case 28:
			// TODO

			/***** Answer start *****/
				Enabler.disable();
				X_Stepper.homing();
				Y_Stepper.homing();
				Enabler.enable();
			/***** Answer end *****/
			break;
		default:
			Serial.println("Error: command not implemented");
			break;
	}
}

void Move_Stepper_Linear(float X, float Y){
	// checking enabled
	if(Enabler.get_enable())
		Enabler.disable();

	int X_steps = X/Milis_Per_Step - X_Stepper.get_pos();
	int Y_steps = Y/Milis_Per_Step - Y_Stepper.get_pos();

	bool X_direction = (X_steps >= 0); // positive is true, negative is false
	bool Y_direction = (Y_steps >= 0);

	char flag = ' '; // to decide which axis will rise

	float TX = X_Stepper_Period;
	float TY = Y_Stepper_Period;

	float X_period = 30000; // assigned as inf
	float Y_period = 30000; // assigned as inf

	long total_time = 0;

	if(abs(X_steps) > abs(Y_steps)){
		total_time = abs(X_steps) * TX;
		X_period = X_Stepper_Period;
		if(Y_steps != 0)
			Y_period = (float)total_time / abs(Y_steps);
	}
	else {
		total_time = abs(Y_steps) * TY;
		Y_period = Y_Stepper_Period;
		if(X_steps != 0)
			X_period = (float)total_time / abs(X_steps);
	}
	
	if(X_period > Y_period)
		flag = 'Y';
	else if(X_period < Y_period)
		flag = 'X';
	else
		flag = 'E';

	unsigned int total_steps = abs(X_steps) + abs(Y_steps);
	unsigned int current_steps = 0;
	
	float tx = X_period;
	float ty = Y_period;

	unsigned long last_rising = millis();

	while(current_steps < total_steps){
		if((int)(millis() - last_rising) < min(tx, ty))
			continue;
		else{
			if(X_steps > 0)
				digitalWrite(X_Stepper.get_direction_pin(), LOW);
			else
				digitalWrite(X_Stepper.get_direction_pin(), HIGH);

			if(Y_steps > 0)
				digitalWrite(Y_Stepper.get_direction_pin(), LOW);
			else
				digitalWrite(Y_Stepper.get_direction_pin(), HIGH);

			switch (flag){
			case 'X':
				digitalWrite(X_Stepper.get_step_pin(), LOW);
				delayMicroseconds(motor_delay_time);
				digitalWrite(X_Stepper.get_step_pin(), HIGH);

				last_rising = millis();

				++current_steps;

				ty -= tx;
				tx = X_period;
				if(tx > ty)
					flag = 'Y';
				else if(tx == ty)
					flag = 'E';
				break;
			
			case 'Y':
				digitalWrite(Y_Stepper.get_step_pin(), LOW);
				delayMicroseconds(motor_delay_time);
				digitalWrite(Y_Stepper.get_step_pin(), HIGH);

				last_rising = millis();

				++current_steps;

				// TODO

				/***** Answer start *****/
					tx -= ty;
					ty = Y_period;
					if(tx < ty)
						flag = 'X';
					else if(tx == ty)
						flag = 'E';
				/**** Answer end *****/
				break;
			
			case 'E':
				digitalWrite(X_Stepper.get_step_pin(), LOW);
				digitalWrite(Y_Stepper.get_step_pin(), LOW);
				delayMicroseconds(motor_delay_time);
				digitalWrite(X_Stepper.get_step_pin(), HIGH);
				digitalWrite(Y_Stepper.get_step_pin(), HIGH);

				last_rising = millis();

				current_steps += 2;

				tx = X_period;
				ty = Y_period;
				if(tx > ty)
					flag = 'Y';
				else if (tx < ty)
					flag = 'X';

				break;

			default:
				break;
			}
		}
	}
	X_Stepper.new_pos(X_steps);
	Y_Stepper.new_pos(Y_steps);
}