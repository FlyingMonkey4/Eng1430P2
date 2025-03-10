#pragma once

#include <Arduino.h>

#include <Adafruit_seesaw.h>
#include <Arduino_APDS9960.h>
#include <Adafruit_VL53L0X.h>

#include "TimeManager.h"

//Soil Sensor
namespace SoilSensor {
  extern Adafruit_seesaw* sensor;  // Declare it as extern since it's defined in the cpp file
  extern bool sensorInitialized;  // Track if initialization was successful

  extern float tempC;
  extern uint16_t capread;

  extern unsigned long lastUpdateTime;

  void setup();
  void run();
}

//Proximity/Gesture/Colour sensor
namespace ProxGestColSensor{
  extern bool sensorInitialized;  // Track if initialization was successful

  extern int proximity;
  extern int r, g, b;

  extern unsigned long lastUpdateTime;

  void setup();
  void run();
}


namespace TimeOfFlightSensor{
  extern Adafruit_VL53L0X lox;

  extern bool sensorInitialized;  // Track if initialization was successful

  extern VL53L0X_RangingMeasurementData_t measure;

  extern unsigned long lastUpdateTime;

  void setup();
  void run();
}