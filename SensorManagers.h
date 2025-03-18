#pragma once

#include <Arduino.h>

#include <Adafruit_seesaw.h>
#include <Arduino_APDS9960.h>
#include <Adafruit_VL53L0X.h>

#include "TimeManager.h"

//Soil Sensor
namespace SoilSensor {
  extern float tempC;
  extern uint16_t capread;

  extern bool toggleState;

  void setup();
  void run();
}

//Proximity/Gesture/Colour sensor
namespace ProxGestColSensor{
  extern int proximity;
  extern int r, g, b;

  void setup();
  void run();
}


namespace TimeOfFlightSensor{
  extern VL53L0X_RangingMeasurementData_t measure;

  void setup();
  void run();
}