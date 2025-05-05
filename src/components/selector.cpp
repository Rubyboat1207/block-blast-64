#include "selector.hpp"

void Selector::ready()
{
    transform = gameObject->GET_COMPONENT(Transform);
}

void Selector::update(float dt)
{
    Component::update(dt);
    auto controller = gameObject->gameManager->controllerState.c;
    if(controller->C_up) {
        selected = 0;
        transform->localPosition.y = 41;
    }
    if(controller->C_left) {
        selected = 1;
        transform->localPosition.y = 107;
    }
    if(controller->C_down) {
        selected = 2;
        transform->localPosition.y = 173;
    }
}