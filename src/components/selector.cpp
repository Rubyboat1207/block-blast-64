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
    
    selected = i;
    rootGameLogic->on_selector_update(selected);
    return true;
}
