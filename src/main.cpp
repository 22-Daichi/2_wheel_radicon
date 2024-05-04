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

int16_t count1 = 0;
int16_t count2 = 0;
int16_t difference = count1 + count2;

int16_t n = 0; // tuika

const int STBY = 12;

// A RIGHT B LEFT
// IN 1 LEFT IN 2 RIGHT

/*void IRAM_ATTR get_count(){
 //Dabble.processInput();
 pcnt_get_counter_value(PCNT_UNIT_0, &count1);
 pcnt_get_counter_value(PCNT_UNIT_1, &count2);
 //difference = count1 + count2;
 ledcWrite( pwmch_2 , 210+(45*difference/10)/((1+(difference/10)^2)^(1/2)));

}*/
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

    if (GamePad.isUpPressed()) {
        encoderA.clear();
        encoderB.clear();
        count1 = encoderA.getCount();
        count2 = encoderB.getCount();
        // difference = count1 + count2;
        // Serial.println("motorA forward");
        motorA.setPower(0.8);
        // Serial.println("motorB forward");
        // ledcWrite( pwmch_2 , 210+(45*difference/10)/((1+(difference/10)^2)^(1/2)));
        motorB.setPower(0.8);
        // timerAlarmEnable(timer);
        n = 1;
    }

    if (n == 1) {
        count1 = encoderA.getCount();
        count2 = encoderB.getCount();
        difference = count1 + count2;
        ledcWrite(motorB.pinPower.channel, 210 + (45 * difference / 10) / ((1 + (difference / 10) ^ 2) ^ (1 / 2)));
        delay(100);
    }
    if (GamePad.isDownPressed()) {
        // timerAlarmDisable(timer);2
        n = 0;
        // Serial.println("motorA back");
        motorA.setPower(-0.8);
        // Serial.println("motorB back");
        motorB.setPower(-0.8);
    }
    if (GamePad.isCrossPressed()) {
        n = 0;
        // timerAlarmDisable(timer);3
        // Serial.println("motorA stop");
        motorA.stop();
        // Serial.println("motorB stop");
        motorB.stop();
    }
    if (GamePad.isCirclePressed()) {
        // timerAlarmDisable(timer);4
        n = 0;
        // Serial.println("motorA back");
        motorA.setPower(-0.8);
        // Serial.println("motorB forward");
        motorB.setPower(0.8);
    }

    if (GamePad.isSquarePressed()) {
        // timerAlarmDisable(timer);5
        n = 0;
        // Serial.println("motorA forward");
        motorA.setPower(0.8);
        // rial.println("motorB back");
        motorB.setPower(-0.8);
    }
    if (GamePad.isRightPressed()) {
        // timerAlarmDisable(timer);6
        n = 0;
        // Serial.println("motorA slow");
        motorA.setPower(0.8);
        // Serial.println("motorB forward");
        motorB.setPower(1.0);
    }
    if (GamePad.isLeftPressed()) {
        // timerAlarmDisable(timer);7
        n = 0;
        // Serial.println("motorA forward");
        motorA.setPower(1.0);
        // Serial.println("motorB slow");
        motorB.setPower(0.8);
    }
    if (GamePad.isStartPressed()) {
        encoderA.clear();
        encoderB.clear();
    }
}