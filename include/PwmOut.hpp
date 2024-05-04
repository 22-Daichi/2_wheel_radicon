#pragma once

#include <Arduino.h>

struct PwmOut {
    uint8_t pinId;
    uint8_t channel;
    uint16_t periodUs;
    uint8_t dutyInt;

    void setup() {
        pinMode(pinId, OUTPUT);
        ledcSetup(channel, periodUs, 8);
        ledcAttachPin(pinId, channel);
        setToZero();
    }
    float getDuty() {
        return dutyInt / 255.0;
    }
    void setDuty(float duty) {
        dutyInt = duty * 255;
        ledcWrite(channel, dutyInt);
    }
    void setToZero() {
        dutyInt = 0;
        ledcWrite(channel, dutyInt);
    }
};
