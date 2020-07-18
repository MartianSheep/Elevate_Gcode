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
#include "../motor/motor_driver_second_edition.h"

/**************** M-code Translator start ****************/
	void M_Code_Translator(int num, vector<String> v){
		#ifdef DEBUG
			Serial.println("M_code_translator...");
			Serial.print("code index:");
			Serial.println(num);
		#endif

		// TODO
		// M84: unlock and enable all motors
			// this is going to enable x and enable y
		// M92: changing steps per unit (not going to implement)
		// M203: changing feedrate (not going to implement)
		// M201: changing motor acceleration (not going to implement)
		// M112: Kill (just print message I guess?)
		// M410: Halt (just print message I guess?)
		// M280: Servo, controlling pen up and pen down
			// M280 P<servo #> S<degree>
			// So we're gonna be
			// M280 P0 S90
			// M280 P0 S60
			// etc.

		// U: Pen Up (not standard gcode)
		// D: Pen Down (not standard gcode)
	}
/**************** M-code Translator end ****************/
