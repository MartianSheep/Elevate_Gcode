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
		
		String gcode_head = cmd[0];
		char gcode_type = gcode_head.charAt(0);
		int gcode_index = gcode_head.substring(1,gcode_head.length()-1).toInt()
		
		vector<String> params;
		for (i=1;i<cmd.size();i++){
			params.push_back(cmd[i]);
		}
		
		switch (gcode_type){
			case 'G':
				G_Code_Translator(gcode_index, params);
			case 'M':
				M_Code_Translator(gcode_index, params);
		} 
	}
/**************** Seperator end ****************/
