#include <gb/gb.h>
#include "scene_game.h"
#include "keypad.h"
#include "../assets/bkg_tile_mine.h"
#include "../assets/bkg_map_mine.h"
#include "../assets/sprite_tile_cursor.h"

#define MAP_MINE_WIDTH (20)
#define MAP_MINE_HEIGHT (18)

#define TILE_0 (0)
#define TILE_1 (1)
#define TILE_2 (2)
#define TILE_3 (3)
#define TILE_4 (4)
#define TILE_5 (5)
#define TILE_6 (6)
#define TILE_7 (7)
#define TILE_8 (8)
#define TILE_9 (9)
#define TILE_BLOCK (10)
#define TILE_BOMB (11)
#define TILE_HIT_BOMB (12)
#define TILE_CHECK (13)
#define TILE_QUESTION (14)
#define TILE_BLANK (15)
#define TILE_TIMER (16)
#define TILE_BLOCK_BLANK (17)
#define TILE_MARK_GAMEOVER_LU (24)
#define TILE_MARK_GAMEOVER_RU (27)
#define TILE_MARK_GAMEOVER_LD (25)
#define TILE_MARK_GAMEOVER_RD (26)

#define BOMB_COUNT_X (3)
#define BOMB_COUNT_Y (0)
#define BOMB_COUNT_W (2)
#define BOMB_COUNT_H (1)

#define TIMER_X (16)
#define TIMER_Y (0)
#define TIMER_W (3)
#define TIMER_H (1)

#define MARK_X (9)
#define MARK_Y (0)
#define MARK_W (2)
#define MARK_H (2)

#define CURSOR_REPEAT_BEGIN (15)
#define CURSOR_REPEAT_INTERVAL (5)

#define SPRITE_CURSOR (1)

static int8_t cursor_x;
static int8_t cursor_y;
static int8_t cursor_anim_count;
static int8_t cursor_anim_tile;

void scene_game_init()
{
    set_bkg_data(0, 30, bkg_tile_mine);
    set_bkg_tiles(0, 0, MAP_MINE_WIDTH, MAP_MINE_HEIGHT, bkg_map_mine);

    set_sprite_data(0, 5, sprite_tile_cursor);

    cursor_x = 0;
    cursor_y = 0;
    cursor_anim_count = 0;
    cursor_anim_tile = 0;

    SHOW_BKG;
    SHOW_SPRITES;
}

void scene_game_update()
{
    if (keypad_repeat(KeypadUp, CURSOR_REPEAT_BEGIN, CURSOR_REPEAT_INTERVAL)) {
        cursor_y -= 8;
    } else if (keypad_repeat(KeypadDown, CURSOR_REPEAT_BEGIN, CURSOR_REPEAT_INTERVAL)) {
        cursor_y += 8;
    } else if (keypad_repeat(KeypadLeft, CURSOR_REPEAT_BEGIN, CURSOR_REPEAT_INTERVAL)) {
        cursor_x -= 8;
    } else if (keypad_repeat(KeypadRight, CURSOR_REPEAT_BEGIN, CURSOR_REPEAT_INTERVAL)) {
        cursor_x += 8;
    }

    cursor_anim_count++;
    if (cursor_anim_count > 15) {
        cursor_anim_count = 0;
        cursor_anim_tile++;
        if (cursor_anim_tile > 4) {
            cursor_anim_tile = 0;
        }

        set_sprite_tile(SPRITE_CURSOR, cursor_anim_tile);
    }
    move_sprite(SPRITE_CURSOR, cursor_x + 8, cursor_y + 16);
}

