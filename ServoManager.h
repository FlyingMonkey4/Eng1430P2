#include <Arduino.h>

#include <Servo.h>

struct ServoMotor{
public:
  ServoMotor(uint8_t pin);

  ///1.0 degree per second.
  void setMaxSpeed(float speed);
  void setAcceleration(float accel);
  void moveTo(int loc);
  int distanceToGo();
  int currentPosition();

  void run();

private:
  float speed,accel;
  int pos,desiredPos;
  Servo servo;
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