/**
 * @file sprite_renderer.hpp
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

 #pragma once
#include "../gameobject.hpp"
#include "transform.hpp"
#include <libdragon.h>

COMPONENT(SpriteRenderer)

private:
    const char* spritePath;
    sprite_t* sprite;
    Transform* transform;
public:
    bool useTransparency = false;
    bool fastRender = true;
    rdpq_blitparms_t * rdpq_blitparams = NULL;
    color_t tint{255,255,255,255};
    bool visible = true;
    void render() override;
    void ready() override;
    void setSprite(const char* spritePath);
    const char* getSpritePath();
    sprite_t* getSprite();
    ~SpriteRenderer() {}
    
COMPONENT_END()