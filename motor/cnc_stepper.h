/**************************************************************************
	FileName		[ cnc_stepper.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Stepper Related Class in CNC Project ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#pragma once

#include <Stepper.h>

class CNC_Stepper
{
public:
	CNC_Stepper(unsigned int steps_per_round,
				unsigned int step_pin,
				unsigned int dir_pin,
				unsigned int ena_pin){

		motor = Stepper(steps_per_round, step_pin, dir_pin);
		enable_pin = ena_pin;

		now_pos = 0;
		enabled = false;
		inverted = false;
	}
	~CNC_Stepper() {};

	/**************** Settings start ****************/
		void setSpeed(int speed){
			motor.setSpeed(speed);
		}

		void setInvert() { inverted = true; }

		void setEndstop(unsigned int end_pin, bool end_inv){
			// this function can only be called in setup() in main.ino
			endstop_pin = end_pin;
			endstop_inverted = end_inv;

			pinMode(endstop_pin, OUTPUT);
		}
	/**************** Settings end ****************/

	/**************** Moving start ****************/
		void step(int steps){ // moving the motor by giving steps
			disable();

			if(inverted)
				steps = -steps;

			motor.step(steps);
			now_pos += steps;
		}

		void homing(){
			// TODO
			// keep going on one single direction until hit endstop
			// and set that position as 0
			now_pos = 0;
		}

		int get_pos() { return now_pos; }

		void set_pos(int new_pos) { // force to set now_pos
			now_pos = new_pos;
		}
	/**************** Moving end ****************/

	/**************** Enable start ****************/
		void enable(){ // enable the motor for manual control
			enabled = true;
			digitalWrite(enable_pin, HIGH);
		}

		void disable(){ // machine overtaking the control
			enabled = false;
			digitalWrite(enable_pin, LOW);
		}

		bool get_enable() { return enabled; }
	/**************** Enable end ****************/

private:
	Stepper			motor;

	bool			enabled;
	// enable means that if human can turn the motor by hand
	// motor should be disabled during machine process
	// and enable by enable()
	// not sure if we can do enable() after a process is done
	// so that the motor won't keep making noise while halt

	bool			inverted;
	// if the motor's direction is inverted
	bool			endstop_inverted;
	// if the endstop's output is inverted
	// would like to set to 0 if homing is not done
	// and set 1 if the machine hits the endstop
	// if endstop inverted, 1 for not done 0 for hit

	unsigned int	enable_pin;
	unsigned int	endstop_pin;

	int				now_pos;
	// the unit of now_pos should be steps
};