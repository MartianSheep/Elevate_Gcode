/**************************************************************************
	FileName		[ gcode_gheader.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Gcode Gx cases ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#pragma once
#include "my_vector.h"
#include "../motor/motor_driver.h"

/**************** G-code Translator start ****************/
	void G_Code_Translator(int num, vector<String> v){
		float X;
		float Y;
		for (int i=0; i<v.size();i++){
			String param = v[i];
			char param_type = param.charAt(0);
			switch(param_type){
				case 'X':
					X = param.setCharAt(0,'').toFloat();
				case 'Y':
					Y = param.setCharAt(0,'').toFloat();
				default:
					Serial.println("Error, other params");
					return;
			}
		}
		//================ for debug ===================
//		Serial.print("X:");
//		Serial.print(X);
//		Serial.print(" Y:");
//		Serial.print(Y);
//		Serial.println();
		//================ for debug ===================
		switch(num){
			case 0:
				// G0: Linear move without extrusion(but we don't have that at fitst)
				//     so I think it's a seperator between each curve;
			case 1:
				// G1: Linear move with extrusion, which would really draw a line;
				break;
			case 21:
				// G21: set units to milimeters;
				break;
			case 28:
				X_homing();
				Y_homing();
				break;
			case 90:
				// G90: set coordinate to absolute;
				break;
			case 92:
				// G92: set position;
				break;
			default:
				Serial.println("Error, command not implemented");
				return;
		}
	}
/**************** G-code Translator end ****************/
