/**************************************************************************
	FileName		[ motor_driver.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Motor Driver for the NTUEE CNC Writing Project ]
	Author			[ Teaching Group, Elevate, NTUEE]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present EESA, NTUEE, NTU, Taiwan]
**************************************************************************/

#pragma once

#include "configuration.h"

#include <Servo.h>
#include <Stepper.h>

/**************** Macro Definitions of Motors start ****************/
	Stepper X_Stepper(StepsPerRevolution, X_Stepper_Step_Pin, X_Stepper_Dir_Pin);
	Stepper Y_Stepper(StepsPerRevolution, Y_Stepper_Step_Pin, Y_Stepper_Dir_Pin);

	Servo Pen_Servo;
/**************** Macro Definitions of Motors end ****************/