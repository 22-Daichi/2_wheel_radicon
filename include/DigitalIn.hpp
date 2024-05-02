#pragma once

#include <Arduino.h>

struct DigitalIn {
    uint8_t pinId;

    void setup() {
        pinMode(pinId, INPUT_PULLDOWN);
    }
    uint8_t getValue() {
        return digitalRead(pinId);
    }
};
