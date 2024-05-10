#pragma once

#include <Arduino.h>

struct MotorDrive
{
    int pinA;
    int pinB;
    int pwmPin;
    int channelNum;
    int frequency;
    // int dutyInt;

    void setup()
    {
        pinMode(pinA, OUTPUT);
        pinMode(pinB, OUTPUT);
        pinMode(pwmPin, OUTPUT);
        ledcSetup(channelNum, frequency, 8);
        ledcAttachPin(pwmPin, channelNum);
    }

    void driveForward(int duty)
    {
        digitalWrite(pinA, HIGH);
        digitalWrite(pinB, LOW);
        ledcWrite(channelNum, duty);
    }
};