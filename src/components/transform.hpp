/**
 * @file transform.hpp
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
#include "../math.hpp"

COMPONENT(Transform)

    // switch to a vector3 at some point if needed
    Vector2f localPosition;
    float rotation;

    Vector2f getGlobalPosition();
    ~Transform() {}
    Transform();
    
COMPONENT_END()