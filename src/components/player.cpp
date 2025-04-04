#include "player.hpp"

void Player::update(float dt)
{
    Component::update(dt);
    auto cs = gameObject->gameManager->controllerState.c[0];
    Vector2f direction{cs.left ? -speed : 0 + cs.right ? speed : 0, cs.up ? -speed : 0 + cs.down ? speed : 0};
    velocity.moveTowardsWithState(direction, dt * acceleration);
    if (velocity.lengthSquared() < 0.5f)
    {
        velocity = Vector2f{0.0f, 0.0f};
    }

    transform->localPosition.x += velocity.x * dt;
    transform->localPosition.y += velocity.y * dt;
}

void Player::ready()
{
    Component::ready();
    transform = gameObject->GET_COMPONENT(Transform);
}
