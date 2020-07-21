/**************************************************************************
	FileName		[ Elevate_Gcode.ino ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Gcode Firmware for the NTUEE CNC Drawing Machine ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#include "configuration.h"
#include "gcode/gcode_headers.h"
#include "motor/motor_driver.h"

void setup() {
	Serial.begin(Baudrate);

	Pen_init(Servo_Pin);

	X_Stepper.init(X_Stepper_Invert);
	X_Stepper.setEndstop(X_Endstop_Pin, X_Endstop_Invert);
	Y_Stepper.init(Y_Stepper_Invert);
	Y_Stepper.setEndstop(Y_Endstop_Pin, Y_Endstop_Invert);
}

String cmd = "";
vector<String> params;

void loop() {
	if(Serial.available()){
		cmd = Serial.readStringUntil('\n'); // read in command
		// temperary dirty code
		if(cmd == "U"){
			Move_Pen(false);
      Serial.write("complete\n");
		}
		else if(cmd == "D"){
			Move_Pen(true);
      Serial.write("complete\n");
		}
		else if (cmd!=""){
			params = Gcode_Parser(cmd); // parse and return params
			Seperator(params); // seperate to G/M translator => motor driving 
      Serial.write("complete\n");
		}
	}
}
