#include <Arduino.h>
#include <DabbleESP32.h>
#include "driver/pcnt.h"

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#define motorAp 25
#define motorBp 13
#define pwmch_1 0
#define pwmch_2 1

const int motorA1 = 27;
const int motorA2 = 26;

const int STBY = 12;

const int motorB1 = 32; // IN1
const int motorB2 = 33; // IN2

void setup()
{
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorAp, OUTPUT);

  pinMode(STBY, OUTPUT);

  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(motorBp, OUTPUT);

  ledcSetup(pwmch_1, 12800, 8);
  ledcSetup(pwmch_2, 12800, 8);

  ledcAttachPin(motorAp, pwmch_1);
  ledcAttachPin(motorBp, pwmch_2);

  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);

  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);

  digitalWrite(STBY, HIGH);

  Dabble.begin("Bluth");
  Serial.begin(9600);
  Serial.println("Motor Standby");
}

void loop()
{
  Dabble.processInput(); 
  if (GamePad.isUpPressed())
  {
    ledcWrite(pwmch_1, 200);
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    ledcWrite(pwmch_2, 200);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
  }

  if (GamePad.isDownPressed())
  {
    // Serial.println("motorA back");
    ledcWrite(pwmch_1, 200);
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    // Serial.println("motorB back");
    ledcWrite(pwmch_2, 200);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);
  }
  if (GamePad.isCrossPressed())
  {
    // Serial.println("motorA stop");
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    ledcWrite(pwmch_1, 0);
    // Serial.println("motorB stop");
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
    ledcWrite(pwmch_2, 0);
  }
  if (GamePad.isCirclePressed())
  {
    // Serial.println("motorA back");
    ledcWrite(pwmch_1, 200);
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    // Serial.println("motorB forward");
    ledcWrite(pwmch_2, 200);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
  }

  if (GamePad.isSquarePressed()){ 
    // Serial.println("motorA forward");
    ledcWrite(pwmch_1, 200);
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    // rial.println("motorB back");
    ledcWrite(pwmch_2, 200);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);
  }
  if (GamePad.isRightPressed()){
    // Serial.println("motorA slow");
    ledcWrite(pwmch_1, 200);
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    // Serial.println("motorB forward");
    ledcWrite(pwmch_2, 256);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
  }
  if (GamePad.isLeftPressed())
  {
    // Serial.println("motorA forward");
    ledcWrite(pwmch_1, 256);
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    // Serial.println("motorB slow");
    ledcWrite(pwmch_2, 200);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
  }
}