#pragma once

#include <stdint.h>
#include <gb/gb.h>

#define KEYPAD_KEY_UP (J_UP)
#define KEYPAD_KEY_DOWN (J_DOWN)
#define KEYPAD_KEY_LEFT (J_LEFT)
#define KEYPAD_KEY_RIGHT (J_RIGHT)
#define KEYPAD_KEY_A (J_A)
#define KEYPAD_KEY_B (J_B)
#define KEYPAD_KEY_SELECT (J_SELECT)
#define KEYPAD_KEY_START (J_START)

void keypad_init();
void keypad_update();
int8_t keypad_trigger(uint8_t key);
int8_t keypad_down(uint8_t key);
int8_t keypad_repeat(uint8_t key, uint8_t begin, uint8_t interval);
