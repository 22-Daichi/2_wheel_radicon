#pragma once

#include <Arduino.h>

#include "driver/pcnt.h"

template<uint8_t PULSE_INPUT_PIN,
         uint8_t PULSE_CTRL_PIN,
         pcnt_channel_t PULSE_COUNTER_CHANNEL,
         pcnt_unit_t PULSE_COUNTER_UNIT,
         bool INCREMENT_ON_POSITIVE_EDGE>
class PulseCounter {
public:
    void setup() {
        config();
        pause();
        clear();
    }
    void config() {
        pcnt_config_t config;
        config.pulse_gpio_num = PULSE_INPUT_PIN;
        config.ctrl_gpio_num = PULSE_CTRL_PIN;
        if (INCREMENT_ON_POSITIVE_EDGE) {
            config.lctrl_mode = PCNT_MODE_KEEP;
            config.hctrl_mode = PCNT_MODE_REVERSE;
        } else {
            config.lctrl_mode = PCNT_MODE_REVERSE;
            config.hctrl_mode = PCNT_MODE_KEEP;
        }
        config.channel = PULSE_COUNTER_CHANNEL;
        config.unit = PULSE_COUNTER_UNIT;
        config.pos_mode = PCNT_COUNT_INC;
        config.neg_mode = PCNT_COUNT_DEC;
        pcnt_unit_config(&config);
    }
    void pause() {
        pcnt_counter_pause(PULSE_COUNTER_UNIT);
    }
    void clear() {
        pcnt_counter_clear(PULSE_COUNTER_UNIT);
    }
    void resume() {
        pcnt_counter_resume(PULSE_COUNTER_UNIT);
    }
    int16_t getCount() {
        int16_t count;
        pcnt_get_counter_value(PULSE_COUNTER_UNIT, &count);
        return count;
    }
};
