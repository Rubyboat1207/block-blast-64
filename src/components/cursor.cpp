/**
 * @file cursor.cpp
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

#include "cursor.hpp"
#include "game_logic.hpp"

void Cursor::update(float dt) {
    Component::update(dt);

    if(rootGameLogic->is_game_over) {
        return;
    }
    
    auto cs = gameObject->gameManager->controllerState.c[0];
    // Vector2f direction{cs.left ? -speed : 0 + cs.right ? speed : 0, cs.up ? -speed : 0 + cs.down ? speed : 0};
    Vector2f direction{cs.x / 128.0f * speed, -cs.y / 128.0f * speed};
    velocity.moveTowardsWithState(direction, dt * acceleration);
    if (velocity.lengthSquared() < 0.5f)
    {
        velocity = Vector2f{0.0f, 0.0f};
    }

    Vector2f newPosition = transform->localPosition + velocity * dt;

    // Clamp X
    if (newPosition.x < 0)
        newPosition.x = 0;
    if (newPosition.x + collision.x > bounds.x)
        newPosition.x = bounds.x - collision.x;

    // Clamp Y
    if (newPosition.y < 0)
        newPosition.y = 0;
    if (newPosition.y + collision.y > bounds.y)
        newPosition.y = bounds.y - collision.y;

    transform->localPosition = newPosition;
    if(framesActive == 2) {
        rootGameLogic->on_selector_update(0);
    }
    auto grid_pos = get_closest_grid_space(rootGameLogic->main_grid);


    // The goal here is to place the block after you release the A button
    // as well as if you hold it for a while, you can let go but it wont place
    // not sure if this makes sense ultimately, but i think it will prevent
    // accidental placements
    if(was_a_pressed && !cs.A && time_since_a_pressed < 3.0f) {
        // place
        rootGameLogic->place(display_grid, grid_pos);
    }

    if(cs.A) {
        time_since_a_pressed += dt;
    }else {
        time_since_a_pressed = 0;
    }

    if(framesActive > 2) {
        update_preview_grid(&grid_pos, false);
    }
    last_grid_pos = grid_pos;

    was_a_pressed = cs.A;
}

void Cursor::ready()
{
    
}

void Cursor::update_collision() {
    if (!display_grid)
        return;

    collision = display_grid->getBounding();

    hand->localPosition.x = collision.x / 2 - 8;
    hand->localPosition.y = collision.y / 2 - 8;
}

Vector2i Cursor::get_closest_grid_space(BlockGrid* grid) const
{
    if (!grid || !grid->filled_sprite)
        return { -1, -1 };

    const Vector2f cursorGlobal = transform->getGlobalPosition();
    const Vector2f gridGlobal   = grid->transform->getGlobalPosition();
    const int blockSize = grid->filled_sprite->width;

    // Position of the cursor relative to the grid’s origin.
    Vector2f local = (cursorGlobal + (Vector2f{(float)blockSize, (float)blockSize} / 2)) - gridGlobal;

    if (blockSize <= 0)
        return { -1, -1 };

    int col = static_cast<int>(std::floor(local.x / blockSize));
    int row = static_cast<int>(std::floor(local.y / blockSize));

    // Clamp to grid dimensions.
    if (col < 0) col = 0;
    if (row < 0) row = 0;
    if (col >= grid->size.x) col = grid->size.x - 1;
    if (row >= grid->size.y) row = grid->size.y - 1;

    return { col, row };
}

void Cursor::update_preview_grid(Vector2i* pos, bool forceRefresh) {
    Vector2i grid_pos{};
    if(pos) {
        grid_pos = *pos;
    }else {
        grid_pos = get_closest_grid_space(preview_grid);
    }
    
    if(grid_pos.x != last_grid_pos.x || grid_pos.y != last_grid_pos.y || forceRefresh) {
        preview_grid->clear();
        if(rootGameLogic->isValid(display_grid, grid_pos)) {
            for(int x = 0; x < display_grid->size.x; x++) {
                for(int y = 0; y < display_grid->size.y; y++) {
                    if (display_grid->state[x][y] == BlockState::EMPTY)
                    {
                        continue;
                    }
                    preview_grid->setState({x + grid_pos.x, y + grid_pos.y}, display_grid->state[x][y]);
                }
            }
        }
    }
}