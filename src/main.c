#include <gb/gb.h>
#include "keypad.h"
#include "scene.h"
#include "scene_title.h"
#include "scene_game.h"

void main()
{
    scene_init();
    scene_change(SceneTitle);

    keypad_init();

    enum Scene scene;

    while (1) {
        keypad_update();

        scene = scene_current();

        if (scene_is_changed()) {
            if (scene == SceneTitle) {
                scene_title_init();
            } else if (scene == SceneGame) {
                scene_game_init();
            }
        }

        if (scene == SceneTitle) {
            scene_title_update();
        } else if (scene == SceneGame) {
            scene_game_update();
        }

        wait_vbl_done();
    }
}
