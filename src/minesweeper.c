#include <rand.h>
#include "minesweeper.h"

#define MINE_MAX_WIDTH (20)
#define MINE_MAX_HEIGHT (16)
#define MINE_BLOCK_SIZE (MINE_MAX_WIDTH * MINE_MAX_HEIGHT)

#define MINE_STATUS_BLANK (1)
#define MINE_STATUS_BOMB (2)
#define MINE_STATUS_NUM_1 (3)
#define MINE_STATUS_NUM_2 (4)
#define MINE_STATUS_NUM_3 (5)
#define MINE_STATUS_NUM_4 (6)
#define MINE_STATUS_NUM_5 (7)
#define MINE_STATUS_NUM_6 (8)
#define MINE_STATUS_NUM_7 (9)
#define MINE_STATUS_NUM_8 (10)
#define MINE_STATUS_FLAG_CHECK (32)
#define MINE_STATUS_FLAG_OPEN (64)

#define POS_TO_INDEX(x, y) (_width * y + x)
#define INDEX_TO_POS_X(index) (index % _width)
#define INDEX_TO_POS_Y(index) (index / _width)

static uint8_t _blocks[MINE_BLOCK_SIZE];
static uint8_t _statuses[MINE_BLOCK_SIZE];
static int16_t _width;
static int16_t _height;
static int16_t _bomb_count;
static int16_t _check_bomb_count;
static int8_t _is_created;
static int8_t _result;

static void create_game(int16_t x, int16_t y);
static void recursive_open(int16_t x, int16_t y);

void mine_init(int16_t width, int16_t height, int16_t bomb_count)
{
    for (int i = 0; i < MINE_BLOCK_SIZE; i++) {
        _blocks[i] = MINE_BLOCK_CLOSE;
        _statuses[i] = MINE_STATUS_BLANK;
    }

    _width = width;
    if (_width > MINE_MAX_WIDTH) {
        _width = MINE_MAX_WIDTH;
    }

    _height = height;
    if (_height > MINE_MAX_HEIGHT) {
        _height = MINE_MAX_HEIGHT;
    }

    _bomb_count = bomb_count;
    _check_bomb_count = bomb_count;
    _is_created = 0;
    _result = MINE_RESULT_PLAYING;
}

int8_t mine_open(int16_t x, int16_t y)
{
    if (_result != MINE_RESULT_PLAYING) { return 0; }

    if (!_is_created) {
        create_game(x, y);
    }

    int16_t index = POS_TO_INDEX(x, y);

    // checked block
    if (_statuses[index] & MINE_STATUS_FLAG_CHECK) { return 0; }

    // already open
    if (_statuses[index] & MINE_STATUS_FLAG_OPEN) { return 0; }

    uint8_t status = _statuses[index];
    if (status == MINE_STATUS_BLANK) {
        recursive_open(x, y);
    } else if (status >= MINE_STATUS_NUM_1 && status <= MINE_STATUS_NUM_8) {
        _blocks[index] = MINE_BLOCK_NUM_1 + (status - MINE_STATUS_NUM_1);
    } else if (status == MINE_STATUS_BOMB) {
        _result = MINE_RESULT_GAMEOVER;
        _blocks[index] = MINE_BLOCK_HIT_BOMB;

        for (int16_t i = 0; i < MINE_BLOCK_SIZE; i++) {
            if (i == index) { continue; }

            if ((_statuses[i] & 0x0f) == MINE_STATUS_BOMB) {
                _blocks[i] = MINE_BLOCK_BOMB;
            }
        }
    }

    _statuses[index] |= MINE_STATUS_FLAG_OPEN;

    if (_result == MINE_RESULT_PLAYING) {
        int16_t dont_open_block_count = 0;
        for (int16_t i = 0; i < MINE_BLOCK_SIZE; i++) {
            if ((_statuses[i] & MINE_STATUS_FLAG_OPEN) == 0) {
                dont_open_block_count++;
            }
        }

        if (dont_open_block_count == _bomb_count) {
            _result = MINE_RESULT_CLEAR;
        }
    }

    return 1;
}

int8_t mine_check(int16_t x, int16_t y)
{
    if (_result != MINE_RESULT_PLAYING) { return 0; }

    int16_t index = POS_TO_INDEX(x, y);

    if (_statuses[index] & MINE_STATUS_FLAG_OPEN) {
        return 0;
    }

    if (_statuses[index] & MINE_STATUS_FLAG_CHECK) {
        _statuses[index] ^= MINE_STATUS_FLAG_CHECK;
        _blocks[index] = MINE_BLOCK_CLOSE;
        _check_bomb_count++;
    } else if (_check_bomb_count > 0) {
        _statuses[index] |= MINE_STATUS_FLAG_CHECK;
        _blocks[index] = MINE_BLOCK_FLAG;
        _check_bomb_count--;
    } else {
        return 0;
    }

    return 1;
}

const uint8_t* mine_get_blocks()
{
    return _blocks;
}

int8_t mine_get_result()
{
    return _result;
}

int16_t mine_get_check_bomb_count()
{
    return _check_bomb_count;
}

static void create_game(int16_t x, int16_t y)
{
    int16_t available_set_bomb_indexes[MINE_BLOCK_SIZE];
    int16_t available_set_bomb_index_size = 0;

    // search put bomb pos
    for (int16_t yy = 0; yy < _height; yy++) {
        for (int16_t xx = 0; xx < _width; xx++) {
            // exclude first open pos and around pos
            if (xx >= x - 1 && xx <= x + 1 && yy >= y - 1 && yy <= y + 1) {
                continue;
            }

            available_set_bomb_indexes[available_set_bomb_index_size] = POS_TO_INDEX(xx, yy);
            available_set_bomb_index_size++;
        }
    }

    // shuffle
    {
        int16_t rand_i;
        int16_t swap;

        for (int16_t i = 0; i < available_set_bomb_index_size; i++) {
            rand_i = randw() % available_set_bomb_index_size;

            swap = available_set_bomb_indexes[i];
            available_set_bomb_indexes[i] = available_set_bomb_indexes[rand_i];
            available_set_bomb_indexes[rand_i] = swap;
        }
    }

    // set bomb
    for (int16_t i = 0; i < _bomb_count; i++) {
        _statuses[available_set_bomb_indexes[i]] = MINE_STATUS_BOMB;
    }

    // numbering bomb around
    //
    // example)
    //  1221
    //  2@@1
    //  2@31
    for (int16_t i = 0; i < _bomb_count; i++) {
        int16_t bomb_x = INDEX_TO_POS_X(available_set_bomb_indexes[i]);
        int16_t bomb_y = INDEX_TO_POS_Y(available_set_bomb_indexes[i]);

        for (int16_t around_y = bomb_y - 1; around_y <= bomb_y + 1; around_y++) {
            for (int16_t around_x = bomb_x - 1; around_x <= bomb_x + 1; around_x++) {
                if (around_x < 0 || around_x >= _width || around_y < 0 || around_y >= _height) {
                    continue;
                }

                int16_t index = POS_TO_INDEX(around_x, around_y);
                if (_statuses[index] == MINE_STATUS_BOMB) {
                    continue;
                } else if (_statuses[index] == MINE_STATUS_BLANK) {
                    _statuses[index] = MINE_STATUS_NUM_1;
                } else {
                    // increment bomb number
                    // MINE_STATUS_NUM_2 to MINE_STATUS_NUM_8
                    _statuses[index]++;
                }
            }
        }
    }

    _is_created = 1;
}

static void recursive_open(int16_t x, int16_t y)
{
    int16_t index;
    uint8_t status;

    for (int16_t around_y = y - 1; around_y <= y + 1; around_y++) {
        for (int16_t around_x = x - 1; around_x <= x + 1; around_x++) {
            if (around_x < 0 || around_x >= _width || around_y < 0 || around_y >= _height) {
                continue;
            }

            index = POS_TO_INDEX(around_x, around_y);
            if (_statuses[index] & MINE_STATUS_FLAG_OPEN) { continue; }

            _statuses[index] |= MINE_STATUS_FLAG_OPEN;

            status = _statuses[index] & 0x0f;

            if (status == MINE_STATUS_BLANK) {
                _blocks[index] = MINE_BLOCK_BLANK;
                recursive_open(around_x, around_y);
            } else if (status >= MINE_STATUS_NUM_1 && status <= MINE_STATUS_NUM_8) {
                _blocks[index] = MINE_BLOCK_NUM_1 + (status - MINE_STATUS_NUM_1);
            }
        }
    }
}
