#pragma once

#include <Arduino.h>

#include <Servo.h>

#include "TimeManager.h"

struct ServoMotor{
public:
  ServoMotor(uint8_t pin);

  ///1.0 degree per second.
  void setMaxSpeed(float maxSpeed);
  void setAcceleration(float accel);
  void moveTo(int loc);
  void setCurrentPosition(int newPos);
  int distanceToGo();
  int currentPosition();

  void run();

private:
  float maxSpeed, accel;            //  must always positive
  float speed, floatPos;            // Signed speed (can be positive or negative), floatPos stores the slowly (relative to delta time) increasing position
  int pos, desiredPos;              // Positions (signed integers)
  Servo servo;                      // Servo object
  uint8_t pin;                      // Servos pin
};



class ServoManager{
public:
  virtual ~ServoManager();


  static ServoManager* getInstance();

  void run();

  static ServoMotor* servos[];
private:
  ServoManager();

  static ServoManager* s_Instance;
};