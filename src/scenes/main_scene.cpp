#include "scenes.hpp"
#include "../components/transform.hpp"
#include "../components/circle_movement.hpp"
#include "../components/sprite_renderer.hpp"
#include "../components/selector.hpp"
#include "../components/block_grid.hpp"
#include "../components/cursor.hpp"
#include "../components/game_logic.hpp"
#include "../components/text_renderer.hpp"


void init_main_scene(GameObjects::GameManager* gm) {
    GameObjects::GameObject* gameLogic = new GameObjects::GameObject();
    auto gl = new GameLogic();
    gameLogic->addComponent(gl);

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
        transform->localPosition = {31, 41};

        SpriteRenderer* sr = new SpriteRenderer();
        sr->setSprite("rom:/selection.sprite");
        sr->useTransparency = true;

        auto selector = new Selector();
        selector->transform = transform;

        selection->addComponent(transform);
        selection->addComponent(sr);
        selection->addComponent(selector);
        gl->selector = selector;
    }
    GameObjects::GameObject* grid = new GameObjects::GameObject();
    {
        auto transform = new Transform();
        transform->localPosition = {105, 41};

        auto blg = new BlockGrid();
        blg->size = {8, 8};
        blg->transform = transform;
        blg->empty_sprite = sprite_load("rom:/block_empty.sprite");
        blg->filled_sprite = sprite_load("rom:/block_normal.sprite");

        grid->addComponent(transform);
        grid->addComponent(blg);
        gl->main_grid = blg;
    }
    GameObjects::GameObject* preview_grid = new GameObjects::GameObject();
    {
        auto transform = new Transform();
        transform->localPosition = {0, 0};

        auto blg = new BlockGrid();
        blg->size = {8, 8};
        blg->transform = transform;
        blg->empty_sprite = nullptr;
        blg->filled_sprite = sprite_load("rom:/block_normal.sprite");
        blg->alpha = 128;

        preview_grid->addComponent(transform);
        preview_grid->addComponent(blg);
    }

    GameObjects::GameObject* cursor_container = new GameObjects::GameObject();
    {
        auto transform = new Transform();
        transform->localPosition = {105, 41};

        cursor_container->addComponent(transform);
    }

    auto c = new Cursor();
    GameObjects::GameObject* cursor = new GameObjects::GameObject();
    {
        auto transform = new Transform();
        transform->localPosition = {105, 41};

        auto blg = new BlockGrid();
        blg->size = {3, 3};
        blg->transform = transform;
        blg->empty_sprite = nullptr;
        blg->filled_sprite = sprite_load("rom:/block_normal.sprite");

        c->display_grid = blg;
        c->transform = transform;
        c->bounds = {192, 192};
        c->preview_grid = preview_grid->GET_COMPONENT(BlockGrid);
        gl->cursor = c;

        cursor->addComponent(transform);
        cursor->addComponent(blg);
        cursor->addComponent(c);
    }
    GameObjects::GameObject* hand = new GameObjects::GameObject();
    {
        auto transform = new Transform();
        transform->localPosition = {0, 0};

        SpriteRenderer* sr = new SpriteRenderer();
        sr->useTransparency = true;
        sr->setSprite("rom:/hand.sprite");

        hand->addComponent(sr);
        hand->addComponent(transform);
        c->hand = transform;
        c->handRenderer = sr;
    }
    GameObjects::GameObject* lose_screen = new GameObjects::GameObject();
    {
        auto transform = new Transform();
        transform->localPosition = {105, 41};

        auto sr = new SpriteRenderer();
        sr->setSprite("rom:/lose_screen.sprite");
        sr->visible = false;
        sr->useTransparency = true;

        lose_screen->addComponent(transform);
        lose_screen->addComponent(sr);

        gl->lose_screen = sr;
    }
    GameObjects::GameObject* points = new GameObjects::GameObject();
    {
        auto transform = new Transform();
        transform->localPosition = {161, 22};
        
        auto textRenderer = new TextRenderer();
        textRenderer->text = "0";

        points->addComponent(transform);
        points->addComponent(textRenderer);

        gl->points_renderer = textRenderer;
    }
    GameObjects::GameObject* high_score = new GameObjects::GameObject();
    {
        auto transform = new Transform();
        transform->localPosition = {31, 22};
        
        auto textRenderer = new TextRenderer();
        textRenderer->text = "0";

        high_score->addComponent(transform);
        high_score->addComponent(textRenderer);

        gl->high_score_renderer = textRenderer;
    }

    


    gm->activeObjects.insert(background);
    background->gameManager = gm;

    background->addChild(gameLogic);
    background->addChild(selection);
    background->addChild(grid);
    grid->addChild(preview_grid);
    background->addChild(cursor_container);
    cursor_container->addChild(cursor);
    cursor->addChild(hand);
    background->addChild(lose_screen);
    background->addChild(points);
    background->addChild(high_score);

    for(int i = 0; i < 3; i++) {
        GameObjects::GameObject* previewContainer = new GameObjects::GameObject();
        {
            auto transform = new Transform();
            if(i == 0) {
                transform->localPosition = {33, 43};
            }else if(i == 1) {
                transform->localPosition = {33, 110};
            }else if(i == 2) {
                transform->localPosition = {33, 175};
            }
            previewContainer->addComponent(transform);
        }

        GameObjects::GameObject* preview = new GameObjects::GameObject();
        auto transform = new Transform();
        transform->localPosition = {0,0};
        

        BlockGrid* blg = new BlockGrid();
        blg->size = {3,3};
        blg->transform = transform;
        blg->empty_sprite = nullptr;
        blg->filled_sprite = sprite_load("rom:/block_tiny.sprite");

        preview->addComponent(blg);
        preview->addComponent(transform);

        gameLogic->addChild(previewContainer);
        previewContainer->addChild(preview);

        gl->previews[i] = blg;
    }
}