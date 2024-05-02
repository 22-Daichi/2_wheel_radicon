#pragma once

#include <Arduino.h>

#include "PulseCounter.hpp"

template<uint8_t PIN_A, uint8_t PIN_B, pcnt_channel_t CHANNEL_A, pcnt_channel_t CHANNEL_B, pcnt_unit_t UNIT>
class Encoder {
private:
    PulseCounter<PIN_A, PIN_B, CHANNEL_A, UNIT, true> counterA;
    PulseCounter<PIN_B, PIN_A, CHANNEL_B, UNIT, false> counterB;

public:
    void setup() {
        counterA.config();
        counterB.config();
        pause();
        clear();
    }

    void pause() {
        pcnt_counter_pause(UNIT);
    }

    void clear() {
        pcnt_counter_clear(UNIT);
    }

    void resume() {
        pcnt_counter_resume(UNIT);
    }

    int16_t getCount() {
        return counterA.getCount();
    }
};