/**************************************************************************
	FileName		[ Elevate_Gcode.ino ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Gcode Firmware for the NTUEE CNC Drawing Machine ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#include "configuration.h"
#include "gcode/gcode_translators.h"
#include "motor/motor_driver.h"
#include "TODOs.h"

void setup() {
	Serial.begin(Baudrate);

	Pen_init(Servo_Pin);

	X_Stepper.init();
	X_Stepper.setEndstop(X_Endstop_Pin);
	Y_Stepper.init();
	Y_Stepper.setEndstop(Y_Endstop_Pin);

	Enabler.init();
}

int sofar = 0;
char buf[MAX_BUF];
char c;
vector<vector<char>> params;

void loop(){
	if(Serial.available()){
		c = Serial.read();
		if ( sofar < MAX_BUF ) {
			buf[sofar++] = c;
			if (c == '\n'){
				buf[sofar] = 0;
				params = Gcode_Parser(buf,sofar);
				Seperator(params);

				delay(ACTION_TIME);

				Serial.println();
				Serial.print("complete\n");
				sofar = 0;
			}
		}
	}	
}
