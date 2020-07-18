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
#include "gcode_gheader.h"
#include "gcode_mheader.h"

/**************** Seperator start ****************/
	void Seperator(vector<String> cmd){
		#ifdef DEBUG		
			Serial.println("Seperator...");
		#endif

		String gcode_head = cmd[0];
		char gcode_type = gcode_head[0];
		int gcode_index = gcode_head.substring(1,gcode_head.length()).toInt();

		vector<String> params;
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
