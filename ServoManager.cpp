#include "ServoManager.h"

//SET TO TRUE OR FALSE TO ACTIVATE MOTOR PORT
#define SERVO1_STATUS false
#define SERVO2_STATUS true

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

#define SERVO1_SPEED_TIME_PER_60DEG 0.18  // Time for 60° rotation (in seconds) from max speed (1.08s per 360)
#define SERVO2_SPEED_TIME_PER_60DEG 0.18  // Time for 60° rotation (in seconds)

//IF SET TO FALSE, MOVETO WILL ONLY BE USED TO DETERMINE DIRECTION
#define SERVO1_IGNORE_MOVETO false
#define SERVO2_IGNORE_MOVETO false

//
#define SERVO1_MAX_SPEED 1.15

//
//SERVOMOTOR     SERVOMOTOR     SERVOMOTOR     SERVOMOTOR
//

ServoMotor::ServoMotor(uint8_t pin) {
  maxSpeed = 0.0;
  speed = 0.0;
  accel = 0.0;
  floatPos=0;
  pos = 0;
  desiredPos = 0;

  this->pin=pin;
  servo.attach(pin);
}

void ServoMotor::run() {
  // Acceleration logic: gradually adjust currentSpeed toward speed
  if((pin==SERVO1_PIN&&!SERVO1_IGNORE_MOVETO)||(pin==SERVO2_PIN&&!SERVO2_IGNORE_MOVETO)){
    floatPos+=speed*TimeManager::getDeltaTime();
  }
  pos=(int) floatPos;
  int8_t direction = (desiredPos > pos) - (desiredPos < pos); // Equivalent to (1, -1, or 0)
  


  if (speed < maxSpeed * direction) {
    speed += accel * TimeManager::getDeltaTime();
    if (speed > maxSpeed * direction) speed = maxSpeed * direction;  // Prevent overshooting
  } else if (speed > maxSpeed * direction) {
    speed -= accel * TimeManager::getDeltaTime();
    if (speed < maxSpeed * direction) speed = maxSpeed * direction;  // Prevent overshooting
  }

  if((pin==SERVO1_PIN&&!SERVO1_IGNORE_MOVETO)||(pin==SERVO2_PIN&&!SERVO2_IGNORE_MOVETO)){
    //Handles Speed Adjustment if pos is equal to desiredPos 
    //or if speed will overlap pos then set pos to desired pos
    //accuracy doesnt matter a ton since its a servo motor and 
    //i dont have the time to do it right
    if(pos==desiredPos){
      speed=0;
    }else{
      //checks if pos will overshoot the desired pos and adjust based on last deltatime
      if (direction * (pos + speed * TimeManager::getDeltaTime()) > direction * desiredPos) {
          speed = (desiredPos - pos) / TimeManager::getDeltaTime();
          pos = desiredPos;
      }
    }
  }

  int pwmValue=0;

  if(pin==SERVO1_PIN){
    // Convert speed (degrees per second) to PWM value
    pwmValue = (speed * (0.18 / 60) * 500) + SERVO1_SPEED_STOP;

    // Apply deadzone if enabled
    if (SERVO1_DEADZONE_STATUS && abs(speed) < SERVO1_SPEED_DEADZONE) {
      pwmValue = SERVO1_SPEED_STOP;
    } else {
        pwmValue = (speed * (0.18 / 60) * 500) + SERVO1_SPEED_STOP;
    }

    // Ensure PWM stays within range
    pwmValue = constrain(pwmValue, SERVO1_SPEED_MIN, SERVO1_SPEED_MAX);
  }
  if(pin==SERVO2_PIN){
    // Convert speed (degrees per second) to PWM value
    pwmValue = (speed * (0.18 / 60) * 500) + SERVO2_SPEED_STOP;

    // Apply deadzone if enabled
    if (SERVO2_DEADZONE_STATUS && abs(speed) < SERVO2_SPEED_DEADZONE) {
      pwmValue = SERVO2_SPEED_STOP;
    } else {
        pwmValue = (speed * (0.18 / 60) * 500) + SERVO2_SPEED_STOP;
    }

    // Ensure PWM stays within range
    pwmValue = constrain(pwmValue, SERVO2_SPEED_MIN, SERVO2_SPEED_MAX);
  }

  // Write new speed to servo
  servo.writeMicroseconds(pwmValue);
  if (((pin==SERVO1_PIN&&!SERVO1_IGNORE_MOVETO)||(pin==SERVO2_PIN&&!SERVO2_IGNORE_MOVETO))&&pos == desiredPos) {
    if (direction != (desiredPos > pos) - (desiredPos < pos)) { 
        speed = 0; // Reset speed only if direction changed
    }
  }
}

void ServoMotor::setMaxSpeed(float maxSpeed) {
  this->maxSpeed = maxSpeed;
}

void ServoMotor::setAcceleration(float accel) {
  this->accel = accel;
}

void ServoMotor::moveTo(int loc) {
  desiredPos = loc;
}

void ServoMotor::setCurrentPosition(int newPos) {
  this->pos = newPos;
}

int ServoMotor::distanceToGo() {
  return desiredPos - pos;
}

int ServoMotor::currentPosition() {
  return pos;
}



//
//SERVOMANAGER     SERVOMANAGER     SERVOMANAGER     SERVOMANAGER
//

//statis inits
ServoManager* ServoManager::s_Instance = nullptr;

ServoMotor* ServoManager::servos[2] = { nullptr };

ServoManager::ServoManager() {
  if (SERVO1_STATUS) {
    servos[0] = new ServoMotor(SERVO1_PIN);

    servos[0]->setMaxSpeed(-360.0);
    servos[0]->setAcceleration(100.0);
    servos[0]->moveTo(24);
  }

  if (SERVO2_STATUS) {
    servos[1] = new ServoMotor(SERVO2_PIN);

    servos[1]->setMaxSpeed(100.0);
    servos[1]->setAcceleration(10.0);
    servos[1]->moveTo(24);
  }
}

ServoManager::~ServoManager() {
}

ServoManager* ServoManager::getInstance() {
  if (!s_Instance) {
    s_Instance = new ServoManager();
  }
  return s_Instance;
}

void ServoManager::run() {
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

  if (SERVO1_STATUS)
    servos[0]->run();
  if (SERVO2_STATUS)
    servos[1]->run();
}