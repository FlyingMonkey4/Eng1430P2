#include "Stepper.h"

//Global variables
Adafruit_MotorShield AFMSbot(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMStop(0x60); // Default address, no jumpers

#define NUMBER_OF_STEP_PORTS 2//edit if more or less stepper ports are avalible

//
//
//    STEPPERMOTOR STRUCT      STEPPERMOTOR STRUCT     STEPPERMOTOR STRUCT      STEPPERMOTOR STRUCT
//
//

StepperMotor::StepperMotor(uint8_t motorPort, uint8_t steps) {
  // Connects stepper with # of steps per revolution, 360/steps=degree
  // to the top shield
  stepperMotor = AFMStop.getStepper(steps, motorPort);
  this->motorPort=motorPort;

  // Check if the motor is successfully initialized
  if (stepperMotor) {

    stepperWrap = AccelStepper(stepperMotor->onestep(FORWARD, SINGLE), stepperMotor->onestep(BACKWARD, SINGLE));

  } else {
    Serial.print("Error: Stepper motor ");
    Serial.print(motorPort);
    Serial.println(" failed to initialize!");
  }
}

StepperMotor::~StepperMotor(){
  //We're assuming that adafruit handles the Adafruit_StepperMotor* since the example doesnt delete it

  // delete type;
}

//
//
//     STEPPERMANAGER      STEPPERMANAGER      STEPPERMANAGER       STEPPERMANAGER
//
//

//Static inits
StepperManager* StepperManager::s_Instance=nullptr;

StepperMotor* StepperManager::stepperMotors[NUMBER_OF_STEP_PORTS]={nullptr};
uint8_t StepperManager::numOfMotors=0;



StepperManager* StepperManager::getInstance(){
  if(!s_Instance){
    Serial.println("Creating new Stepper");
    s_Instance=new StepperManager();
  }
  return s_Instance;
}

void StepperManager::addMotor(uint8_t motorPort){

}

StepperMotor* StepperManager::getMotor(uint8_t motorPort){
  if(false){

  }else{
    return nullptr;
  }
}

StepperManager::StepperManager(){
  /*
  * used to fetch stepper class that manages all stepper motors inside of a stepper struct object
  * 
  */

  Serial.print("start of stepper init");

  //Motor Setup
  //Add Motor to stepperMotors array
  //Set Max speed and Acceleration

  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield

  // stepperMotors[0].stepperWrap.setMaxSpeed(100.0);
  // stepperMotors[0].stepperWrap.setAcceleration(100.0);
  // stepperMotors[0].stepperWrap.moveTo(24);

  // stepperMotors[1].stepperWrap.setMaxSpeed(200.0);
  // stepperMotors[1].stepperWrap.setAcceleration(100.0);
  // stepperMotors[1].stepperWrap.moveTo(50000);

  Serial.println("end of stepper init");
}

StepperManager::~StepperManager(){
  delete[] stepperMotors;
}

void StepperManager::run(){
  Serial.print("INSIDE RUNN ");
    // Change direction at the limits
    // if (stepperMotors[0].stepperWrap.distanceToGo() == 0){
	  //   stepperMotors[0].stepperWrap.moveTo(-stepperMotors[0].stepperWrap.currentPosition());
    // }

    // if (stepperMotors[1].stepperWrap.distanceToGo() == 0){
	  //   stepperMotors[1].stepperWrap.moveTo(-stepperMotors[1].stepperWrap.currentPosition());
    // }
    // Serial.println(stepperMotors[0].stepperWrap.distanceToGo());

    // stepperMotors[0].stepperWrap.run();
    // stepperMotors[1].stepperWrap.run();
    // Serial.println("After run function");
}