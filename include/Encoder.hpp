#pragma once

#include <Arduino.h>

#include "PulseCounter.hpp"

class Encoder {
private:
    const PulseCounter pulseCounterA;
    const PulseCounter pulseCounterB;

public:
    Encoder(uint8_t pinA, uint8_t pinB, pcnt_channel_t channelA, pcnt_channel_t channelB, pcnt_unit_t unit)
      : pulseCounterA{pinA, pinB, channelA, unit, false}
      , pulseCounterB{pinB, pinA, channelB, unit, true} {}

    inline void setup() const {
        pulseCounterA.config();
        pulseCounterB.config();
        pause();
        clear();
    }

    inline void pause() const {
        pcnt_counter_pause(getUnit());
    }

    inline void clear() const {
        pcnt_counter_clear(getUnit());
    }

    inline void resume() const {
        pcnt_counter_resume(getUnit());
    }

    inline pcnt_unit_t getUnit() const {
        return pulseCounterA.getUnit();
    }

    inline int16_t getCount() const {
        return pulseCounterA.getCount();
    }
};