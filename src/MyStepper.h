#ifndef MYSTEPPER_H
#define MYSTEPPER_H
#include <Arduino.h>

/* Stepper library -- designed for microstep driver
StepPin used both digitalWrite and analogWrite so it needs to be connected to a pwm pin

Westport Automation - 2025
*/

class MyStepper
{

private:
	int StepPin;
	int DirPin;
	int EnPin;
	int HomePin;
	long _PreviousSteps;
	long _Steps;
	int _Fast = 100;
	int _Slow = 800;
	long _Error = 0;
	bool _StartUP = true;
	bool _Holding = true; // If true, the stepper driver is enabled and holding the motor in place. default is true
	bool _HomeDir = false; // Direction to home the motor, default is false (low)

public:

	MyStepper();
	void init(int, int, int, int);
	void Home();
	void Step(long,bool);
	void setDir(bool);
	void setEn(bool);
	void setHolding(bool holding) { _Holding = holding; } // Set whether the stepper driver is holding the motor in place
	bool isHolding() { return _Holding; } // Check if the stepper driver is holding the motor in place
	void setHomeDir(bool dir) { _HomeDir = dir; } // Set the direction to home the motor, default is false (low)
};
#endif
