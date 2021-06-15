#include "keypad.h"

static uint8_t current_key;
static uint8_t prev_key;
static uint8_t repeat_count;

void keypad_init()
{
    current_key = 0;
    prev_key = 0;
    repeat_count = 0;
}

void keypad_update()
{
    prev_key = current_key;
    current_key = joypad();
}

int8_t keypad_trigger(enum KeypadKey key)
{
    return current_key & key && !(prev_key & key);
}

int8_t keypad_down(enum KeypadKey key)
{
    return current_key & key;
}

int8_t keypad_repeat(enum KeypadKey key, uint8_t begin, uint8_t interval)
{
    if ((current_key & key) == 0) {
        return 0;
    }

    if (current_key != prev_key) {
        repeat_count = 0;
        return 1;
    }

    repeat_count++;

    if (repeat_count > begin + interval) {
        repeat_count = begin + 1;
        return 1;
    }

    if (repeat_count == begin) {
        return 1;
    }

    return 0;
}
