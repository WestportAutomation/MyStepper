#include "MyStepper.h"

#define Disable LOW
#define Enable HIGH

MyStepper::MyStepper() {

}

void MyStepper::init(int en, int dir, int step, int home) {
	EnPin = en;
	DirPin = dir;
	StepPin = step;
	HomePin = home;

	pinMode(EnPin, OUTPUT);
	pinMode(DirPin, OUTPUT);		
	pinMode(StepPin, OUTPUT);
	pinMode(HomePin, INPUT_PULLUP); // Home pin is an input with pullup
	_Error = 0;
	_PreviousSteps = 0;
	_Steps = 0;
	digitalWrite(EnPin, Disable); // Disable the stepper driver
	digitalWrite(DirPin, LOW); // Set the direction to low

	if (_StartUP) {
		// If this is the first time we are starting up, we need to home the motor
		// This is a safety feature to ensure the motor starts in a known position
		Home();
		_StartUP = false; // Set startup to false after homing
	}
}

void MyStepper::Step(long steps, bool dir) {  // step the motor the number of steps in the direction passed in to func.  chk the system hasn't reached home.  
	digitalWrite(EnPin, Enable); //Enable is activelow
	digitalWrite(DirPin, dir);
	while (_Error < steps && digitalRead(HomePin)) {
		digitalWrite(StepPin, HIGH);
		delayMicroseconds(_Fast);
		digitalWrite(StepPin, LOW);
		delayMicroseconds(_Fast);
		_Error++;
	}	
	_PreviousSteps = _Error;
	_Error = 0;  // Reset error
	if (!_Holding) {
		// If we are not holding the motor, we can disable the stepper driver
		digitalWrite(EnPin, Disable); // Disable the stepper driver
	}
}

void MyStepper::setDir(bool dir) {
	digitalWrite(DirPin, dir);
}

void MyStepper::setEn(bool en) {
	digitalWrite(EnPin, en);
}

void MyStepper::Home() {
	digitalWrite(DirPin, _HomeDir);  // Set the direction to HomeDir for homing. Have to determine which way the motor needs to go to hit the home switch
	digitalWrite(EnPin, Enable); // Enable the stepper driver
	while (digitalRead(HomePin))
	{
		analogWrite(StepPin, 100);
	}
	if (!_Holding) {
		// If we are not holding the motor, we can disable the stepper driver
		digitalWrite(EnPin, Disable); // Disable the stepper driver
	}
}