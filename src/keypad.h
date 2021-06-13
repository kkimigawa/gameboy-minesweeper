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

struct KeyPad {
    uint8_t key;
    uint8_t prev_key;
    uint8_t repeat_begin;
    uint8_t repeat_interval;
    uint8_t repeat_begin_count;
    uint8_t repeat_interval_count;
};

void keypad_init(struct KeyPad* keypad);
void keypad_set_repeat(struct KeyPad* keypad, uint8_t repeat_begin, uint8_t repeat_interval);
void keypad_update(struct KeyPad* keypad);
int keypad_trigger(const struct KeyPad* keypad, uint8_t key);
int keypad_down(const struct KeyPad* keypad, uint8_t key);
