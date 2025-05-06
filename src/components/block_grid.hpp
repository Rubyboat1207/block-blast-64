#pragma once
#include "../gameobject.hpp"
#include "transform.hpp"

enum class BlockState {
    EMPTY,
    RED,
    PURPLE,
    BLUE,
    YELLOW,
};


COMPONENT(BlockGrid)
    bool visible = true;
    Vector2i size;
    Transform* transform;
    BlockState** state;
    sprite_t* empty_sprite;
    sprite_t* filled_sprite;
    Vector2i getBounding();
    void ready() override;
    void render() override;
    ~BlockGrid() {}
    void setState(Vector2i pos, BlockState block_state);
    void clear();
COMPONENT_END()