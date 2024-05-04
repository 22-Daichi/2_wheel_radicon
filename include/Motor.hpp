#pragma once

#include <Arduino.h>

#include "DigitalOut.hpp"
#include "PwmOut.hpp"

struct Motor {
    DigitalOut pinForwardRotation;
    DigitalOut pinReverseRotation;
    PwmOut pinPower;
    float currentPower;

    void setup() {
        pinForwardRotation.setup();
        pinReverseRotation.setup();
        pinPower.setup();
        setPower(0);
    }
    void setPower(float power) {
        currentPower = power;
        if (power > 0) {
            pinForwardRotation.setHigh();
            pinReverseRotation.setLow();
        } else if (power < 0) {
            pinForwardRotation.setLow();
            pinReverseRotation.setHigh();
        } else {
            pinForwardRotation.setHigh();
            pinReverseRotation.setHigh();
        }
        pinPower.setDuty(abs(power));
    }
    void stop() {
        currentPower = 0;
        pinForwardRotation.setLow();
        pinReverseRotation.setLow();
        pinPower.setToZero();
    }
};
