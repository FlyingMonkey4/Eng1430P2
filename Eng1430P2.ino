#include "Stepper.h"
#include "ServoManager.h"
#include "TimeManager.h"
#include "SensorManagers.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("in setup");

  //Calls getInstance to make sure a manager is created
  StepperManager::getInstance();
  // ServoManager::getInstance();
  SoilSensor::setup();
  // ProxGestColSensor::setup();
  // TimeOfFlightSensor::setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  TimeManager::update();
  
  //update sensor data before reaching motors
  SoilSensor::run();
  // ProxGestColSensor::run();
  // TimeOfFlightSensor::run();

  StepperManager::getInstance()->run();
  // ServoManager::getInstance()->run();

}
