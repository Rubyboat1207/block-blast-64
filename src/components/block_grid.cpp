#include "block_grid.hpp"

void BlockGrid::ready()
{
    state = new BlockState*[size.x];
    visualState = new BlockState*[size.x];

    for(int i = 0; i < size.x; i++) {
        state[i] = new BlockState[size.y];
        visualState[i] = new BlockState[size.y];
    }

    for(int x = 0; x < size.x; x++) {
        for(int y = 0; y < size.y; y++) {
            state[x][y] = BlockState::EMPTY;
            visualState[x][y] = BlockState::EMPTY;
        }
    }



    empty_sprite = sprite_load("rom:/block_empty.sprite");
    filled_sprite = sprite_load("rom:/block_normal.sprite");

    setVisualState({0,0}, BlockState::RED);
    setVisualState({1,0}, BlockState::BLUE);
    setVisualState({2,0}, BlockState::YELLOW);
    setVisualState({3,0}, BlockState::PURPLE);
}

void BlockGrid::render() {
    auto offset = transform->getGlobalPosition();
    for(int x = 0; x < size.x; x++) {
        for(int y = 0; y < size.y; y++) {
            auto state = visualState[x][y];

            auto position = offset + Vector2f{(float) x * empty_sprite->width, (float) y * empty_sprite->height};

            sprite_t* sprite = filled_sprite;

            rdpq_set_mode_standard();
            rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);

            switch (state) {
                case(BlockState::EMPTY): {
                    sprite = empty_sprite;
                    rdpq_set_prim_color(RGBA32(255,255,255,255));
                }break;
                case(BlockState::BLUE): rdpq_set_prim_color(RGBA32(32, 134, 230,255)); break;
                case(BlockState::PURPLE): rdpq_set_prim_color(RGBA32(143, 74, 212,255)); break;
                case(BlockState::RED): rdpq_set_prim_color(RGBA32(255, 94, 94,255)); break;
                case(BlockState::YELLOW): rdpq_set_prim_color(RGBA32(252, 223, 3,255)); break;
            }

            rdpq_sprite_blit(sprite, position.x, position.y, NULL);
        }
    }
}

void BlockGrid::setVisualState(Vector2i pos, BlockState state)
{
    visualState[pos.x][pos.y] = state;
}
