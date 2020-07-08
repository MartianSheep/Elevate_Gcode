/**************************************************************************
	FileName		[ Elevate_Gcode.ino ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Gcode Firmware for the NTUEE CNC Writing Project ]
	Author			[ Teaching Group, Elevate, NTUEE]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present EESA, NTUEE, NTU, Taiwan]
**************************************************************************/

#include <Servo.h>
#include <Stepper.h>

#include "configuration.h"
#include "gcode_headers.h"
#include "motor_driver.h"

void setup() {
	Serial.begin(Baudrate);

	Pen_Servo.attach(Servo_Pin);
	Pen_Servo.write(Servo_Pen_Up_Angle);
	delay(200);

	X_Stepper.setSpeed(X_Stepper_Speed);
	Y_Stepper.setSpeed(Y_Stepper_Speed);
}

void loop() {
	// TODO
}
