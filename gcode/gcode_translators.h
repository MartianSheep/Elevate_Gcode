/**************************************************************************
	FileName		[ gcode_headers.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Gcode headers package and Seperator ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#pragma once

#include "gcode_parser.h"
#include "my_vector.h"
#include "../motor/motor_driver.h"

/**************** G-code Translator start ****************/
	void G_Code_Translator(int gcode_index, vector<vector<char>> v){
		// #ifdef DEBUG
		// 	Serial.print("G_code_translator, code index: ");
		// 	Serial.println(gcode_index);
		// #endif

		float X = X_coordinate();
		float Y = Y_coordinate();

		for (int i=0; i<v.size();i++){
			vector<char> param = v[i]; //param_type+param_num(X or Y)
			char param_type = param[0]; 


			//generate param_num
			String param_num_string = "";
			for (int i = 1; i < param.size(); i++){
				param_num_string += param[i];
			}

			switch(param_type){
				case 'X':
					// param = param.substring(1,param.length());
					X = param_num_string.toFloat();
					break;
				case 'Y':
					// param = param.substring(1,param.length());
					Y = param_num_string.toFloat();
					break;
				default:
					Serial.println("Gcode Translator: ");
					Serial.println(param_type);
					Serial.println("Error, other params");
					return;
			}
		}

		#ifdef DEBUG
			Serial.print("X: ");
			Serial.print(X);
			Serial.print(" Y: ");
			Serial.print(Y);
			Serial.println();
		#endif

		switch(gcode_index){
			case 0:
				// G0: Linear move without extrusion(but we don't have that at first)
				//     so I think it's a seperator between each curve;
				Move_to(X,Y);
				// Move_Stepper_Linear(X,Y);
				break;
			case 1:
				// G1: Linear move with extrusion, which would really draw a line;
				Move_Stepper_Linear(X,Y); 
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
				// G92: set position and return now position;
				if(X != X_coordinate())
					set_X_coordinate(X);
				if(Y != Y_coordinate())
					set_Y_coordinate(Y);
				Serial.print("Now Position: (");
				Serial.print( X_coordinate() );
				Serial.print(',');
				Serial.print( Y_coordinate() );
				Serial.print(')');
				Serial.println();
				break;
			default:
				Serial.println("Error, command not implemented");
				break;
		}
		return;
	}
/**************** G-code Translator end ****************/

/**************** M-code Translator start ****************/
	void M_Code_Translator(int gcode_index, vector<vector<char>> v){
		// #ifdef DEBUG
		// 	Serial.println("M_code_translator...");
		// 	Serial.print("code index:");
		// 	Serial.println(gcode_index);
		// #endif

		switch(gcode_index){
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
						// P = v[i].substring(1,v[i].length()).toInt();

						// generate P
						String P_string = "";
						for (int j = 1; j < v[i].size(); j++){
							P_string += v[i][j];
						}
						P = P_string.toInt();
					}
					else if(target == 'S'){
						// deg = v[i].substring(1,v[i].length()).toInt();
						// generate deg
						String deg_string = "";
						for (int j = 1; j < v[i].size(); j++){
							deg_string += v[i][j];
						}
						deg = deg_string.toInt();
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
/**************** Seperator start ****************/
	void Seperator(vector<vector<char>> cmd){
		#ifdef DEBUG		
			Serial.println("Seperator...");
		#endif

		vector<char> gcode_head = cmd[0]; //gcode_type+gcode_index
		char gcode_type = gcode_head[0];

		// int gcode_index = gcode_head.substring(1,gcode_head.size()).toInt();
		// generate gcode_index
		String gcode_index_string = "";
		for (int i = 1; i < gcode_head.size(); i++){
			gcode_index_string += gcode_head[i];
		}

		int gcode_index = gcode_index_string.toInt();

		// generate params to translator
		vector<vector<char>> params;
		for (int i=1;i<cmd.size();i++){
			params.push_back(cmd[i]);
		}

		switch (gcode_type){
			case 'G':
				G_Code_Translator(gcode_index, params);
				break;
			case 'M':
				M_Code_Translator(gcode_index, params);
				break;
			default:
				Serial.print("Unknown gcode_type: \"");
				Serial.print(gcode_type);
				Serial.println("\".");
		}

		#ifdef DEBUG
			Serial.println("/*****Seperator ends*****/");
		#endif
	}
/**************** Seperator end ****************/

