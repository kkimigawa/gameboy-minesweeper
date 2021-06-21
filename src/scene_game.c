#include <gb/gb.h>
#include "scene_game.h"
#include "keypad.h"
#include "minesweeper.h"
#include "../assets/bkg_tile_mine.h"
#include "../assets/bkg_map_mine.h"
#include "../assets/sprite_tile_cursor.h"

#define MAP_MINE_WIDTH (20)
#define MAP_MINE_HEIGHT (18)
#define MAP_BLOCK_OFFSET_X (0)
#define MAP_BLOCK_OFFSET_Y (2)
#define TILE_SIZE (8)

#define TILE_NUM_0 (6)
#define TILE_NUM_1 (7)
#define TILE_NUM_2 (8)
#define TILE_NUM_3 (9)
#define TILE_NUM_4 (10)
#define TILE_NUM_5 (11)
#define TILE_NUM_6 (12)
#define TILE_NUM_7 (13)
#define TILE_NUM_8 (14)
#define TILE_NUM_9 (15)
#define TILE_TIMER (16)
#define TILE_MARK_GAMEOVER_LU (24)
#define TILE_MARK_GAMEOVER_RU (26)
#define TILE_MARK_GAMEOVER_LD (25)
#define TILE_MARK_GAMEOVER_RD (27)
#define TILE_MARK_CLEAR_LU (28)
#define TILE_MARK_CLEAR_RU (30)
#define TILE_MARK_CLEAR_LD (29)
#define TILE_MARK_CLEAR_RD (31)

#define BOMB_COUNT_X (4)
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
#define CURSOR_SPRITE_INDEX (0)
#define CURSOR_SPRITE_NUM (5)
#define CURSOR_DISP_OFFSET_X (8)
#define CURSOR_DISP_OFFSET_Y (32)
#define CURSOR_ANIM_FRAME (15)

#define SPRITE_CURSOR (1)

#define MINE_WIDTH (20)
#define MINE_HEIGHT (16)
#define MINE_BOMB (30)

static int16_t _cursor_x;
static int16_t _cursor_y;
static int16_t _cursor_disp_x;
static int16_t _cursor_disp_y;
static int8_t _cursor_anim_count;
static int8_t _cursor_anim_tile;

static void bkg_mine_bomb_count(int16_t bomb_count);
static void bkg_mine_timer(uint8_t timer);
static void bkg_mine_clear();
static void bkg_mine_gameover();
static void bkg_blocks();

void scene_game_init()
{
    set_bkg_data(0, 40, bkg_tile_mine);
    set_bkg_tiles(0, 0, MAP_MINE_WIDTH, MAP_MINE_HEIGHT, bkg_map_mine);

    set_sprite_data(CURSOR_SPRITE_INDEX, CURSOR_SPRITE_NUM, sprite_tile_cursor);

    mine_init(MINE_WIDTH, MINE_HEIGHT, MINE_BOMB);
    bkg_blocks();
    bkg_mine_bomb_count(MINE_BOMB);

    _cursor_x = 0;
    _cursor_y = 0;
    _cursor_disp_x = CURSOR_DISP_OFFSET_X;
    _cursor_disp_y = CURSOR_DISP_OFFSET_Y;
    _cursor_anim_count = 0;
    _cursor_anim_tile = 0;

    SHOW_BKG;
    SHOW_SPRITES;
}

void scene_game_update()
{
    if (keypad_repeat(KeypadUp, CURSOR_REPEAT_BEGIN, CURSOR_REPEAT_INTERVAL)) {
        if (_cursor_y > 0) {
            _cursor_y--;
            _cursor_disp_y = CURSOR_DISP_OFFSET_Y + _cursor_y * TILE_SIZE;
        }
    } else if (keypad_repeat(KeypadDown, CURSOR_REPEAT_BEGIN, CURSOR_REPEAT_INTERVAL)) {
        if (_cursor_y < MINE_HEIGHT - 1) {
            _cursor_y++;
            _cursor_disp_y = CURSOR_DISP_OFFSET_Y + _cursor_y * TILE_SIZE;
        }
    } else if (keypad_repeat(KeypadLeft, CURSOR_REPEAT_BEGIN, CURSOR_REPEAT_INTERVAL)) {
        if (_cursor_x > 0) {
            _cursor_x--;
            _cursor_disp_x = CURSOR_DISP_OFFSET_X + _cursor_x * TILE_SIZE;
        }
    } else if (keypad_repeat(KeypadRight, CURSOR_REPEAT_BEGIN, CURSOR_REPEAT_INTERVAL)) {
        if (_cursor_x < MINE_WIDTH - 1) {
            _cursor_x++;
            _cursor_disp_x = CURSOR_DISP_OFFSET_X + _cursor_x * TILE_SIZE;
        }
    } else if (keypad_trigger(KeypadA)) {
        if (mine_open(_cursor_x, _cursor_y)) {
            bkg_blocks();

            int8_t result = mine_get_result();
            if (result == MINE_RESULT_CLEAR) {
                bkg_mine_clear();
            } else if (result == MINE_RESULT_GAMEOVER) {
                bkg_mine_gameover();
            }
        }
    } else if (keypad_trigger(KeypadB)) {
        if (mine_check(_cursor_x, _cursor_y)) {
            bkg_mine_bomb_count(mine_get_check_bomb_count());
            bkg_blocks();
        }
    }

    _cursor_anim_count++;
    if (_cursor_anim_count > CURSOR_ANIM_FRAME) {
        _cursor_anim_count = 0;
        _cursor_anim_tile++;
        if (_cursor_anim_tile >= CURSOR_SPRITE_INDEX + CURSOR_SPRITE_NUM) {
            _cursor_anim_tile = CURSOR_SPRITE_INDEX;
        }

        set_sprite_tile(SPRITE_CURSOR, _cursor_anim_tile);
    }

    move_sprite(SPRITE_CURSOR, _cursor_disp_x, _cursor_disp_y);
}

static void bkg_mine_bomb_count(int16_t bomb_count)
{
    int8_t digit_1 = TILE_NUM_0 + (bomb_count % 10);
    int8_t digit_10 = TILE_NUM_0 + (bomb_count / 10);

    uint8_t cells[2] = { digit_10, digit_1 };
    set_bkg_tiles(BOMB_COUNT_X, BOMB_COUNT_Y, BOMB_COUNT_W, BOMB_COUNT_H, cells);
}

static void bkg_mine_timer(uint8_t timer)
{
    int8_t digit_1 = timer % 10;
    int8_t digit_10 = (timer % 100) / 10;
    int8_t digit_100 = timer / 100;

    uint8_t cells[3] = { digit_100, digit_10, digit_1 };
    set_bkg_tiles(TIMER_X, TIMER_Y, TIMER_W, TIMER_H, cells);
}

static void bkg_mine_clear()
{
    uint8_t cells[4] = {
        TILE_MARK_CLEAR_LU,
        TILE_MARK_CLEAR_RU,
        TILE_MARK_CLEAR_LD,
        TILE_MARK_CLEAR_RD
    };

    set_bkg_tiles(MARK_X, MARK_Y, MARK_W, MARK_H, cells);
}

static void bkg_mine_gameover()
{
    uint8_t cells[4] = {
        TILE_MARK_GAMEOVER_LU,
        TILE_MARK_GAMEOVER_RU,
        TILE_MARK_GAMEOVER_LD,
        TILE_MARK_GAMEOVER_RD
    };

    set_bkg_tiles(MARK_X, MARK_Y, MARK_W, MARK_H, cells);
}

static void bkg_blocks()
{
    set_bkg_tiles(MAP_BLOCK_OFFSET_X, MAP_BLOCK_OFFSET_Y, MINE_WIDTH, MINE_HEIGHT, (uint8_t*)mine_get_blocks());
}
