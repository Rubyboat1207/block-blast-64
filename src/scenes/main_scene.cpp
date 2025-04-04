#include "scenes.hpp"
#include "../components/transform.hpp"
#include "../components/circle_movement.hpp"
#include "../components/sprite_renderer.hpp"
#include "../components/player.hpp"


void init_main_scene(GameObjects::GameManager* gm) {
    GameObjects::GameObject* go = new GameObjects::GameObject();

    go->addComponent(new Transform());
    // auto cm = new CircleMovement();
    // cm->center = Vector2f{320/2 - 50, 240/2 - 48};
    // cm->radius = 50;
    // go->addComponent(cm);
    auto sr = new SpriteRenderer();
    sr->setSprite("rom:/rubyboat.sprite");
    go->addComponent(sr);
    go->addComponent(new Player());

    gm->activeObjects.insert(go);
    go->gameManager = gm;

    GameObjects::GameObject* tophat = new GameObjects::GameObject();
    tophat->addComponent(new Transform());
    auto sr2 = new SpriteRenderer();
    sr2->setSprite("rom:/tophat.sprite");
    sr2->useTransparency = true;
    tophat->addComponent(sr2);
    go->addChild(tophat);
    tophat->GET_COMPONENT(Transform)->localPosition = Vector2f{(float) sr2->getSprite()->width / 2, -20};
}