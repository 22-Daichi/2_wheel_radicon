#include <Arduino.h>

#include "GamePad.hpp"
#include "MotorDriver.hpp"

const int motorR1 = 27; // AIN1
const int motorR2 = 26; // AIN2

const int motorL1 = 32; // BIN1
const int motorL2 = 33; // BIN2

const int motorRp = 25;        // PWMA
const int motorLp = 13;        // PWmB
const int pwmChannelRight = 0; // 右のモーター用のpwmチャンネル
const int pwmChannelLeft = 1;  // 左のモーター用のpwmチャンネル

const int STBY = 12;            // このままにしておいてください
const int pwmFrequency = 12800; // pwmの周波数

void setup() {
    pinMode(STBY, OUTPUT);
    digitalWrite(STBY, HIGH);      // モータードライバのための設定
    ble::beginConnection("Bluth"); // スマホと接続のためのおまじない
    // その他必要な処理を書く
}

void loop() {
    using ble::gamePad::Button;
    Button button = ble::gamePad::pressedButton(); // おまじない

    if (button == Button::Up) {
        // 十字キーの上ボタンが押された時の処理
    }
    else if (button == Button::Down) {
        // 十字キーの下ボタンが押された時の処理
    }
    else if (button == Button::Left) {
        // 十字キーの左ボタンが押された時の処理
    }
    else if (button == Button::Right) {
        // 十字キーの右ボタンが押された時の処理
    }
    else if (button == Button::Circle) {
        // 〇ボタンが押された時の処理
    }
    else if (button == Button::Cross) {
        // ×ボタンが押された時の処理
    }
    else if (button == Button::Square) {
        // □ボタンが押された時の処理
    }
}