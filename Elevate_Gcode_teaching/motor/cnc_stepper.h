/**************************************************************************
	FileName		[ cnc_stepper.h ]
	PackageName		[ Elevate_Gcode ]
	Function		[ Stepper Related Class in CNC Project ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
**************************************************************************/

#pragma once

class Enable_Controller
{
public:
	Enable_Controller(unsigned int ena_pin = 0){
		enabled = false;
		enable_pin = ena_pin;
	}
	~Enable_Controller() {};

	/**************** Settings start ****************/
		void init(){
			pinMode(enable_pin, OUTPUT);
			enable();
		}
	/**************** Settings end ****************/

	/**************** Enabling start ****************/
		void enable(){ // enable the motor for manual control
			enabled = true;
			digitalWrite(enable_pin, HIGH);
		}

		void disable(){ // machine overtaking the control
			enabled = false;
			digitalWrite(enable_pin, LOW);
		}

		bool get_enable() { return enabled; }
	/**************** Enabling start ****************/
private:
	bool			enabled;
	// enable means that if human can turn the motor by hand
	// motor should be disabled during machine process
	unsigned int	enable_pin;
};

class CNC_Stepper
{
public:
	CNC_Stepper(unsigned int st_pin = 0,
				unsigned int dir_pin = 0){

		step_pin = st_pin;
		direction_pin = dir_pin;

		now_pos = 0;
	}
	~CNC_Stepper() {};

	/**************** Settings start ****************/
		void init(){
			pinMode(step_pin, OUTPUT);
			pinMode(direction_pin, OUTPUT);
		}

		void setEndstop(unsigned int end_pin){
			endstop_pin = end_pin;
			pinMode(endstop_pin, INPUT_PULLUP);
		}
	/**************** Settings end ****************/

	/**************** Moving and Positions start ****************/
		void homing();

		int get_pos() { return now_pos; }
		void set_pos(int new_pos) { now_pos = new_pos; }
		void new_pos(int x){ now_pos += x; }
	/**************** Moving and Positions end ****************/

	/**************** Get Pin start ****************/
		unsigned int get_step_pin(){ return step_pin; }
		unsigned int get_direction_pin(){ return direction_pin; }
	/**************** Get Pin end ****************/

private:
	unsigned int	step_pin;
	unsigned int	direction_pin;
	unsigned int	endstop_pin;

	int				now_pos;
	// the unit of now_pos should be steps
};
