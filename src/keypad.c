#include "keypad.h"

void keypad_init(struct KeyPad* keypad)
{
    keypad->key = 0;
    keypad->prev_key = 0;
    keypad->repeat_begin = 0;
    keypad->repeat_interval = 0;
    keypad->repeat_begin_count = 0;
    keypad->repeat_interval_count = 0;
}

void keypad_set_repeat(struct KeyPad* keypad, uint8_t repeat_begin, uint8_t repeat_interval)
{
    keypad->repeat_begin = repeat_begin;
    keypad->repeat_interval = repeat_interval;
}

void keypad_update(struct KeyPad* keypad)
{
    keypad->prev_key = keypad->key;
    keypad->key = joypad();
}

int keypad_trigger(const struct KeyPad* keypad, uint8_t key)
{
    return keypad->key & key && !(keypad->prev_key & key);
}

int keypad_down(const struct KeyPad* keypad, uint8_t key)
{
    return keypad->key & key;
}
