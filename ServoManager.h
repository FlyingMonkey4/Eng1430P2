#include <Arduino.h>

#include <Servo.h>

struct ServoMotor{

  ServoMotor(uint8_t pin);

  void run();

  int pos;
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