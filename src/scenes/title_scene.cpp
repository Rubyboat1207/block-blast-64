/**
 * @file title_scene.cpp
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 * 
 * Copyright (C) 2025 Rubyboat (owner of https://github.com/Rubyboat1207)
 */

#include "scenes.hpp"
#include "../components/transform.hpp"
#include "../components/sprite_renderer.hpp"
#include "../components/selector.hpp"
#include "../components/block_grid.hpp"
#include "../components/cursor.hpp"
#include "../components/game_logic.hpp"
#include "../components/text_renderer.hpp"
#include "../components/clear_anim_manager.hpp"
#include "../components/start_screen.hpp"
#include "../save_manager.hpp"

void init_title_scene(GameObjects::GameManager *gm)
{
    if(save_manager == nullptr) {
        save_manager = new SaveManager();
        save_manager->load();
    }
    GameObjects::GameObject* root = new GameObjects::GameObject();
    {
        auto transform = new Transform();
        transform->localPosition = {0, 0};
        root->addComponent(new StartScreen());

        root->addComponent(transform);
    }

    GameObjects::GameObject* title = new GameObjects::GameObject();
    {
        auto transform = new Transform();

        auto sr = new SpriteRenderer();
        sr->useTransparency = true;
        sr->setSprite("rom:/title.sprite");

        transform->localPosition = {320 / 2 - sr->getSprite()->width / 2.0f, 10};
        title->addComponent(transform);
        title->addComponent(sr);
    }

    GameObjects::GameObject* title_l = new GameObjects::GameObject();
    {
        auto transform = new Transform();
        transform->localPosition = {0,0};

        auto sr = new SpriteRenderer();
        sr->useTransparency = true;
        sr->setSprite("rom:/title_l.sprite");
        switch(random_u32() % 5) {
            case(0): sr->tint = BLOCKS_COLOR_PURPLE(255); break;
            case(1): sr->tint = BLOCKS_COLOR_RED(255); break;
            case(2): sr->tint = BLOCKS_COLOR_YELLOW(255); break;
            case(3): sr->tint = BLOCKS_COLOR_GREEN(255); break;
            case(4): sr->tint = BLOCKS_COLOR_ORANGE(255); break;
        }
        sr->fastRender = false;


        title->addComponent(transform);
        title->addComponent(sr);
    }
    GameObjects::GameObject* title_c = new GameObjects::GameObject();
    {
        auto transform = new Transform();
        transform->localPosition = {0,0};

        auto sr = new SpriteRenderer();
        sr->useTransparency = true;
        sr->setSprite("rom:/title_c.sprite");
        sr->tint = BLOCKS_COLOR_BLUE(255);
        switch(random_u32() % 3) {
            case(0): sr->tint = BLOCKS_COLOR_PURPLE(255); break;
            case(1): sr->tint = BLOCKS_COLOR_RED(255); break;
            case(2): sr->tint = BLOCKS_COLOR_YELLOW(255); break;
        }
        sr->fastRender = false;


        title->addComponent(transform);
        title->addComponent(sr);
    }

    GameObjects::GameObject* text = new GameObjects::GameObject();
    {
        auto transform = new Transform();
        transform->localPosition = {100,200};

        auto text_renderer = new TextRenderer();

        text_renderer->text = "Press START to play!";


        text->addComponent(transform);
        text->addComponent(text_renderer);
    }
    


    gm->activeObjects.insert(root);
    gm->setRoot(root);

    root->gameManager = gm;

    root->addChild(title);
    title->addChild(title_c);
    title->addChild(title_l);
    root->addChild(text);
}