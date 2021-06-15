#include <gb/gb.h>
#include "keypad.h"
#include "scene.h"
#include "scene_game.h"

void main()
{
    scene_init();
    scene_change(SceneGame);

    keypad_init();

    while (1) {
        keypad_update();

        if (scene_is_changed()) {
            switch (scene_current()) {
                case SceneTitle:
                    break;

                case SceneGame:
                    scene_game_init();
                    break;
            }
        }

        switch (scene_current()) {
            case SceneTitle:
                break;

            case SceneGame:
                scene_game_update();
                break;
        }

        wait_vbl_done();
    }
}
