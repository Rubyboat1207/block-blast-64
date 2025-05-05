#include "block_grid.hpp"

void BlockGrid::ready()
{
    state = new BlockState*[size.x];

    for(int i = 0; i < size.x; i++) {
        state[i] = new BlockState[size.y];
    }

    empty_sprite = sprite_load("rom:/rubyboat.sprite");
}

void BlockGrid::render() {
    for(int x = 0; x < size.x; x++) {
        for(int y = 0; y < size.y; y++) {
            
        }
    }
}