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
		unsigned int step_pin, unsigned int dir_pin, unsigned int ena_pin){
		// TODO: inverted motor?
		motor = Stepper(steps_per_round, step_pin, dir_pin);
		enable_pin = ena_pin;

		now_pos = 0;
		enabled = false;
		inverted = false;
	}
	~CNC_Stepper() {};

	/**************** Settings start ****************/
		void setSpeed(float speed){
			motor.setSpeed(speed);
		}

		void setInvert() { inverted = true; }

		void homing(){
			// TODO
		}
	/**************** Settings end ****************/

	/**************** Moving start ****************/
		void step(float steps){
			// TODO: inverted motor?
			motor.step(steps);
		}

		void move_to(float pos){
			// TODO: inverted motor?
			motor.step(pos - now_pos);
		}
	/**************** Moving end ****************/

	/**************** Enable start ****************/
		void enable(){
			// TODO
		}

		void disable(){
			// TODO
		}

		bool get_enable() { return enabled; }
	/**************** Enable end ****************/

private:
	Stepper			motor;
	bool			enabled;
	bool			inverted;
	unsigned int	enable_pin;
	float			now_pos;
};