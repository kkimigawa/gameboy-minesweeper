#pragma once

#include <stdint.h>

#define MINE_BLOCK_CLOSE (0)
#define MINE_BLOCK_BLANK (1)
#define MINE_BLOCK_FLAG (2)
#define MINE_BLOCK_QUESTION (3)
#define MINE_BLOCK_BOMB (4)
#define MINE_BLOCK_HIT_BOMB (5)
#define MINE_BLOCK_NUM_1 (7)
#define MINE_BLOCK_NUM_2 (8)
#define MINE_BLOCK_NUM_3 (9)
#define MINE_BLOCK_NUM_4 (10)
#define MINE_BLOCK_NUM_5 (11)
#define MINE_BLOCK_NUM_6 (12)
#define MINE_BLOCK_NUM_7 (13)
#define MINE_BLOCK_NUM_8 (14)

#define MINE_RESULT_PLAYING (0)
#define MINE_RESULT_CLEAR (1)
#define MINE_RESULT_GAMEOVER (2)

// initialize minesweeper
void mine_init(int16_t width, int16_t height, int16_t bomb_count);

// open block
int8_t mine_open(int16_t x, int16_t y);

// checked flag
int8_t mine_check(int16_t x, int16_t y);

// get gameboy map tile list
const uint8_t* mine_get_blocks();

// get game result
int8_t mine_get_result();

// get checked flag count
int16_t mine_get_check_bomb_count();
