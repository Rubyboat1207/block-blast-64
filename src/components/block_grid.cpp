/**
 * @file block_grid.cpp
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

#include "block_grid.hpp"

void BlockGrid::ready()
{
    state = new BlockState*[size.x];

    for(int i = 0; i < size.x; i++) {
        state[i] = new BlockState[size.y];
    }

    for(int x = 0; x < size.x; x++) {
        for(int y = 0; y < size.y; y++) {
            state[x][y] = BlockState::EMPTY;
        }
    }
}

void BlockGrid::render() {
    if(!visible) {
        return;
    }
    auto offset = transform->getGlobalPosition();
    for(int x = 0; x < size.x; x++) {
        for(int y = 0; y < size.y; y++) {
            auto b_state = state[x][y];

            if(empty_sprite == nullptr && b_state == BlockState::EMPTY) {
                continue;
            }

            auto position = offset + Vector2f{(float) x * filled_sprite->width, (float) y * filled_sprite->height};

            sprite_t* sprite = filled_sprite;

            rdpq_set_mode_standard();
            if(alpha == 255) {
                rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
                rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
                switch (b_state) {
                    case(BlockState::EMPTY): {
                        sprite = empty_sprite;
                        rdpq_set_prim_color(RGBA32(255,255,255,255));
                    }break;
                    case(BlockState::BLUE): rdpq_set_prim_color(BLOCKS_COLOR_BLUE(255)); break;
                    case(BlockState::PURPLE): rdpq_set_prim_color(BLOCKS_COLOR_PURPLE(255)); break;
                    case(BlockState::RED): rdpq_set_prim_color(BLOCKS_COLOR_RED(255)); break;
                    case(BlockState::YELLOW): rdpq_set_prim_color(BLOCKS_COLOR_YELLOW(255)); break;
                    case(BlockState::GREEN): rdpq_set_prim_color(BLOCKS_COLOR_GREEN(255)); break;
                    case(BlockState::ORANGE): rdpq_set_prim_color(BLOCKS_COLOR_ORANGE(255)); break;
                    case(BlockState::GRAY): rdpq_set_prim_color(BLOCKS_COLOR_GRAY(255)); break;
                }
            }else {
                rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY_CONST);
                rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
                switch (b_state) {
                    case(BlockState::EMPTY): {
                        sprite = empty_sprite;
                        rdpq_set_fog_color(RGBA32(255,255,255,alpha));
                    }break;
                    case(BlockState::BLUE): rdpq_set_prim_color(BLOCKS_COLOR_BLUE(alpha)); rdpq_set_fog_color(BLOCKS_COLOR_BLUE(alpha)); break;
                    case(BlockState::PURPLE): rdpq_set_prim_color(BLOCKS_COLOR_PURPLE(alpha)); rdpq_set_fog_color(BLOCKS_COLOR_PURPLE(alpha)); break;
                    case(BlockState::RED): rdpq_set_prim_color(BLOCKS_COLOR_RED(alpha)); rdpq_set_fog_color(BLOCKS_COLOR_RED(alpha)); break;
                    case(BlockState::YELLOW): rdpq_set_prim_color(BLOCKS_COLOR_YELLOW(alpha)); rdpq_set_fog_color(BLOCKS_COLOR_YELLOW(alpha)); break;
                    case(BlockState::GREEN): rdpq_set_prim_color(BLOCKS_COLOR_GREEN(alpha)); rdpq_set_fog_color(BLOCKS_COLOR_GREEN(alpha)); break;
                    case(BlockState::ORANGE): rdpq_set_prim_color(BLOCKS_COLOR_ORANGE(alpha)); rdpq_set_fog_color(BLOCKS_COLOR_ORANGE(alpha)); break;
                    case(BlockState::GRAY): rdpq_set_prim_color(BLOCKS_COLOR_GRAY(alpha)); rdpq_set_fog_color(BLOCKS_COLOR_GRAY(alpha)); break;
                }
            }

            
            
            

            rdpq_sprite_blit(sprite, position.x, position.y, NULL);
        }
    }
}

void BlockGrid::setState(Vector2i pos, BlockState block_state)
{
    state[pos.x][pos.y] = block_state;
}



Vector2i BlockGrid::getBounding()
{
    if (!this->state || !this->filled_sprite)
        return {0, 0};

    int blockSize = filled_sprite->width;

    Vector2i minPos{size.x, size.y};
    Vector2i maxPos{0, 0};
    bool found = false;

    for (int y = 0; y < size.y; ++y) {
        for (int x = 0; x < size.x; ++x) {
            if (state[x][y] != BlockState::EMPTY) {
                if (!found) {
                    minPos = { x, y };
                    maxPos = { x, y };
                    found = true;
                } else {
                    if (x < minPos.x) minPos.x = x;
                    if (y < minPos.y) minPos.y = y;
                    if (x > maxPos.x) maxPos.x = x;
                    if (y > maxPos.y) maxPos.y = y;
                }
            }
        }
    }

    if (found) {
        return {
            (maxPos.x - minPos.x + 1) * blockSize,
            (maxPos.y - minPos.y + 1) * blockSize
        };
    } else {
        return {
            0,
            0
        };
    }
}

void BlockGrid::clear()
{
    for (int y = 0; y < size.y; ++y) {
        for (int x = 0; x < size.x; ++x) {
            state[x][y] = BlockState::EMPTY;
        }
    }
}
