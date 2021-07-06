#include <gb/gb.h>
#include <rand.h>
#include <stdint.h>
#include "helper.h"

static uint16_t _seed;

void rand_init()
{
    _seed = DIV_REG;
}

void rand_init_seed()
{
    _seed |= (uint16_t)DIV_REG << 8;
    initrand(_seed);
}
