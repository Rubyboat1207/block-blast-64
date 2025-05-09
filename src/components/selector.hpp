#pragma once
#include "../gameobject.hpp"
#include "transform.hpp"

COMPONENT(Selector)
    Transform* transform;
    wav64_t select_sound;
    uint8_t last_selected = 0;
    bool c_right_pressed = false;

    int selected = 0;
    void ready() override;
    void update(float dt);
    ~Selector() {}
    bool select(int i);
COMPONENT_END()