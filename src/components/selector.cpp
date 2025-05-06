#include "selector.hpp"
#include "game_logic.hpp"

void Selector::ready()
{
    transform = gameObject->GET_COMPONENT(Transform);
}

void Selector::update(float dt)
{
    Component::update(dt);
    auto controller = gameObject->gameManager->controllerState.c;
    if(controller->C_up) {
        select(0);
    }
    if(controller->C_left) {
        select(1);
    }
    if(controller->C_down) {
        select(2);
    }
}

void Selector::select(int i)
{
    if(i == selected) {
        return;
    }
    if(!rootGameLogic->previews[i]->visible) {
        return;
    }
    switch(i) {
        case(0): transform->localPosition.y = 41 ; break;
        case(1): transform->localPosition.y = 107; break;
        case(2): transform->localPosition.y = 173; break;
    }
    
    selected = i;
    rootGameLogic->on_selector_update(selected);
}
