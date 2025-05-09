/**
 * @file block_grid.hpp
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

enum class BlockState {
    EMPTY,
    RED,
    PURPLE,
    BLUE,
    YELLOW,
    GREEN,
    ORANGE,
    GRAY
};

#define BLOCKS_COLOR_BLUE(alpha) RGBA32(32, 134, 230,alpha)
#define BLOCKS_COLOR_PURPLE(alpha) RGBA32(143, 74, 212,alpha)
#define BLOCKS_COLOR_RED(alpha) RGBA32(255, 94, 94,alpha)
#define BLOCKS_COLOR_YELLOW(alpha) RGBA32(252, 223, 3,alpha)
#define BLOCKS_COLOR_GREEN(alpha) RGBA32(51, 161, 62,alpha)
#define BLOCKS_COLOR_ORANGE(alpha) RGBA32(235, 149, 38,alpha)
#define BLOCKS_COLOR_GRAY(alpha) RGBA32(64, 64, 64, alpha)


COMPONENT(BlockGrid)
    bool visible = true;
    Vector2i size;
    Transform* transform;
    BlockState** state;
    sprite_t* empty_sprite;
    sprite_t* filled_sprite;
    Vector2i getBounding();
    uint8_t alpha = 255;
    void ready() override;
    void render() override;
    ~BlockGrid() {}
    void setState(Vector2i pos, BlockState block_state);
    void clear();
COMPONENT_END()