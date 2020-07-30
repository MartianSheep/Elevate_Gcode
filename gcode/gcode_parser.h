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

// /**************** Parser start ****************/
// 	vector<String> Gcode_Parser(String cmd){
// 		vector<String> parsed_data;
// 		#ifdef DEBUG
// 			Serial.print("Parser parsing: \"");
// 			Serial.print(cmd);
// 			Serial.println("\"...");
// 		#endif

// 		int currentIndex = 0;
// 		bool isalpha = false;
// 		bool isF = false;
// 		String value = "";
		
// 		while( currentIndex < cmd.length() ){
// 			char currentChar = cmd[currentIndex++];

// 			if (currentChar == 'F'){ // case F
// 				parsed_data.push_back(value); // push current value in vector
// 				isF = true; // mark appear of F
// 			}
// 			else if (currentChar == '.'){// add decimal point
// 				value += currentChar;
// 				continue;
// 			}
// 			else if (currentChar == ' '){ //skip blankspace
// 				continue;
// 			}
// 			else if (!isDigit(currentChar) && !isalpha){ //non-digit & first alpha(like G)
// 				isalpha = true;
// 				value += currentChar;
// 			}
// 			else if (!isDigit(currentChar) && isalpha){// non-digit & other alpha(like X,Y)
// 				if (!isF){
// 					parsed_data.push_back(value); // push non F value to vector 
// 					value = currentChar; // renew the value
// 				}else{
// 					value = currentChar; // renew the value
// 					isF = false; 
// 				}
// 			}
// 			else{
// 				value += currentChar; // add digit to value
// 			}
// 		}

// 		if (!isF){ // push last non F value to vector
// 			parsed_data.push_back(value);
// 		}

// 		#ifdef DEBUG
// 			Serial.println("======Parsing Complete!======");
// 			Serial.print("Parsed data: ");
// 			parsed_data.print();
// 		#endif

// 		return parsed_data;
// 	}
// /**************** Parser end ****************/

/**************** Parser Char* start ****************/
	vector<vector<char>> Gcode_Parser(char *cmd, int len){
		
		// const int MAX_VALUE_LEN = 10;

		// #ifdef DEBUG
		// 	Serial.print("Parser parsing: \"");
		// 	// Serial.print(cmd);
		// 	Serial.println("\"...");
		// #endif

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