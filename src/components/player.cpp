#include "player.hpp"

void Player::update(float dt)
{
    Component::update(dt);
    auto cs = gameObject->gameManager->controllerState.c[0];
    Vector2f direction{cs.x * speed, -cs.y * speed};
    // velocity.x = clamp(velocity.x, -100.0f, 100.0f);
    // velocity.y = clamp(velocity.y, -100.0f, 100.0f);
    velocity = velocity.moveTowards(direction, dt * acceleration);
    if (velocity.lengthSquared() < 0.5f)
    {
        velocity = Vector2f{0.0f, 0.0f};
    }

    transform->localPosition.x += velocity.x * dt;
    transform->localPosition.y += velocity.y * dt;
    char text[100];
    sprintf(text, "Controller %d, %d. \nVelocity: %f, %f", cs.x, cs.y, velocity.x, velocity.y);
    graphics_draw_text(gameObject->gameManager->display,  0, 0, text);
}

void Player::ready()
{
    Component::ready();
    // gameObject->gameManager->camera_pos = Vector2f{320, 420};
    transform = gameObject->GET_COMPONENT(Transform);
}
