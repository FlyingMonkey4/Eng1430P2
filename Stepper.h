#pragma once

#include <Arduino.h>

#include <AccelStepper.h>
#include <Adafruit_MotorShield.h>

extern Adafruit_MotorShield AFMSbot; // Rightmost jumper closed
extern Adafruit_MotorShield AFMStop; // Default address, no jumpers

class StepperManager{
public:
  virtual ~StepperManager();

  static StepperManager* getInstance();

  void run();

  static Adafruit_StepperMotor* motors[];
  static AccelStepper motorWraps[];
private:

  static StepperManager* s_Instance;

  StepperManager();
};