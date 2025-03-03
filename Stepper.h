#pragma once

#include <Arduino.h>

#include <AccelStepper.h>
#include <Adafruit_MotorShield.h>

class Stepper{
public:

  void setup();
  void loop();

  static void forwardstep1();
  static void backwardstep1();
  static void forwardstep2();
  static void backwardstep2();

  AccelStepper stepper1;
  AccelStepper stepper2;
};