#include <Arduino.h>
#include <DabbleESP32.h>
#include <MotorDriver.hpp>

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

const int motorR1 = 27;
const int motorR2 = 26;

const int motorL1 = 32;
const int motorL2 = 33;

const int motorRp = 25;
const int motorLp = 13;
const int pwmChannelRight = 0;
const int pwmChannelLeft = 1;

const int STBY = 12;
const int pwmFrequency = 12800;

MotorDrive motorRight = {
    motorR1,
    motorR2,
    motorRp,
    pwmChannelRight,
    pwmFrequency,
};

MotorDrive motorLeft = {
    motorL1,
    motorL2,
    motorLp,
    pwmChannelLeft,
    pwmFrequency,
};

void setup()
{
  motorRight.setup();
  motorLeft.setup();
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);
  motorRight.neutral();
  motorLeft.neutral();
  Dabble.begin("Bluth");
  Serial.begin(9600);
  Serial.println("Motor Standby");
}

void loop()
{
  Dabble.processInput();
  if (GamePad.isUpPressed())
  {
    motorRight.driveForward(200);
    motorLeft.driveForward(200);
  }

  if (GamePad.isDownPressed())
  {
    motorRight.driveBackward(200);
    motorLeft.driveBackward(200);
  }
  if (GamePad.isCrossPressed())
  {
    motorRight.stop();
    motorLeft.stop();
  }
  if (GamePad.isCirclePressed())
  {
    motorRight.driveBackward(200);
    motorLeft.driveForward(200);
  }

  if (GamePad.isSquarePressed())
  {
    motorRight.driveForward(200);
    motorLeft.driveBackward(200);
  }
  if (GamePad.isRightPressed())
  {
    motorRight.driveForward(200);
  }
  if (GamePad.isLeftPressed())
  {
    motorRight.driveBackward(200);
  }
}