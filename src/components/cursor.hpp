#pragma once
#include "../gameobject.hpp"
#include "transform.hpp"
#include "block_grid.hpp"



COMPONENT(Cursor)
    static Cursor* instance;
    BlockGrid* display_grid;
    float speed = 300.0f;
    float acceleration = 2000.0f;
    Vector2f bounds;
    Vector2i collision;
    Transform* transform;
    Vector2f velocity{0,0};
    void ready() override;
    void update(float dt) override;
    void update_collision();
    ~Cursor() {}
COMPONENT_END()