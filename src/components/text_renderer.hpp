#pragma once
#include "../gameobject.hpp"
#include "transform.hpp"
#include <string>

COMPONENT(TextRenderer)
    Transform* transform;
    std::string text = "";
    int selected = 0;
    void ready() override;
    void render();
    ~TextRenderer() {}
COMPONENT_END()