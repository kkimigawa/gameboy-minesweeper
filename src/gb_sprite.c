#include <gb/gb.h>
#include "gb_sprite.h"

void set_sprite_tile16(uint8_t nb, uint8_t tile)
{
    SPRITES_8x16;

    set_sprite_tile(nb, tile);
    set_sprite_tile(nb + 1, tile + 2);
}

void move_sprite16(uint8_t nb, uint8_t x, uint8_t y)
{
    move_sprite(nb, x, y);
    move_sprite(nb + 1, x + 8, y);
}

