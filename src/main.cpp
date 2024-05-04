#include <Arduino.h>

#include "DabbleESP32.h"
#include "driver/pcnt.h"

#include "Encoder.hpp"
#include "Motor.hpp"

// motor A
DigitalOut motorFwdA = {27, 0};
DigitalOut motorRevA = {26, 0};
PwmOut motorPowA = {25, 0, 12800, 0};
Motor motorA = {motorFwdA, motorRevA, motorPowA, 0};

// motor B
DigitalOut motorFwdB = {32, 0};
DigitalOut motorRevB = {33, 0};
PwmOut motorPowB = {13, 1, 12800, 0};
Motor motorB = {motorFwdB, motorRevB, motorPowB, 0};

Encoder encoderA = {21, 4, PCNT_CHANNEL_0, PCNT_CHANNEL_1, PCNT_UNIT_0};
Encoder encoderB = {34, 23, PCNT_CHANNEL_0, PCNT_CHANNEL_1, PCNT_UNIT_1};

// hw_timer_t* timer = NULL;

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

int16_t n = 0; // tuika

const int STBY = 12;

void setup() {
    // put your setup code here, to run once:
    motorA.setup();
    motorB.setup();

    pinMode(STBY, OUTPUT);
    digitalWrite(STBY, HIGH);

    encoderA.setup();
    encoderA.resume();

    encoderB.setup();
    encoderB.resume();

    // timer = timerBegin(0, 8000, true);
    // timerAttachInterrupt(timer, &get_count, true);
    // timerAlarmWrite(timer, 10000, true);
    // timerAlarmDisable(timer);

    Dabble.begin("Bluth");
    Serial.begin(9600);
    Serial.println("Motor Standby");
}

void loop() {
    // put your main code here, to run repeatedly:
    Dabble.processInput(); // this function is used to refresh data obtained from smartphone.Hence calling this function
                           // is mandatory in order to get data properly from your mobile.

    uint8_t gamePadState = GamePad.isUpPressed()         ? 1U
                           : GamePad.isDownPressed()     ? 2U
                           : GamePad.isLeftPressed()     ? 3U
                           : GamePad.isRightPressed()    ? 4U
                           : GamePad.isStartPressed()    ? 5U
                           : GamePad.isSelectPressed()   ? 6U
                           : GamePad.isTrianglePressed() ? 7U
                           : GamePad.isCirclePressed()   ? 8U
                           : GamePad.isCrossPressed()    ? 9U
                           : GamePad.isSquarePressed()   ? 10U
                                                         : 0U;

    switch (gamePadState) {
        case 0: // no button is pressed
            break;

        case 1: { // UP is pressed
            Serial.println("motorA forward");
            Serial.println("motorB forward");
            encoderA.clear();
            encoderB.clear();
            const auto difference = encoderA.getCount() + encoderB.getCount();
            const auto dutyB = 0.8F + 0.01765F * difference / sqrtf(1 + sq(difference / 10.0F));
            motorA.setPower(0.8);
            motorB.setPower(dutyB);
        } break;

        case 2: // DOWN is pressed
            Serial.println("motorA back");
            Serial.println("motorB back");
            motorA.setPower(-0.8);
            motorB.setPower(-0.8);
            break;

        case 3: // LEFT is pressed
            Serial.println("motorA forward");
            Serial.println("motorB slow");
            motorA.setPower(1.0);
            motorB.setPower(0.8);
            break;

        case 4: // RIGHT is pressed
            Serial.println("motorA slow");
            Serial.println("motorB forward");
            motorA.setPower(0.8);
            motorB.setPower(1.0);
            break;

        case 5: // START is pressed
            Serial.println("clear encoder counts");
            encoderA.clear();
            encoderB.clear();
            break;

        case 8: // CIRCLE is pressed
            Serial.println("motorA back");
            Serial.println("motorB forward");
            motorA.setPower(-0.8);
            motorB.setPower(0.8);
            break;

        case 9: // CROSS is pressed
            Serial.println("motorA stop");
            Serial.println("motorB stop");
            motorA.stop();
            motorB.stop();
            break;

        case 10: // SQUARE is pressed
            Serial.println("motorA forward");
            Serial.println("motorB back");
            motorA.setPower(0.8);
            motorB.setPower(-0.8);
            break;

        default:
            break;
    }
}