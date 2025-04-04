#include "scenes.hpp"
#include "../components/transform.hpp"
#include "../components/circle_movement.hpp"
#include "../components/sprite_renderer.hpp"


void init_main_scene(GameObjects::GameManager* gm) {
    GameObjects::GameObject* go = new GameObjects::GameObject();

    go->add_component(new Transform());
    auto cm = new CircleMovement();
    cm->center = Vector2f{320/2 - 50, 240/2 - 48};
    cm->radius = 50;
    go->add_component(cm);
    auto sr = new SpriteRenderer();
    // sr->visible = false;
    sr->setSprite("rom:/rubyboat.sprite");
    go->add_component(sr);
    debugf("starting\n");
    debugf("%d", gm->active_objects.size());

    gm->active_objects.insert(go);
    go->gameManager = gm;

    GameObjects::GameObject* tophat = new GameObjects::GameObject();
    tophat->add_component(new Transform());
    auto sr2 = new SpriteRenderer();
    sr2->setSprite("rom:/tophat.sprite");
    tophat->add_component(sr2);
    go->add_child(tophat);
    tophat->GET_COMPONENT(Transform)->localPosition = Vector2f{(float) sr2->getSprite()->width / 2, -20};

    debugf("%d", gm->active_objects.size());
}