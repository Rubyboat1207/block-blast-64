/**
 * @file text_renderer.hpp
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
#include <string>

COMPONENT(TextRenderer)
    Transform* transform;
    std::string text = "";
    int selected = 0;
    void ready() override;
    void render();
    ~TextRenderer() {}
COMPONENT_END()