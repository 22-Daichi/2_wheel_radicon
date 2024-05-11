#pragma once

#include <Arduino.h>

struct MotorDrive
{
    int pin1;
    int pin2;
    int pwmPin;
    int channelNum;
    int frequency;
    // int dutyInt;

    void setup()
    {
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
        pinMode(pwmPin, OUTPUT);
        ledcSetup(channelNum, frequency, 8);
        ledcAttachPin(pwmPin, channelNum);
    }

    void neutral()
    {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        ledcWrite(channelNum, 0);
    }

    void driveForward(int duty)
    {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        ledcWrite(channelNum, duty);
    }

    void driveBackward(int duty)
    {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        ledcWrite(channelNum, duty);
    }

    void stop()
    {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, HIGH);
        ledcWrite(channelNum, 0);
    }
};