#include <Arduino.h>
#include "Class/MotorDriverClass.h"

MotorDriver motor1(9,8,10);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motor1.initialize();
  
}

void loop() 
{
  motor1.rotateDegrees(-90);
}