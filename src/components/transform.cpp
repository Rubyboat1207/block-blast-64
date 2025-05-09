/**
 * @file transform.cpp
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

#include "transform.hpp"

Vector2f Transform::getGlobalPosition()
{
    Vector2f gp{localPosition.x, localPosition.y};

    GameObjects::GameObject* current_parent = gameObject->parent;

    // to avoid recursion, because it sucks
    for(int max_depth = 0; max_depth < 128; max_depth++) {
        if(current_parent == nullptr) {
            return gp;
        }
        Transform* transform = current_parent->GET_COMPONENT(Transform);
        if(transform == nullptr) {
            return gp;
        }
        
        gp += transform->localPosition;
        current_parent = current_parent->parent;
    }

    return gp;
}

Transform::Transform()
{
    this->localPosition = {0,0};
    this->rotation = 0;
}
