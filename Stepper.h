#pragma once

#include <Arduino.h>
#include <HardwareSerial.h>

#include <AccelStepper.h>
#include <Adafruit_MotorShield.h>


//TODO check to see if all adafruit motorshield products use the same pins, if so then just make a h file that inits these values
extern Adafruit_MotorShield AFMSbot; // Rightmost jumper closed
extern Adafruit_MotorShield AFMStop; // Default address, no jumpers

struct StepperMotor {
public:
  virtual ~StepperMotor();

  StepperMotor() : stepperMotor(nullptr) {}

  StepperMotor(uint8_t motorPort, uint8_t steps=200);

  //local variables
  uint8_t motorPort;

  Adafruit_StepperMotor* stepperMotor; // The actual stepper motor
  AccelStepper stepperWrap; // Wrapper for AccelStepper
};

class StepperManager{
public:
  virtual ~StepperManager();

  static StepperManager* getInstance();
  void run();

  static void addMotor(uint8_t motorPort);
  static const StepperMotor* getMotor(uint8_t motorPort);

  const uint8_t getNumOfMotors(){return numOfMotors;} 

private:
  StepperManager();


  //Manager Variables
  static StepperManager* s_Instance;

  //StepperMotor Variables
  static uint8_t numOfMotors;
  static StepperMotor* stepperMotors[];//motorNum, Motor*
};