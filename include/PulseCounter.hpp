#pragma once

#include <Arduino.h>

#include "driver/pcnt.h"

struct PulseCounter {
    uint8_t pulseInputPin;
    uint8_t pulseControlPin;
    pcnt_channel_t pulseCounterChannel;
    pcnt_unit_t pulseCounterUnit;
    uint8_t pulseCountLowerLimit;
    uint8_t pulseCountUpperLimit;
    bool incrementOnPositiveEdge;

    void setup() {
        config();
        pause();
        clear();
    }
    void config() {
        pcnt_config_t config;
        config.pulse_gpio_num = pulseInputPin;
        config.ctrl_gpio_num = pulseControlPin;
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
        config.counter_l_lim = pulseCountLowerLimit;
        config.counter_h_lim = pulseCountUpperLimit;
        pcnt_unit_config(&config);
    }
    void pause() {
        pcnt_counter_pause(pulseCounterUnit);
    }
    void clear() {
        pcnt_counter_clear(pulseCounterUnit);
    }
    void resume() {
        pcnt_counter_resume(pulseCounterUnit);
    }
};
