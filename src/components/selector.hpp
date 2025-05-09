#pragma once
#include "../gameobject.hpp"
#include "transform.hpp"

COMPONENT(Selector)
    Transform* transform;
    wav64_t select_sound;

    int selected = 0;
    void ready() override;
    void update(float dt);
    ~Selector() {}
    bool select(int i);
COMPONENT_END()