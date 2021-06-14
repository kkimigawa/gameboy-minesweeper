#include <gb/gb.h>
#include "sprite_mine.h"
#include "../assets/sprite_tile_cursor.h"

#define SPRITE_CURSOR (1)

static int8_t cursor_anim_count;
static int8_t cursor_anim_tile;

void sprite_mine_setup()
{
    set_sprite_data(0, 5, sprite_tile_cursor);
    set_sprite_tile(SPRITE_CURSOR, 0);

    move_sprite(SPRITE_CURSOR, 8, 16);

    cursor_anim_count = 0;
    cursor_anim_tile = 0;

    SHOW_SPRITES;
}

void sprite_mine_update()
{
    cursor_anim_count++;
    if (cursor_anim_count > 15) {
        cursor_anim_count = 0;
        cursor_anim_tile++;
        if (cursor_anim_tile > 4) {
            cursor_anim_tile = 0;
        }

        set_sprite_tile(SPRITE_CURSOR, cursor_anim_tile);
    }
}

void sprite_mine_cursor(int8_t x, int8_t y)
{
    move_sprite(SPRITE_CURSOR, x + 8, y + 16);
}
