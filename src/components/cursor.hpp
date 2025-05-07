#pragma once
#include "../gameobject.hpp"
#include "transform.hpp"
#include "block_grid.hpp"
#include "sprite_renderer.hpp"



COMPONENT(Cursor)
    BlockGrid* display_grid;
    BlockGrid* preview_grid;
    Vector2i last_grid_pos{};
    float speed = 300.0f;
    float acceleration = 1500.0f;
    Vector2f bounds;
    Vector2i collision;
    Transform* transform;
    Transform* hand;
    Vector2f velocity{0,0};
    bool was_a_pressed;
    void ready() override;
    void update(float dt) override;
    void update_collision();
    Vector2i get_closest_grid_space(BlockGrid* grid) const;
    SpriteRenderer* handRenderer;
    void update_preview_grid(Vector2i* pos);
    ~Cursor() {}
COMPONENT_END()