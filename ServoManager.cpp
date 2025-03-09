#include "ServoManager.h"

//SET TO TRUE OR FALSE TO ACTIVATE MOTOR PORT
#define SERVO1_STATUS true
#define SERVO2_STATUS false

//pin 10 Servo1, pin 9 Servo2
#define SERVO1_PIN 10
#define SERVO2_PIN 9

//SERVO SPEEDS
//CAN ALSO ADJUST POTENTIOMETER
#define SERVO1_SPEED_STOP 1500
#define SERVO2_SPEED_STOP 1500
#define SERVO1_SPEED_MIN 1000
#define SERVO2_SPEED_MIN 1000
#define SERVO1_SPEED_MAX 2000
#define SERVO2_SPEED_MAX 2000

#define SERVO1_DEADZONE_STATUS false
#define SERVO2_DEADZONE_STATUS false
//Plus or minus from the servo stop speed
#define SERVO1_SPEED_DEADZONE 20
#define SERVO2_SPEED_DEADZONE 20

#define SERVO1_SPEED_TIME_PER_60DEG 0.18 // Time for 60° rotation (in seconds) from max speed (1.08s per 360)
#define SERVO2_SPEED_TIME_PER_60DEG 0.18 // Time for 60° rotation (in seconds)

//
#define SERVO1_MAX_SPEED 1.15

//
//SERVOMOTOR     SERVOMOTOR     SERVOMOTOR     SERVOMOTOR
//

ServoMotor::ServoMotor(uint8_t pin){
  speed=0.0;accel=0.0;
  pos=0;desiredPos=0;
  
  servo.attach(pin);
}

void ServoMotor::run(){
  //move towards desired position
}

void ServoMotor::setMaxSpeed(float speed){
  this->speed=speed;
}

void ServoMotor::setAcceleration(float accel){
  this->accel=accel;
}

void ServoMotor::moveTo(int loc){
  desiredPos=loc;
}

int ServoMotor::distanceToGo(){
  return desiredPos-pos;
}

int ServoMotor::currentPosition(){
  return pos;
}



//
//SERVOMANAGER     SERVOMANAGER     SERVOMANAGER     SERVOMANAGER
//

//statis inits
ServoManager* ServoManager::s_Instance=nullptr;

ServoMotor* ServoManager::servos[2]={nullptr};

ServoManager::ServoManager(){
  if(SERVO1_STATUS){
    servos[0]=new ServoMotor(SERVO1_PIN);

    servos[0]->setMaxSpeed(100.0);
    servos[0]->setAcceleration(100.0);
    servos[0]->moveTo(24);
  }

  if(SERVO2_STATUS){
    servos[1]=new ServoMotor(SERVO1_PIN);

    servos[1]->setMaxSpeed(100.0);
    servos[1]->setAcceleration(100.0);
    servos[1]->moveTo(24);
  }
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
  //MOTOR1 ACTIVITIES :D
  if (SERVO1_STATUS) {
    if (servos[0]->distanceToGo() == 0) {
      servos[0]->moveTo(-servos[0]->currentPosition());
    }
  }

  //MOTOR2 ACTIVITIES :D
  if (SERVO2_STATUS) {
    if (servos[1]->distanceToGo() == 0) {
      servos[1]->moveTo(-servos[1]->currentPosition());
    }
  }

  if(SERVO1_STATUS)
    servos[0]->run();
  if(SERVO2_STATUS)
    servos[1]->run();
}