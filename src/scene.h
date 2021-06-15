#pragma once

#include <stdint.h>

enum Scene {
    SceneNone,
    SceneTitle,
    SceneGame,
};

void scene_init();
inline enum Scene scene_current();
inline int8_t scene_is_changed();
void scene_change(enum Scene scene);
