#include "scene.h"

static enum Scene current_scene;
static enum Scene prev_scene;

void scene_init()
{
    current_scene = SceneNone;
    prev_scene = SceneNone;
}

inline enum Scene scene_current()
{
    return current_scene;
}

inline int8_t scene_is_changed()
{
    if (prev_scene != current_scene) {
        prev_scene = current_scene;
        return 1;
    }

    return 0;
}

void scene_change(enum Scene scene)
{
    current_scene = scene;
}
