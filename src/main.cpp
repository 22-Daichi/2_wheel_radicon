#include <Arduino.h>

#include "DabbleESP32.h"
#include "driver/pcnt.h"

#include "Encoder.hpp"

Encoder encoderA = {21, 4, PCNT_CHANNEL_0, PCNT_CHANNEL_1, PCNT_UNIT_0};
Encoder encoderB = {34, 23, PCNT_CHANNEL_0, PCNT_CHANNEL_1, PCNT_UNIT_1};

// hw_timer_t* timer = NULL;

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#define motorAp 25
#define motorBp 13
#define pwmch_1 0
#define pwmch_2 1

int16_t count1 = 0;
int16_t count2 = 0;
int16_t difference = count1 + count2;

int16_t n = 0; // tuika

const int motorA1 = 27;
const int motorA2 = 26;

const int STBY = 12;

const int motorB1 = 32; // IN1
const int motorB2 = 33; // IN2

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
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorAp, OUTPUT);

    pinMode(STBY, OUTPUT);

    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    pinMode(motorBp, OUTPUT);

    ledcSetup(pwmch_1, 12800, 8);
    ledcSetup(pwmch_2, 12800, 8);

    ledcAttachPin(motorAp, pwmch_1);
    ledcAttachPin(motorBp, pwmch_2);

    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    // ledcWrite( pwmch_1 , 0 );

    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
    // ledcWrite( pwmch_2 , 0 );

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
        ledcWrite(pwmch_1, 200);
        digitalWrite(motorA1, HIGH);
        digitalWrite(motorA2, LOW);
        // Serial.println("motorB forward");
        // ledcWrite( pwmch_2 , 210+(45*difference/10)/((1+(difference/10)^2)^(1/2)));
        ledcWrite(pwmch_2, 200);
        digitalWrite(motorB1, HIGH);
        digitalWrite(motorB2, LOW);
        // timerAlarmEnable(timer);
        n = 1;
    }

    if (n == 1) {
        count1 = encoderA.getCount();
        count2 = encoderB.getCount();
        difference = count1 + count2;
        ledcWrite(pwmch_2, 210 + (45 * difference / 10) / ((1 + (difference / 10) ^ 2) ^ (1 / 2)));
        delay(100);
    }
    if (GamePad.isDownPressed()) {
        // timerAlarmDisable(timer);2
        n = 0;
        // Serial.println("motorA back");
        ledcWrite(pwmch_1, 200);
        digitalWrite(motorA1, LOW);
        digitalWrite(motorA2, HIGH);
        // Serial.println("motorB back");
        ledcWrite(pwmch_2, 200);
        digitalWrite(motorB1, LOW);
        digitalWrite(motorB2, HIGH);
    }
    if (GamePad.isCrossPressed()) {
        n = 0;
        // timerAlarmDisable(timer);3
        // Serial.println("motorA stop");
        digitalWrite(motorA1, LOW);
        digitalWrite(motorA2, LOW);
        ledcWrite(pwmch_1, 0);
        // Serial.println("motorB stop");
        digitalWrite(motorB1, LOW);
        digitalWrite(motorB2, LOW);
        ledcWrite(pwmch_2, 0);
    }
    if (GamePad.isCirclePressed()) {
        // timerAlarmDisable(timer);4
        n = 0;
        // Serial.println("motorA back");
        ledcWrite(pwmch_1, 200);
        digitalWrite(motorA1, LOW);
        digitalWrite(motorA2, HIGH);
        // Serial.println("motorB forward");
        ledcWrite(pwmch_2, 200);
        digitalWrite(motorB1, HIGH);
        digitalWrite(motorB2, LOW);
    }

    if (GamePad.isSquarePressed()) {
        // timerAlarmDisable(timer);5
        n = 0;
        // Serial.println("motorA forward");
        ledcWrite(pwmch_1, 200);
        digitalWrite(motorA1, HIGH);
        digitalWrite(motorA2, LOW);
        // rial.println("motorB back");
        ledcWrite(pwmch_2, 200);
        digitalWrite(motorB1, LOW);
        digitalWrite(motorB2, HIGH);
    }
    if (GamePad.isRightPressed()) {
        // timerAlarmDisable(timer);6
        n = 0;
        // Serial.println("motorA slow");
        ledcWrite(pwmch_1, 200);
        digitalWrite(motorA1, HIGH);
        digitalWrite(motorA2, LOW);
        // Serial.println("motorB forward");
        ledcWrite(pwmch_2, 256);
        digitalWrite(motorB1, HIGH);
        digitalWrite(motorB2, LOW);
    }
    if (GamePad.isLeftPressed()) {
        // timerAlarmDisable(timer);7
        n = 0;
        // Serial.println("motorA forward");
        ledcWrite(pwmch_1, 256);
        digitalWrite(motorA1, HIGH);
        digitalWrite(motorA2, LOW);
        // Serial.println("motorB slow");
        ledcWrite(pwmch_2, 200);
        digitalWrite(motorB1, HIGH);
        digitalWrite(motorB2, LOW);
    }
    if (GamePad.isStartPressed()) {
        encoderA.clear();
        encoderB.clear();
    }
}