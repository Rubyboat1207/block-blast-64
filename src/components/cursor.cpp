#include "cursor.hpp"

void Cursor::update(float dt) {
    Component::update(dt);
    
    auto cs = gameObject->gameManager->controllerState.c[0];
    Vector2f direction{cs.left ? -speed : 0 + cs.right ? speed : 0, cs.up ? -speed : 0 + cs.down ? speed : 0};
    velocity.moveTowardsWithState(direction, dt * acceleration);
    if (velocity.lengthSquared() < 0.5f)
    {
        velocity = Vector2f{0.0f, 0.0f};
    }

    Vector2f newPosition = transform->localPosition + velocity * dt;

    // Clamp X
    if (newPosition.x < 0)
        newPosition.x = 0;
    if (newPosition.x + collision.x > bounds.x)
        newPosition.x = bounds.x - collision.x;

    // Clamp Y
    if (newPosition.y < 0)
        newPosition.y = 0;
    if (newPosition.y + collision.y > bounds.y)
        newPosition.y = bounds.y - collision.y;

    transform->localPosition = newPosition;
}

void Cursor::ready()
{
    display_grid->setState({0,0}, BlockState::RED);
    display_grid->setState({0,1}, BlockState::RED);
    display_grid->setState({1,0}, BlockState::RED);
    display_grid->setState({1,1}, BlockState::RED);
    display_grid->setState({2,1}, BlockState::RED);

    update_collision();
}

void Cursor::update_collision() {
    if (!display_grid || !display_grid->state || !display_grid->filled_sprite)
        return;

    int blockSize = display_grid->filled_sprite->width;

    Vector2i minPos{display_grid->size.x, display_grid->size.y};
    Vector2i maxPos{0, 0};
    bool found = false;

    for (int y = 0; y < display_grid->size.y; ++y) {
        for (int x = 0; x < display_grid->size.x; ++x) {
            if (display_grid->state[x][y] != BlockState::EMPTY) {
                if (!found) {
                    minPos = { x, y };
                    maxPos = { x, y };
                    found = true;
                } else {
                    if (x < minPos.x) minPos.x = x;
                    if (y < minPos.y) minPos.y = y;
                    if (x > maxPos.x) maxPos.x = x;
                    if (y > maxPos.y) maxPos.y = y;
                }
            }
        }
    }

    if (found) {
        collision.x = (maxPos.x - minPos.x + 1) * blockSize;
        collision.y = (maxPos.y - minPos.y + 1) * blockSize;
    } else {
        collision.x = 0;
        collision.y = 0;
    }
}

