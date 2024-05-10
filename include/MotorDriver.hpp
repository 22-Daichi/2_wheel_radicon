#pragma once

#include <Arduino.h>
#include <MotorDriver.hpp>

struct MotorDrive
{
    int pinA;
    int pinB;
    int pwmPin;
    int pwmChannel;

    void setup()
    {
        pinMode(pinA, OUTPUT);
        pinMode(pinB, OUTPUT);
        pinMode(pwmPin, OUTPUT);
    }
};