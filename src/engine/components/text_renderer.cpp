/**
 * @file text_renderer.cpp
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
#include "text_renderer.hpp"

void TextRenderer::ready() {
    Component::ready();
    if(gameObject == nullptr) {
        return;
    }
    transform = gameObject->GET_COMPONENT(Transform);
}

void TextRenderer::render() {
    auto position = transform->getGlobalPosition();
    rdpq_set_mode_standard();
    rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
    rdpq_set_prim_color(RGBA32(255,255,255,255));
    rdpq_text_print(NULL, 1, position.x, position.y, text.c_str());
}