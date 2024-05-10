#pragma once

#include <DabbleESP32.h>

namespace game_pad {

enum class Button {
    None,
    Up,
    Down,
    Left,
    Right,
    Start,
    Select,
    Triangle,
    Circle,
    Cross,
    Square,
};

auto pressedButton() -> Button {
    if (GamePad.isUpPressed()) {
        return Button::Up;
    } else if (GamePad.isDownPressed()) {
        return Button::Down;
    } else if (GamePad.isLeftPressed()) {
        return Button::Left;
    } else if (GamePad.isRightPressed()) {
        return Button::Right;
    } else if (GamePad.isStartPressed()) {
        return Button::Start;
    } else if (GamePad.isSelectPressed()) {
        return Button::Select;
    } else if (GamePad.isTrianglePressed()) {
        return Button::Triangle;
    } else if (GamePad.isCirclePressed()) {
        return Button::Circle;
    } else {
        return Button::None;
    }
}

}
