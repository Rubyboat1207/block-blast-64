/**
 * @file clear_anim_manager.cpp
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

#include "clear_anim_manager.hpp"

void ClearAnimationManager::ready()
{
    clear_anim_sprite = sprite_load("rom:/destroy_anim.sprite");
}

void ClearAnimationManager::render()
{
    for(int i = 0; i < CLEAR_ANIM_MAX_COUNT_ACTIVE; i++) {
        if(clear_animations[i] == nullptr) {
            continue;
        }

        if(clear_animations[i]->hold_time < CLEAR_ANIM_TOTAL_HOLD_FRAMES) {
            clear_animations[i]->hold_time += 1;
        }else {
            clear_animations[i]->hold_time = 0;
            clear_animations[i]->animation_progress++;
        }

        if(clear_animations[i]->animation_progress >= CLEAR_ANIM_TOTAL_FRAMES) {
            delete clear_animations[i];
            clear_animations[i] = nullptr;
            continue;
        }

        rdpq_blitparms_s params = {};
        params.s0 = clear_animations[i]->animation_progress * 24;
        params.width = 24;
        // params.cx = 24 / 2;
        // params.cy = clear_anim_sprite->height / 2;
        if(clear_animations[i]->vertical) {
            rdpq_set_mode_copy(true);
        }else {
            rdpq_set_mode_standard();
            params.theta = 3.1415f / 2;
        }

        rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
        rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
        rdpq_set_prim_color(RGBA32(255,255,255,255));
        rdpq_mode_alphacompare(254);

        Vector2i pos{0,0};
        if(clear_animations[i]->vertical) {
            pos.y = CLEAR_ANIM_VERTICAL_ORIGIN;
            pos.x = clear_animations[i]->index * 24 + 105;
        }else {
            pos.x = CLEAR_ANIM_HORIZONTAL_ORIGIN;
            pos.y = clear_animations[i]->index * 24 + 41 + 24;
        }

        rdpq_sprite_blit(clear_anim_sprite, pos.x, pos.y, &params);
    }
}