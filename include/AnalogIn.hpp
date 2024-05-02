#pragma once

#include <Arduino.h>

struct AnalogIn {
    uint8_t pinId;

    void setup() {
        pinMode(pinId, INPUT);
    }
    uint16_t getValue() {
        return analogRead(pinId);
    }
};
