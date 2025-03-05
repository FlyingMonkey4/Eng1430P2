#include "Stepper.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("in setup");
  StepperManager::getInstance();
}

void loop() {
  // put your main code here, to run repeatedly:
  StepperManager::getInstance()->run();
}
