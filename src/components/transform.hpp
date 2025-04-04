#pragma once
#include "../gameobject.hpp"
#include "../math.hpp"

COMPONENT(Transform)
    // switch to a vector3 at some point if needed
    Vector2f localPosition;
    float rotation;

    Vector2f getGlobalPosition();
    ~Transform() {}
};