#include "keypad.h"

static uint8_t _current_key;
static uint8_t _prev_key;
static uint8_t _repeat_count;

void keypad_init()
{
    _current_key = 0;
    _prev_key = 0;
    _repeat_count = 0;
}

void keypad_update()
{
    _prev_key = _current_key;
    _current_key = joypad();
}

int8_t keypad_trigger(enum KeypadKey key)
{
    return _current_key & key && !(_prev_key & key);
}

int8_t keypad_down(enum KeypadKey key)
{
    return _current_key & key;
}

int8_t keypad_repeat(enum KeypadKey key, uint8_t begin, uint8_t interval)
{
    if ((_current_key & key) == 0) {
        return 0;
    }

    if ((_prev_key & key) == 0 && _current_key != _prev_key) {
        _repeat_count = 0;
        return 1;
    }

    _repeat_count++;

    if (_repeat_count > begin + interval) {
        _repeat_count = begin + 1;
        return 1;
    }

    if (_repeat_count == begin) {
        return 1;
    }

    return 0;
}
