#include "minesweeper.h"
#include <rand.h>

#define POS_TO_INDEX(width, x, y) (width * y + x)
#define INDEX_TO_POS_X(width, index) (index % width)
#define INDEX_TO_POS_Y(width, index) (index / width)

static uint8_t game_blocks[MINE_MAX_WIDTH * MINE_MAX_HEIGHT];
static uint8_t game_width;
static uint8_t game_height;
static uint8_t bomb_count;
static uint8_t game_result;

void mine_init(int8_t width, int8_t height, int8_t bomb_count)
{
    for (int i = 0; i < sizeof(game_blocks); i++) {
        game_blocks[i] = MINE_BLOCK_BLANK;
    }

    game_width = width;
    game_height = height;
    bomb_count = bomb_count;
    game_result = MINE_RESULT_PLAYING;
}

void mine_open(int8_t x, int8_t y)
{
    int8_t index = POS_TO_INDEX(game_width, x, y);

    if (game_blocks[index] & MINE_BLOCK_FLAG_OPEN != 0) {
        game_blocks[index] -= MINE_BLOCK_FLAG_OPEN;
    }
/*
  if (game_blocks[index] & MINE_BLOCK_FLAG_OPEN != 0) { // open block
        game_blocks[index] ^= MINE_BLOCK_FLAG_OPEN;

        if (game_blocks[index] & 0x0f == MINE_BLOCK_BOMB) {
            mine->result = MINE_RESULT_GAMEOVER;
        }
    } else { // already opened
        if (game_blocks[index] >= MINE_BLOCK_1 && game_blocks[index] <= MINE_BLOCK_8) {
            // count around bomb
        }
    }
    */
}

void mine_flag(int8_t x, int8_t y)
{
    int8_t index = POS_TO_INDEX(game_width, x, y);
}
