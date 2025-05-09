/**
 * @file sprite_renderer.cpp
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

#include "../gameobject.hpp"
#include <libdragon.h>
#include "transform.hpp"
#include "sprite_renderer.hpp"

using namespace GameObjects;

void SpriteRenderer::render() {
    Component::render();
    if(!visible) {
        return;
    }
    Vector2f globalPos = transform->getGlobalPosition();
    #if USING_CAMERA
    globalPos += gameObject->gameManager->camera_pos;
    #endif

    if(useTransparency) {
        if(fastRender) {
            rdpq_set_mode_copy(true);
        }else {
            rdpq_set_mode_standard();
        }
        rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
        rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
        rdpq_set_prim_color(tint);
        rdpq_set_fog_color(tint);
        rdpq_mode_alphacompare(1);
        rdpq_sprite_blit(sprite, globalPos.x, globalPos.y, rdpq_blitparams);
    }else {
        if(fastRender) {
            rdpq_set_mode_copy(false);
        }else {
            rdpq_set_mode_standard();
        }
        rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
        rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
        rdpq_set_prim_color(tint);
        rdpq_mode_alphacompare(0);
        rdpq_sprite_blit(sprite, globalPos.x, globalPos.y, rdpq_blitparams);
    }
}

void SpriteRenderer::ready() {
    Component::ready();
    if(gameObject == nullptr) {
        return;
    }
    transform = gameObject->GET_COMPONENT(Transform);
}

void SpriteRenderer::setSprite(const char *spritePath) {
    this->spritePath = spritePath;

    sprite = sprite_load(spritePath);
}

const char *SpriteRenderer::getSpritePath()
{
    return spritePath;
}

sprite_t *SpriteRenderer::getSprite()
{
    return sprite;
}
