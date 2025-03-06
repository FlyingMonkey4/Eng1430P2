#include "ServoManager.h"

//SET TO TRUE OR FALSE TO ACTIVATE MOTOR PORT
#define SERVO1_STATUS true
#define SERVO2_STATUS false

//pin 10 Servo1, pin 9 Servo2
#define SERVO1_PIN 10
#define SERVO2_PIN 9

//
//SERVOMOTOR     SERVOMOTOR     SERVOMOTOR     SERVOMOTOR
//

ServoMotor::ServoMotor(uint8_t pin){

}

void ServoMotor::run(){

}



//
//SERVOMANAGER     SERVOMANAGER     SERVOMANAGER     SERVOMANAGER
//

//statis inits
ServoManager* ServoManager::s_Instance=nullptr;

ServoManager::ServoManager(){

}

ServoManager::~ServoManager(){

}

ServoManager* ServoManager::getInstance(){
  if(!s_Instance){
    s_Instance=new ServoManager();
  }
  return s_Instance;
}

void ServoManager::run(){

}