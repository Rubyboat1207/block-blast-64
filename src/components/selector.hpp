/**
 * @file selector.hpp
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
#include "../engine/gameobject.hpp"
#include "../engine/components/transform.hpp"

COMPONENT(Selector)
    Transform* transform;
    wav64_t select_sound;
    uint8_t last_selected = 0;
    bool c_right_pressed = false;

    int selected = 0;
    void ready() override;
    void update(float dt);
    ~Selector() {}
    bool select(int i);
COMPONENT_END()