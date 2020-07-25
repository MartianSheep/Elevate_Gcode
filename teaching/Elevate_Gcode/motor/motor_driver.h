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
#include "../TODOs.h"
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

	// void Pen_Degree(int degree){

	// 	//TOD

	// }
/**************** Servo end ****************/

/**************** Stepper Moving start ****************/
	void Move_to(float X, float Y){
		int X_steps = X/X_Milis_Per_Step - X_Stepper.get_pos();
		int Y_steps = Y/Y_Milis_Per_Step - Y_Stepper.get_pos();

		if(X_steps > 0){
			if(X_Stepper.inverted_status())
				digitalWrite(X_Stepper.get_direction_pin(), LOW);
			else
				digitalWrite(X_Stepper.get_direction_pin(), HIGH);
		}
		else{
			if(X_Stepper.inverted_status())
				digitalWrite(X_Stepper.get_direction_pin(), HIGH);
			else
				digitalWrite(X_Stepper.get_direction_pin(), LOW);
		}

		X_steps = abs(X_steps);
		Y_steps = abs(Y_steps);

		while(X_steps > 0){
			digitalWrite(X_Stepper.get_step_pin(), LOW);

			delayMicroseconds(300);

			digitalWrite(X_Stepper.get_step_pin(), HIGH);

			--X_steps;
		}

		if(Y_steps > 0){
			if(Y_Stepper.inverted_status())
				digitalWrite(Y_Stepper.get_direction_pin(), LOW);
			else
				digitalWrite(Y_Stepper.get_direction_pin(), HIGH);
		}
		else{
			if(Y_Stepper.inverted_status())
				digitalWrite(Y_Stepper.get_direction_pin(), HIGH);
			else
				digitalWrite(Y_Stepper.get_direction_pin(), LOW);
		}

		while(Y_steps > 0){
			digitalWrite(Y_Stepper.get_step_pin(), LOW);

			delayMicroseconds(300);

			digitalWrite(Y_Stepper.get_step_pin(), HIGH);

			--Y_steps;
		}
	}

	void Move_Stepper_Linear(float X, float Y){
		// #ifdef DEBUG
		// 	Serial.println("Linear moving...");
		// #endif
		
		// Serial.println("Linear moving");

		// Serial.print("X_Stepper.get_pos(): ");
		// Serial.print(X_Stepper.get_pos());
		// Serial.print("\tY_Stepper.get_pos(): ");
		// Serial.println(Y_Stepper.get_pos());

		int X_steps = X/X_Milis_Per_Step - X_Stepper.get_pos();
		int Y_steps = Y/Y_Milis_Per_Step - Y_Stepper.get_pos();

		// Serial.print("X_Steps: ");
		// Serial.print(X_steps);
		// Serial.print("\t Y_steps: ");
		// Serial.println(Y_steps);

		bool X_direction = (X_steps >= 0); //positive is true, negative is false
		bool Y_direction = (Y_steps >= 0);

		char flag = ' ';//to decide which axis will rise

		float TX = X_Stepper_Period;
		float TY = Y_Stepper_Period;

		float X_period=30000;
		float Y_period=30000;

		long total_time = 0;

		if(abs(X_steps) > abs(Y_steps)){
			total_time = abs(X_steps) * TX;
			X_period = X_Stepper_Period;
			if(Y_steps!=0)
				Y_period = (float)total_time/abs(Y_steps);
		}
		else {
			total_time = abs(Y_steps) * TY;
			Y_period = Y_Stepper_Period;
			if(X_steps!=0)
				X_period = (float)total_time/abs(X_steps);
		}
		
		if(X_period > Y_period) flag = 'Y';
		else if(X_period < Y_period) flag = 'X';
		else flag = 'E';

		unsigned int total_steps = abs(X_steps) + abs(Y_steps);
		unsigned int current_steps = 0;
		
		float tx = X_period;
		float ty = Y_period;

		// Serial.print("X_period: ");
		// Serial.print(X_period);
		// Serial.print("\tY_period: ");
		// Serial.println(Y_period);

		unsigned long last_rising = millis();

		while(current_steps < total_steps){
			if((int)(millis() - last_rising) < min(tx, ty)) {

				continue;

			}
			else{
				if(X_steps > 0){
					if(X_Stepper.inverted_status())
						digitalWrite(X_Stepper.get_direction_pin(), LOW);
					else
						digitalWrite(X_Stepper.get_direction_pin(), HIGH);
				}
				else{
					if(X_Stepper.inverted_status())
						digitalWrite(X_Stepper.get_direction_pin(), HIGH);
					else
						digitalWrite(X_Stepper.get_direction_pin(), LOW);
				}

				if(Y_steps > 0){
					if(Y_Stepper.inverted_status())
						digitalWrite(Y_Stepper.get_direction_pin(), LOW);
					else
						digitalWrite(Y_Stepper.get_direction_pin(), HIGH);
				}
				else{
					if(Y_Stepper.inverted_status())
						digitalWrite(Y_Stepper.get_direction_pin(), HIGH);
					else
						digitalWrite(Y_Stepper.get_direction_pin(), LOW);
				}
				
				switch (flag){
				case 'X':
					digitalWrite(X_Stepper.get_step_pin(), LOW);

					delayMicroseconds(50);

					digitalWrite(X_Stepper.get_step_pin(), HIGH);

					//Serial.println("X");

					last_rising = millis();

					++current_steps;

					ty -= tx;
					tx = X_period;
					if(tx>ty) flag = 'Y';
					else if(tx == ty) flag = 'E';
					break;
				
				case 'Y':
					digitalWrite(Y_Stepper.get_step_pin(), LOW);

					delayMicroseconds(50);

					digitalWrite(Y_Stepper.get_step_pin(), HIGH);

					//Serial.println("Y");

					last_rising = millis();


					++current_steps;

					flag = Y_next();

					break;
				
				case 'E':
					digitalWrite(X_Stepper.get_step_pin(), LOW);
					digitalWrite(Y_Stepper.get_step_pin(), LOW);
					delayMicroseconds(50);
					digitalWrite(X_Stepper.get_step_pin(), HIGH);
					digitalWrite(Y_Stepper.get_step_pin(), HIGH);

					//Serial.println("E");

					last_rising = millis();

					current_steps += 2;

					tx = X_period;
					ty = Y_period;
					if(tx > ty) flag = 'Y';
					else if (tx < ty) flag = 'X';

					break;

				default:
					break;
				}
			}
		}
		X_Stepper.new_pos(X_steps);
		Y_Stepper.new_pos(Y_steps);
		// Serial.print("X_Stepper.get_pos(): ");
		// Serial.print(X_Stepper.get_pos());
		// Serial.print("\tY_Stepper.get_pos(): ");
		// Serial.println(Y_Stepper.get_pos());
		// Serial.println("End Moving");
	}
/**************** Stepper Moving end ****************/

/**************** Stepper Enable start ****************/
	void Enable_Stepper_X(bool enable = true){
		if(enable)	X_Stepper.enable();
		else 		X_Stepper.disable();
	}

	void Enable_Stepper_Y(bool enable = true){
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
		X_Stepper.set_pos(new_pos/X_Milis_Per_Step);
	}
	void set_Y_coordinate(float new_pos){
		Y_Stepper.set_pos(new_pos/Y_Milis_Per_Step);
	}
	
/**************** Coordinate end ****************/
