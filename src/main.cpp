#include <Arduino.h>
#include <MotorDriver.hpp>

#include "GamePad.hpp"

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

void setup() {
    motorRight.setup();
    motorLeft.setup();
    pinMode(STBY, OUTPUT);
    digitalWrite(STBY, HIGH);
    motorRight.neutral();
    motorLeft.neutral();
    ble::beginConnection("Bluth");
    Serial.begin(9600);
    Serial.println("Motor Standby");
}

void loop() {
    using ble::gamePad::Button;
    Button button = ble::gamePad::pressedButton();

    if (button == Button::Up) {
        motorRight.driveForward(200);
        motorLeft.driveForward(200);
    }
    else if (button == Button::Down) {
        motorRight.driveBackward(200);
        motorLeft.driveBackward(200);
    }
    else if (button == Button::Left) {
        motorRight.driveBackward(200);
    }
    else if (button == Button::Right) {
        motorRight.driveForward(200);
    }
    else if (button == Button::Circle) {
        motorRight.driveBackward(200);
        motorLeft.driveBackward(200);
    }
    else if (button == Button::Cross) {
        motorRight.stop();
        motorLeft.stop();
    }
    else if (button == Button::Square) {
        motorRight.driveForward(200);
        motorLeft.driveBackward(200);
    }
}