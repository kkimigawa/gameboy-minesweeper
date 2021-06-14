#pragma once

#include <stdint.h>

/* struct GbAnimSprite { */
/*     uint8_t anim_count; */
/*     uint8_t anim_start_tile; */
/*     uint8_t anim_end_tile; */
/* }; */

void set_sprite_tile16(uint8_t nb, uint8_t tile);
void move_sprite16(uint8_t nb, uint8_t x, uint8_t y);

//void gb_anim_sprite_setup(struct GbAnimSprite* anim);
