#include "minesweeper.h"
#include <rand.h>

#define POS_TO_INDEX(width, x, y) (width * y + x)
#define INDEX_TO_POS_X(width, index) (index % width)
#define INDEX_TO_POS_Y(width, index) (index / width)1
void mine_init(struct Minesweeper* mine, int8_t width, int8_t height, int8_t bomb_count)
{
    for (int i = 0; i < sizeof(mine->blocks); i++) {
        mine->blocks[i] = MINE_BLOCK_BLANK;
    }

    mine->width = width;
    mine->height = height;
    mine->bomb_count = bomb_count;
    mine->result = MINE_RESULT_PLAYING;
}

void mine_open(struct Minesweeper* mine, int8_t x, int8_t y)
{
    int8_t index = POS_TO_INDEX(mine->width, x, y);

    if (mine->blocks[index] & MINE_BLOCK_FLAG_OPEN != 0) {
        mine->blocks[index] -= MINE_BLOCK_FLAG_OPEN;
    }
/*
  if (mine->blocks[index] & MINE_BLOCK_FLAG_OPEN != 0) { // open block
        mine->blocks[index] ^= MINE_BLOCK_FLAG_OPEN;

        if (mine->blocks[index] & 0x0f == MINE_BLOCK_BOMB) {
            mine->result = MINE_RESULT_GAMEOVER;
        }
    } else { // already opened
        if (mine->blocks[index] >= MINE_BLOCK_1 && mine->blocks[index] <= MINE_BLOCK_8) {
            // count around bomb
        }
    }
    */
}

void mine_flag(struct Minesweeper* mine, int8_t x, int8_t y)
{
    int8_t index = POS_TO_INDEX(mine->width, x, y);
}
