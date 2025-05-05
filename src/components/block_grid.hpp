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
    Vector2i size;
    Transform* transform;
    BlockState** state;
    BlockState** visualState;
    sprite_t* empty_sprite;
    sprite_t* filled_sprite;
    void ready() override;
    void render() override;
    ~BlockGrid() {}
    void setVisualState(Vector2i pos, BlockState state);
    void cleanVisualState();
    void setState(Vector2i pos, BlockState state);
COMPONENT_END()