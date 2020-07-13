/**************************************************************************
	FileName		[ gcode_parser.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Parse the input to Gcode arrays ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#pragma once

#include "gcode_headers.h"
#include "my_vector.h"


/**************** Parser start ****************/
	vector<String> Gcode_Parser(String cmd){
		vector<String> parsed_data;
		
		int currentIndex = 0;
		bool isalpha = false;
		bool isF = false;
		String value;
		
		while( currentIndex < cmd.length()){
			char currentChar = cmd[currentIndex++];
//			Serial.println(currentChar);
			
			if (currentChar == 'F'){ // case F
				parsed_data.push_back(value); // push current value in vector
				//value = currentChar;
				isF = true; // mark appear of F
			}
			else if (currentChar == '.'){// add decimal point
				
				value += currentChar;
				continue;
				
			}
			else if (currentChar == ' '){ //skip blankspace
				continue;
			}
			else if (!isDigit(currentChar) && !isalpha){ //non-digit & first alpha(like G)
				
				isalpha = true;
				value += currentChar;
				
				
			}else if (!isDigit(currentChar) && isalpha){// non-digit & other alpha(like X,Y)
				if (!isF){
//					Serial.println(value);
					parsed_data.push_back(value); // push non F value to vector 
					value = currentChar; // renew the value
				}else{
					value = currentChar; // renew the value
					isF = false; 
				}
				
				
			}
			else{
				
				value += currentChar; // add digit to value
				
			}	
		}
		if (!isF){ //push last non F value to vector
//				Serial.println(value);
				parsed_data.push_back(value);
			}
//		Serial.println("======Parsing Complete!======");
		return parsed_data;
		
		
	}
/**************** Parser end ****************/
