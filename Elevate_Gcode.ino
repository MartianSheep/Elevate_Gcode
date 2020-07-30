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

void setup() {
	Serial.begin(Baudrate);

	Pen_init(Servo_Pin);

	X_Stepper.init(X_Stepper_Invert);
	X_Stepper.setEndstop(X_Endstop_Pin, X_Endstop_Invert);
	Y_Stepper.init(Y_Stepper_Invert);
	Y_Stepper.setEndstop(Y_Endstop_Pin, Y_Endstop_Invert);
}

int sofar = 0;
char buf[MAX_BUF];
vector<vector<char>> params;

void loop(){
	if( Serial.available()){
		char c = Serial.read();
		if ( sofar < MAX_BUF ) {
			buf[sofar++]=c;
			if (c == '\n'){
				buf[sofar]=0;
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
