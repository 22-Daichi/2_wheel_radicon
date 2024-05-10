#pragma once

#include <Arduino.h>

struct PwmOut
{
    int pinNum;
    int channelNum;
    int frequency;
    int dutyInt;

    void setup()
    {
        pinMode(pinNum, OUTPUT);
        ledcSetup(channelNum, frequency, 8);
        ledcAttachPin(pinNum, channelNum);
        setToZero();
    }
    void setDuty(float duty)
    {
        ledcWrite(channelNum, dutyInt);
    }
    void setToZero()
    {
        dutyInt = 0;
        ledcWrite(channelNum, 0);
    }
};