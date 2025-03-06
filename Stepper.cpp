#include "Stepper.h"

//adafruit board stuff
Adafruit_MotorShield AFMSbot(0x61);  // Rightmost jumper closed
Adafruit_MotorShield AFMStop(0x60);  // Default address, no jumpers

//SET TO TRUE OR FALSE TO ACTIVATE MOTOR PORT
#define MOTOR1_STATUS true
#define MOTOR2_STATUS false
#define MOTOR3_STATUS false

#define MOTOR1_STEPS_PER_REV 100
#define MOTOR2_STEPS_PER_REV 200
#define MOTOR3_STEPS_PER_REV 200

//SINGLE, DOUBLE, INTERLEAVE or MICROSTEP
#define MOTOR1_STYLE DOUBLE
#define MOTOR2_STYLE SINGLE
#define MOTOR3_STYLE SINGLE


//MOTOR STEP FUNCTIONS
namespace StepperMotor {
void mf0() {
  StepperManager::motors[0]->onestep(FORWARD, MOTOR1_STYLE);
}
void mb0() {
  StepperManager::motors[0]->onestep(BACKWARD, MOTOR1_STYLE);
}
void mf1() {
  StepperManager::motors[1]->onestep(FORWARD, MOTOR2_STYLE);
}
void mb1() {
  StepperManager::motors[1]->onestep(BACKWARD, MOTOR2_STYLE);
}
void mf2() {
  StepperManager::motors[2]->onestep(FORWARD, MOTOR3_STYLE);
}
void mb2() {
  StepperManager::motors[2]->onestep(BACKWARD, MOTOR3_STYLE);
}
}



//
//    STEPPERMANAGER       STEPPERMANAGER       STEPPERMANAGER       STEPPERMANAGER
//

//static Inits
StepperManager* StepperManager::s_Instance = nullptr;

Adafruit_StepperMotor* StepperManager::motors[3] = { nullptr };
AccelStepper StepperManager::motorWraps[3];



StepperManager::StepperManager() {
  //TODO SEE IF MORE ADAFRUIT STUFF USES THIS AND IF SO CREATE ITS OWN BOARD SETUP
  AFMSbot.begin();  // Start the bottom shield
  AFMStop.begin();  // Start the top shield

  if (MOTOR1_STATUS) {
    motors[0] = AFMStop.getStepper(MOTOR1_STEPS_PER_REV, 1);
    motorWraps[0] = AccelStepper(StepperMotor::mf0, StepperMotor::mb0);

    motorWraps[0].setMaxSpeed(100.0);
    motorWraps[0].setAcceleration(100.0);
    motorWraps[0].moveTo(24);
  }
  if (MOTOR2_STATUS) {
    motors[2] = AFMStop.getStepper(MOTOR1_STEPS_PER_REV, 2);
    motorWraps[1] = AccelStepper(StepperMotor::mf1, StepperMotor::mb1);

    motorWraps[1].setMaxSpeed(200.0);
    motorWraps[1].setAcceleration(100.0);
    motorWraps[1].moveTo(50000);
  }
  if (MOTOR3_STATUS) {
    motors[2] = AFMStop.getStepper(MOTOR1_STEPS_PER_REV, 3);
    motorWraps[2] = AccelStepper(StepperMotor::mf2, StepperMotor::mb2);

    motorWraps[2].setMaxSpeed(300.0);
    motorWraps[2].setAcceleration(100.0);
    motorWraps[2].moveTo(1000000);
  }
}

StepperManager::~StepperManager() {
}

StepperManager* StepperManager::getInstance() {
  if (!s_Instance) {
    s_Instance = new StepperManager();
  }
  return s_Instance;
}

void StepperManager::run() {

  //MOTOR1 ACTIVITIES :D
  if (MOTOR1_STATUS) {
    if (motorWraps[0].distanceToGo() == 0) {
      motorWraps[0].moveTo(-motorWraps[0].currentPosition());
    }
  }

  //MOTOR2 ACTIVITIES :D
  if (MOTOR2_STATUS) {
    if (motorWraps[1].distanceToGo() == 0) {
      motorWraps[1].moveTo(-motorWraps[1].currentPosition());
    }
  }

  //MOTOR3 ACTIVITIES :D
  if (MOTOR3_STATUS) {
    if (motorWraps[2].distanceToGo() == 0) {
      motorWraps[2].moveTo(-motorWraps[2].currentPosition());
    }
  }

  if(MOTOR1_STATUS)
    motorWraps[0].run();
  if(MOTOR2_STATUS)
    motorWraps[1].run();
  if(MOTOR3_STATUS)
    motorWraps[2].run();
}