/**************************************************************************
	FileName		[ gcode_mheader.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Gcode Mx Cases ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#pragma once
#include "my_vector.h"
#include "../motor/motor_driver.h"

/**************** M-code Translator start ****************/
	void M_Code_Translator(int num, vector<String> v){
		#ifdef DEBUG
			Serial.println("M_code_translator...");
			Serial.print("code index:");
			Serial.println(num);
		#endif

		switch(num){
			case 84: // enable
				Enable_Stepper_X();
				Enable_Stepper_Y();
				break;
			case 112: // Kill
			case 410: // Halt
				Serial.println("Warning: Please directly plug out");
				Serial.println("or turn off the switch.");
				break;
			case 280: // Servo
				int P = -1;
				int deg = 400;

				for(int i = 0; i < v.size(); ++i){
					char target = v[i][0];
					if(target == 'P'){
						P = v[i].substring(1,v[i].length()).toInt();
					}
					else if(target == 'S'){
						deg = v[i].substring(1,v[i].length()).toInt();
					}
				}

				if(P != 0){
					Serial.print("Error: Servo #");
					Serial.print(P);
					Serial.println(" doesn't exists.");

					return;
				}
				if(deg >= 180 || deg <= -180){
					Serial.println("Error: Wrong degree.");
					return;
				}

				Pen_Degree(deg);
				break;
		}
	}
/**************** M-code Translator end ****************/
