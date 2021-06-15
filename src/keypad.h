#pragma once

#include <stdint.h>
#include <gb/gb.h>

enum KeypadKey {
    KeypadUp = J_UP,
    KeypadDown = J_DOWN,
    KeypadLeft = J_LEFT,
    KeypadRight = J_RIGHT,
    KeypadA = J_A,
    KeypadB = J_B,
    KeypadStart = J_START,
    KeypadSelect = J_SELECT,
};

void keypad_init();
void keypad_update();
int8_t keypad_trigger(enum KeypadKey key);
int8_t keypad_down(enum KeypadKey key);
int8_t keypad_repeat(enum KeypadKey key, uint8_t begin, uint8_t interval);
