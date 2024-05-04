#pragma once

#include <Arduino.h>

#include "driver/pcnt.h"

class PulseCounter {
private:
    const uint8_t pulseInputPin;
    const uint8_t pulseCtrlPin;
    const pcnt_channel_t pulseCounterChannel;
    const pcnt_unit_t pulseCounterUnit;
    const bool incrementOnPositiveEdge;

public:
    PulseCounter(uint8_t pulseInputPin,
                 uint8_t pulseCtrlPin,
                 pcnt_channel_t pulseCounterChannel,
                 pcnt_unit_t pulseCounterUnit,
                 bool incrementOnPositiveEdge)
      : pulseInputPin{pulseInputPin}
      , pulseCtrlPin{pulseCtrlPin}
      , pulseCounterChannel{pulseCounterChannel}
      , pulseCounterUnit{pulseCounterUnit}
      , incrementOnPositiveEdge{incrementOnPositiveEdge} {}

    inline void setup() const {
        config();
        pause();
        clear();
    }
    inline void config() const {
        pcnt_config_t config;
        config.pulse_gpio_num = pulseInputPin;
        config.ctrl_gpio_num = pulseCtrlPin;
        if (incrementOnPositiveEdge) {
            config.lctrl_mode = PCNT_MODE_KEEP;
            config.hctrl_mode = PCNT_MODE_REVERSE;
        } else {
            config.lctrl_mode = PCNT_MODE_REVERSE;
            config.hctrl_mode = PCNT_MODE_KEEP;
        }
        config.channel = pulseCounterChannel;
        config.unit = pulseCounterUnit;
        config.pos_mode = PCNT_COUNT_INC;
        config.neg_mode = PCNT_COUNT_DEC;
        pcnt_unit_config(&config);
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
        return pulseCounterUnit;
    }
    inline int16_t getCount() const {
        int16_t count;
        pcnt_get_counter_value(getUnit(), &count);
        return count;
    }
};
