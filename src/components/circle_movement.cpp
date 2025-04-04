#include "circle_movement.hpp"
#include <libdragon.h>

void CircleMovement::ready() {
    Component::ready();
    transform = gameObject->GET_COMPONENT(Transform);
}


void CircleMovement::update(float dt)
{
    Component::update(dt);
    // Vector2f sincos = sincosFOURTHORDER(transform->rotation);

    transform->localPosition.x = center.x + cos(transform->rotation) * radius;
    transform->localPosition.y = center.y + sin(transform->rotation) * radius;
    transform->rotation += dt * 5;
}