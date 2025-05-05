#include "../gameobject.hpp"

enum class BlockState {
    EMPTY,
    RED,
    PURPLE,
    BLUE,
    YELLOW,
};


COMPONENT(BlockGrid)
    Vector2i size;
    BlockState** state;
    BlockState** visualState;
    sprite_t* empty_sprite;
    sprite_t* filled_sprite;
    void ready() override;
    void render();
    ~BlockGrid() {}
    void setVisualState();
    void cleanVisualState();
    void setState();
COMPONENT_END()