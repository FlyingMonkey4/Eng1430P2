#include "Stepper.h"

Adafruit_MotorShield AFMSbot(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMStop(0x60); // Default address, no jumpers

// Connect two steppers with 200 steps per revolution (1.8 degree)
// to the top shield
Adafruit_StepperMotor *myStepper1 = AFMStop.getStepper(200, 1);
Adafruit_StepperMotor *myStepper2 = AFMStop.getStepper(200, 2);

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void Stepper::forwardstep1() {
  myStepper1->onestep(FORWARD, SINGLE);
}
void Stepper::backwardstep1() {
  myStepper1->onestep(BACKWARD, SINGLE);
}
// wrappers for the second motor!
void Stepper::forwardstep2() {
  myStepper2->onestep(FORWARD, DOUBLE);
}
void Stepper::backwardstep2() {
  myStepper2->onestep(BACKWARD, DOUBLE);
}

void Stepper::setup(){

  // Now we'll wrap the 3 steppers in an AccelStepper object
  stepper1=AccelStepper(forwardstep1, backwardstep1);
  stepper2=AccelStepper(forwardstep2, backwardstep2);

  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield

  stepper1.setMaxSpeed(100.0);
  stepper1.setAcceleration(100.0);
  stepper1.moveTo(24);

  stepper2.setMaxSpeed(200.0);
  stepper2.setAcceleration(100.0);
  stepper2.moveTo(50000);

}

void Stepper::loop(){

    // Change direction at the limits
    if (stepper1.distanceToGo() == 0)
	stepper1.moveTo(-stepper1.currentPosition());

    if (stepper2.distanceToGo() == 0)
	stepper2.moveTo(-stepper2.currentPosition());


    stepper1.run();
    stepper2.run();
}