#include "block_grid.hpp"

void BlockGrid::ready()
{
    state = new BlockState*[size.x];

    for(int i = 0; i < size.x; i++) {
        state[i] = new BlockState[size.y];
    }

    for(int x = 0; x < size.x; x++) {
        for(int y = 0; y < size.y; y++) {
            state[x][y] = BlockState::EMPTY;
        }
    }
}

void BlockGrid::render() {
    auto offset = transform->getGlobalPosition();
    for(int x = 0; x < size.x; x++) {
        for(int y = 0; y < size.y; y++) {
            auto b_state = state[x][y];

            if(empty_sprite == nullptr && b_state == BlockState::EMPTY) {
                continue;
            }

            auto position = offset + Vector2f{(float) x * filled_sprite->width, (float) y * filled_sprite->height};

            sprite_t* sprite = filled_sprite;

            rdpq_set_mode_standard();
            rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);

            switch (b_state) {
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

void BlockGrid::setState(Vector2i pos, BlockState block_state)
{
    state[pos.x][pos.y] = block_state;
}
