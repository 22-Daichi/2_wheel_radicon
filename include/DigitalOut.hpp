#pragma once

#include <Arduino.h>

struct DigitalOut {
    uint8_t pinId;
    uint8_t state;

    void setup() {
        pinMode(pinId, OUTPUT);
        setLow();
    }
    void setHigh() {
        state = 1;
        digitalWrite(pinId, state);
    }
    void setLow() {
        state = 0;
        digitalWrite(pinId, state);
    }
    void toggle() {
        state ^= 1;
        digitalWrite(pinId, state);
    }
};
