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
#include "../TODOs.h"

/**************** G-code Translator start ****************/
	void G_Code_Translator(int gcode_index, vector<vector<char>> v){
		float X = X_coordinate();
		float Y = Y_coordinate();

		for (int i = 0; i < v.size(); ++i){
			vector<char> param = v[i];
			char param_type = param[0];

			// generate param_num
			String param_num_string = "";
			for (int i = 1; i < param.size(); ++i){
				param_num_string += param[i];
			}

			switch(param_type){
				case 'X':
					X = param_num_string.toFloat();

					if(X < 0){
						Serial.println("Warning: X axis out of bed range.");
						Serial.println("System auto adjust to the end of bed.");
						X = 0;
					}
					else if(X > Bed_Size){
						Serial.println("Warning: X axis out of bed range.");
						Serial.println("System auto adjust to the end of bed.");
						X = Bed_Size;						
					}

					break;
				case 'Y':
					Y = param_num_string.toFloat();

					if(Y < 0){
						Serial.println("Warning: Y axis out of bed range.");
						Serial.println("System auto adjust to the end of bed.");
						Y = 0;
					}
					else if(Y > Bed_Size){
						Serial.println("Warning: Y axis out of bed range.");
						Serial.println("System auto adjust to the end of bed.");
						Y = Bed_Size;						
					}
					
					break;
				default:
					Serial.println("Gcode Translator: ");
					Serial.println(param_type);
					Serial.println("Error, other params");
					return;
			}
		}

		Gcode_Index_Switcher(gcode_index, X, Y);
		return;
	}
/**************** G-code Translator end ****************/

/**************** M-code Translator start ****************/
	void M_Code_Translator(int gcode_index, vector<vector<char>> v){
		switch(gcode_index){
			case 84:
				Enabler.enable();
				break;
			case 280:
				int P = -1;
				int deg = 400;

				for(int i = 0; i < v.size(); ++i){
					char target = v[i][0];
					if(target == 'P'){
						// generate P
						String P_string = "";
						for (int j = 1; j < v[i].size(); ++j){
							P_string += v[i][j];
						}
						P = P_string.toInt();
					}
					else if(target == 'S'){
						// generate deg
						String deg_string = "";
						for (int j = 1; j < v[i].size(); ++j){
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
			default:
				Serial.println("Error: command not implemented");
				break;
		}
	}
/**************** M-code Translator end ****************/
	
/**************** Seperator start ****************/
	void Seperator(vector<vector<char>> cmd){
		vector<char> gcode_head = cmd[0];
		char gcode_type = gcode_head[0];

		// generate gcode_index
		String gcode_index_string = "";
		for (int i = 1; i < gcode_head.size(); ++i)
			gcode_index_string += gcode_head[i];

		int gcode_index = gcode_index_string.toInt();

		// generate params to translator
		vector<vector<char>> params;
		for (int i = 1; i < cmd.size(); ++i)
			params.push_back(cmd[i]);

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
	}
/**************** Seperator end ****************/

