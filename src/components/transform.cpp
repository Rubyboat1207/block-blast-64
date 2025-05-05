#include "transform.hpp"

Vector2f Transform::getGlobalPosition()
{
    Vector2f gp{localPosition.x, localPosition.y};

    GameObjects::GameObject* current_parent = gameObject->parent;

    // to avoid recursion, because it sucks
    for(int max_depth = 0; max_depth < 128; max_depth++) {
        if(current_parent == nullptr) {
            return gp;
        }
        Transform* transform = current_parent->GET_COMPONENT(Transform);
        if(transform == nullptr) {
            return gp;
        }
        
        gp += transform->localPosition;
        current_parent = current_parent->parent;
    }

    return gp;
}

Transform::Transform()
{
    this->localPosition = {0,0};
    this->rotation = 0;
}
