#include "Stepper.h"
#include "ServoManager.h"
#include "TimeManager.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("in setup");

  //Calls getInstance to make sure a manager is created
  StepperManager::getInstance();
  ServoManager::getInstance();
}

void loop() {
  // put your main code here, to run repeatedly:
  TimeManager::update();
  
  StepperManager::getInstance()->run();
  ServoManager::getInstance()->run();

}
