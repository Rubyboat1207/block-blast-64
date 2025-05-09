/**
 * @file clear_anim_manager.hpp
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

#define CLEAR_ANIM_HORIZONTAL_ORIGIN 64
#define CLEAR_ANIM_VERTICAL_ORIGIN 0
#define CLEAR_ANIM_TOTAL_FRAMES 11
#define CLEAR_ANIM_MAX_COUNT_ACTIVE 12
#define CLEAR_ANIM_TOTAL_HOLD_FRAMES 6

struct ClearAnimation {
    uint8_t index;
    bool vertical;
    uint8_t animation_progress;
    uint8_t hold_time;

    inline ClearAnimation(uint8_t index, bool vertical): index(index), vertical(vertical), animation_progress(0), hold_time(0) {}
};

COMPONENT(ClearAnimationManager)
    ClearAnimation* clear_animations[CLEAR_ANIM_MAX_COUNT_ACTIVE] = {};
    sprite_t* clear_anim_sprite;

    void ready() override;
    void render();
    ~ClearAnimationManager() {}
COMPONENT_END()