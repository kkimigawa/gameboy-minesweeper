#pragma once

#include <stdint.h>

#define MINE_MAX_WIDTH (16)
#define MINE_MAX_HEIGHT (16)

#define MINE_BLOCK_BLANK (0)
#define MINE_BLOCK_1 (1)
#define MINE_BLOCK_2 (2)
#define MINE_BLOCK_3 (3)
#define MINE_BLOCK_4 (4)
#define MINE_BLOCK_5 (5)
#define MINE_BLOCK_6 (6)
#define MINE_BLOCK_7 (7)
#define MINE_BLOCK_8 (8)
#define MINE_BLOCK_BOMB (9)
#define MINE_BLOCK_FLAG_CHECK (1<<6)
#define MINE_BLOCK_FLAG_OPEN (1<<7)

#define MINE_RESULT_PLAYING (0)
#define MINE_RESULT_CLEAR (1)
#define MINE_RESULT_GAMEOVER (2)

struct Minesweeper {
    uint8_t blocks[MINE_MAX_WIDTH * MINE_MAX_HEIGHT];
    int8_t width;
    int8_t height;
    int8_t bomb_count;
    int8_t result;
};

void mine_init(struct Minesweeper* mine, int8_t width, int8_t height, int8_t bomb_count);
void mine_start(struct Minesweeper* mine, int8_t x, int8_t y);
void mine_open(struct Minesweeper* mine, int8_t x, int8_t y);
void mine_check(struct Minesweeper* mine, int8_t x, int8_t y);
