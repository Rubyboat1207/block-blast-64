#include "scenes.hpp"
#include "../components/transform.hpp"
#include "../components/circle_movement.hpp"
#include "../components/sprite_renderer.hpp"


void init_main_scene(GameObjects::GameManager* gm) {
    GameObjects::GameObject* go = new GameObjects::GameObject();

    go->addComponent(new Transform());

    gm->activeObjects.insert(go);
    go->gameManager = gm;
}