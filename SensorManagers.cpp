#include "SensorManagers.h"

//updates onces every given amount of milliseconds
#define SOIL_SENSOR_UPDATE_INTERVAL_MS 30000

namespace SoilSensor {
  static Adafruit_seesaw sensor;
  static bool sensorInitialized = false;  // Track initialization status
  float tempC=0;
  uint16_t capread=0;

  static unsigned long lastUpdateTime=0;

  void setup() {

    sensor = Adafruit_seesaw();

    if (!sensor.begin(0x36)) {
      Serial.println("ERROR! Soil sensor not found");
      sensorInitialized = false;  // Mark as not initialized
    } else {
      Serial.print("Seesaw started! Version: ");
      Serial.println(sensor.getVersion(), HEX);
      sensorInitialized = true;  // Mark as successfully initialized
    }
  }

  void run() {
    if (sensorInitialized){
      unsigned long currentMillis = millis();  // Get current time
      if (currentMillis - lastUpdateTime >= SOIL_SENSOR_UPDATE_INTERVAL_MS) {  
        lastUpdateTime = currentMillis;  // Reset timer
        
        tempC = sensor.getTemp();
        capread = sensor.touchRead(0);

        Serial.print("Temperature: ");
        Serial.print(tempC);
        Serial.println("°C");

        Serial.print("Capacitive: ");
        Serial.println(capread);
      }
    }
  }
}



//SET TRUE IF YOU WANT THAT DATA COLLECTED
#define PROX_STATUS false
#define GEST_STATUS false
#define COL_STATUS true

//updates onces every given amount of milliseconds
#define PROXGESTCOL_SENSOR_UPDATE_INTERVAL_MS 30000

namespace ProxGestColSensor{
  static bool sensorInitialized = false;  // Track initialization status

  int proximity = 0;
  int r = 0, g = 0, b = 0;
  
  static unsigned long lastUpdateTime=0;

  
  void setup(){
    if(!APDS.begin()){
      Serial.println("ERROR! Failed to initializing APDS-9960(ProxGestColSensor) sensor");
    }else{
      sensorInitialized=true;
    }
  }

  void run(){
    if(sensorInitialized){
      unsigned long currentMillis = millis();  // Get current time
      if (currentMillis - lastUpdateTime >= PROXGESTCOL_SENSOR_UPDATE_INTERVAL_MS) {  
        lastUpdateTime = currentMillis;  // Reset timer

        // Check if a proximity reading is available.
        if (APDS.proximityAvailable()&&PROX_STATUS) {
          proximity = APDS.readProximity();
        }

        // // Check if a gesture reading is available
        if (APDS.gestureAvailable()&&GEST_STATUS) {
          int gesture = APDS.readGesture();
          switch (gesture) {
            case GESTURE_UP:
              Serial.println("Detected UP gesture");
              break;

            case GESTURE_DOWN:
              Serial.println("Detected DOWN gesture");
              break;

            case GESTURE_LEFT:
              Serial.println("Detected LEFT gesture");
              break;

            case GESTURE_RIGHT:
              Serial.println("Detected RIGHT gesture");
              break;

            default:
              // Ignore
              break;
          }
        }

        // Check if a color reading is available
        if (APDS.colorAvailable()&&COL_STATUS) {
          APDS.readColor(r, g, b);
        }
      }
    }
  }
}



#define FLIGHT_SENSOR_UPDATE_INTERVAL_MS 30000

namespace TimeOfFlightSensor{
  static Adafruit_VL53L0X lox = Adafruit_VL53L0X();

  static bool sensorInitialized = false;  // Track initialization status

  VL53L0X_RangingMeasurementData_t measure;

  static unsigned long lastUpdateTime=0;
  

  void setup(){
    if (!lox.begin()) {
      Serial.println("ERROR! Failed to boot VL53L0X");
    }else{
      sensorInitialized=true;
    }
  }

  void run(){
    if(sensorInitialized){
      unsigned long currentMillis = millis();  // Get current time
      if (currentMillis - lastUpdateTime >= FLIGHT_SENSOR_UPDATE_INTERVAL_MS) {  
        lastUpdateTime = currentMillis;  // Reset timer

        lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
      }
    }
  }
}