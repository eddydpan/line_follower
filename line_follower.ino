#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor * leftMotor = AFMS.getMotor(3);
Adafruit_DCMotor * rightMotor = AFMS.getMotor(4);

int sensorPin = A0;
int analog0 = 0;
int analog1 = 0;
int t;

void setup() {
  // put your setup code here, to run once:
  long baudRate = 9600;
  AFMS.begin();
  Serial.begin(baudRate);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  leftMotor->setSpeed(100);
  leftMotor->run(FORWARD);
  rightMotor->setSpeed(100);
  rightMotor->run(FORWARD);

  analog0 = analogRead(1);
  analog1 = analogRead(3);
  
  Serial.print(analog0);
  Serial.print(",");
  Serial.print(analog1);
  Serial.println(",");
}

