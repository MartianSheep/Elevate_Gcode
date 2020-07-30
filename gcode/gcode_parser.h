/**************************************************************************
	FileName		[ gcode_parser.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Parse the input to Gcode arrays ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#pragma once

#include "my_vector.h"

/**************** Parser Char* start ****************/
	vector<vector<char>> Gcode_Parser(char *cmd, int len){
		
		#ifdef DEBUG
			Serial.print("Parser parsing: \"");
			Serial.print(cmd);
			Serial.println("\"...");
		#endif

		vector<vector<char>> parsed_data;

		vector<char> value;

		char currentChar;

		bool isF = false;

		for(int index = 0; index < len ; index++){

			currentChar = cmd[index];
			// #ifdef DEBUG
			// Serial.println(currentChar);
			// #endif
			if (currentChar == ' '){
				if(!isF){
					parsed_data.push_back(value); //insert param into vector 
					value.clear(); // clear value to accept next value
				}else{
					value.clear(); // clear value to accept next value
					isF = false; // set to not F state
				}
			}
			else {
				if (currentChar == 'F') isF = true;
				value.push_back(currentChar);
			}
		}

		if (!isF){
			parsed_data.push_back(value); // push in the last non-F params
		}

		return parsed_data;
	}
/**************** Parser Char* end ****************/