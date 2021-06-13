#include <stdint.h>
#include <gb/gb.h>
#include "keypad.h"
#include "bkg_mine.h"
#include "sprite_mine.h"

static struct KeyPad keypad;
//static struct Minesweeper mine;

static int8_t cursor_x;
static int8_t cursor_y;

void init()
{
    cursor_x = 0;
    cursor_y = 0;

    keypad_init(&keypad);

    bkg_mine_setup();
    sprite_mine_setup();
}

void update_game()
{
    if (keypad_trigger(&keypad, KEYPAD_KEY_UP)) {
        cursor_y -= 8;
    } else if (keypad_trigger(&keypad, KEYPAD_KEY_DOWN)) {
        cursor_y += 8;
    } else if (keypad_trigger(&keypad, KEYPAD_KEY_LEFT)) {
        cursor_x -= 8;
    } else if (keypad_trigger(&keypad, KEYPAD_KEY_RIGHT)) {
        cursor_x += 8;
    }

    sprite_mine_update();
    sprite_mine_cursor(cursor_x, cursor_y);
}

void main()
{
    init();

    while (1) {
        keypad_update(&keypad);

        update_game();

        wait_vbl_done();
    }
}
