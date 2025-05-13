/**
 * @file cursor.hpp
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
#include "block_grid.hpp"
#include "../engine/components/sprite_renderer.hpp"



COMPONENT(Cursor)
    BlockGrid* display_grid;
    BlockGrid* preview_grid;
    Vector2i last_grid_pos{};
    float speed = 300.0f;
    float acceleration = 1500.0f;
    float time_since_a_pressed = 0.0f;
    Vector2f bounds;
    Vector2i collision;
    Transform* transform;
    Transform* hand;
    Vector2f velocity{0,0};
    bool was_a_pressed;
    void ready() override;
    void update(float dt) override;
    void update_collision();
    Vector2i get_closest_grid_space(BlockGrid* grid) const;
    SpriteRenderer* handRenderer;
    void update_preview_grid(Vector2i* pos, bool forceRefresh);
    ~Cursor() {}
COMPONENT_END()