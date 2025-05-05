#include "scenes.hpp"
#include "../components/transform.hpp"
#include "../components/circle_movement.hpp"
#include "../components/sprite_renderer.hpp"
#include "../components/selector.hpp"
#include "../components/block_grid.hpp"


void init_main_scene(GameObjects::GameManager* gm) {
    GameObjects::GameObject* background = new GameObjects::GameObject();
    {
        auto transform = new Transform();
        transform->localPosition = {0, 0};

        SpriteRenderer* background_renderer = new SpriteRenderer();
        background_renderer->setSprite("rom:/blockblast_background.sprite");

        background->addComponent(background_renderer);
        background->addComponent(transform);
    }
    GameObjects::GameObject* selection = new GameObjects::GameObject();
    {
        auto transform = new Transform();
        transform->localPosition = {27, 107};

        SpriteRenderer* sr = new SpriteRenderer();
        sr->setSprite("rom:/selection.sprite");
        sr->useTransparency = true;

        auto selector = new Selector();
        selector->transform = transform;

        selection->addComponent(transform);
        selection->addComponent(sr);
        selection->addComponent(selector);
    }
    GameObjects::GameObject* grid = new GameObjects::GameObject();
    {
        auto transform = new Transform();
        transform->localPosition = {105, 41};

        auto blg = new BlockGrid();
        blg->size = {8, 8};
        blg->transform = transform;

        grid->addComponent(transform);
        grid->addComponent(blg);
    }

    gm->activeObjects.insert(background);
    background->gameManager = gm;

    background->addChild(selection);
    background->addChild(grid);

}