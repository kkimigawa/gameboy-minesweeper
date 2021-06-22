#include <stdio.h>
#include <stdint.h>
#include <gb/drawing.h>
#include "scene_title.h"
#include "scene.h"
#include "keypad.h"
#include "../assets/bkg_map_title.h"
#include "../assets/bkg_tile_title.h"

#define MAP_WIDTH (20)
#define MAP_HEIGHT (18)

void scene_title_init()
{
    HIDE_BKG;
    HIDE_SPRITES;

    set_bkg_data(0, 127, bkg_tile_title);
    set_bkg_tiles(0, 0, MAP_WIDTH, MAP_HEIGHT, bkg_map_title);

    SHOW_BKG;
}

void scene_title_update()
{
    if (keypad_trigger(KeypadStart)) {
        scene_change(SceneGame);
    }
}
