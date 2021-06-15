#include <stdint.h>
#include <gb/gb.h>
#include "keypad.h"
#include "bkg_mine.h"
#include "sprite_mine.h"

#define CURSOR_REPEAT_BEGIN (15)
#define CURSOR_REPEAT_INTERVAL (5)

//static struct Minesweeper mine;

static int8_t cursor_x;
static int8_t cursor_y;

void init()
{
    cursor_x = 0;
    cursor_y = 0;

    keypad_init();

    bkg_mine_setup();
    sprite_mine_setup();
}

void update_game()
{
    if (keypad_repeat(KEYPAD_KEY_UP, CURSOR_REPEAT_BEGIN, CURSOR_REPEAT_INTERVAL)) {
        cursor_y -= 8;
    } else if (keypad_repeat(KEYPAD_KEY_DOWN, CURSOR_REPEAT_BEGIN, CURSOR_REPEAT_INTERVAL)) {
        cursor_y += 8;
    } else if (keypad_repeat(KEYPAD_KEY_LEFT, CURSOR_REPEAT_BEGIN, CURSOR_REPEAT_INTERVAL)) {
        cursor_x -= 8;
    } else if (keypad_repeat(KEYPAD_KEY_RIGHT, CURSOR_REPEAT_BEGIN, CURSOR_REPEAT_INTERVAL)) {
        cursor_x += 8;
    }

    sprite_mine_update();
    sprite_mine_cursor(cursor_x, cursor_y);
}

void main()
{
    init();

    while (1) {
        keypad_update();

        update_game();

        wait_vbl_done();
    }
}
