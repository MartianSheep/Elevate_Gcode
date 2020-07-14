/**************************************************************************
	FileName		[ Elevate_Gcode.ino ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Gcode Firmware for the NTUEE CNC Drawing Machine ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#include <Servo.h>
#include <Stepper.h>

#include "configuration.h"
#include "gcode/gcode_headers.h"
#include "motor/motor_driver.h"

void setup() {
	Serial.begin(Baudrate);

	Pen_Servo.attach(Servo_Pin);
	Pen_Servo.write(Servo_Pen_Up_Angle);
	delay(Pen_Delay_Time);

	X_Stepper.init(X_Stepper_Invert);
	X_Stepper.setEndstop(X_Endstop_Pin, X_Endstop_Invert);
	Y_Stepper.init(Y_Stepper_Invert);
	Y_Stepper.setEndstop(Y_Endstop_Pin, Y_Endstop_Invert);
}

String cmd = "";

void loop() {
	cmd = Serial.readStringUntil('\n'); //readin command
	vector<String> params = Gcode_Parser(cmd); //parse and return params
	Seperator(params); // seperate to G/M translator => motor driving
}
