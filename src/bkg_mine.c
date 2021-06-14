#include <gb/gb.h>
#include "bkg_mine.h"
#include "../assets/bkg_tile_mine.h"
#include "../assets/bkg_map_mine.h"

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

void bkg_mine_setup()
{
    set_bkg_data(0, 30, bkg_tile_mine);
    set_bkg_tiles(0, 0, MAP_MINE_WIDTH, MAP_MINE_HEIGHT, bkg_map_mine);

    SHOW_BKG;
}

void bkg_mine_bomb_count(uint8_t bomb_count)
{
    uint8_t digit_1 = bomb_count % 10;
    uint8_t digit_10 = bomb_count / 10;

    uint8_t cells[2] = { digit_10, digit_1 };
    set_bkg_tiles(BOMB_COUNT_X, BOMB_COUNT_Y, BOMB_COUNT_W, BOMB_COUNT_H, cells);
}

void bkg_mine_timer(uint8_t timer)
{
    uint8_t digit_1 = timer % 10;
    uint8_t digit_10 = (timer % 100) / 10;
    uint8_t digit_100 = timer / 100;

    uint8_t cells[3] = { digit_100, digit_10, digit_1 };
    set_bkg_tiles(TIMER_X, TIMER_Y, TIMER_W, TIMER_H, cells);
}

void bkg_mine_gameover()
{
    uint8_t cells[4] = {
        TILE_MARK_GAMEOVER_LU,
        TILE_MARK_GAMEOVER_RU,
        TILE_MARK_GAMEOVER_LD,
        TILE_MARK_GAMEOVER_RD
    };

    set_bkg_tiles(MARK_X, MARK_Y, MARK_W, MARK_H, cells);
}
