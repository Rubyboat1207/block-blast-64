#pragma once
#include "../gameobject.hpp"
#include "transform.hpp"

COMPONENT(Selector)
    Transform* transform;
    int selected = 0;
    void ready() override;
    void update(float dt);
    ~Selector() {}
    void select(int i);
COMPONENT_END()