/**
 * @file selector.cpp
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

#include "selector.hpp"
#include "game_logic.hpp"

void Selector::ready()
{
    transform = gameObject->GET_COMPONENT(Transform);
    wav64_open(&select_sound, "rom:/audio/selector_change.wav64");
}

void Selector::update(float dt)
{
    Component::update(dt);
    auto controller = gameObject->gameManager->controllerState.c;
    if(controller->C_up) {
        if(select(0)) {
            mixer_ch_stop(1);
            wav64_play(&select_sound, 1);
        }
    }
    if(controller->C_left) {
        if(select(1)) {
            mixer_ch_stop(1);
            wav64_play(&select_sound, 1);
        }
    }
    if(controller->C_down) {
        if(select(2)) {
            mixer_ch_stop(1);
            wav64_play(&select_sound, 1);
        }
    }
    if(controller->C_right && !c_right_pressed) {
        c_right_pressed = true;
        if(select(last_selected)) {
            mixer_ch_stop(1);
            wav64_play(&select_sound, 1);
        }
    }

    if(!controller->C_right) {
        c_right_pressed = false;
    }
}

bool Selector::select(int i)
{
    if(i == selected) {
        return false;
    }
    if(!rootGameLogic->previews[i]->visible) {
        return false;
    }
    switch(i) {
        case(0): transform->localPosition.y = 41 ; break;
        case(1): transform->localPosition.y = 107; break;
        case(2): transform->localPosition.y = 173; break;
    }
    
    last_selected = selected;
    selected = i;
    rootGameLogic->on_selector_update(selected);
    return true;
}
