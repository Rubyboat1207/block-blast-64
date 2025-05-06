#pragma once
#include "../gameobject.hpp"
#include "transform.hpp"
#include "block_grid.hpp"
#include "selector.hpp"
#include "cursor.hpp"
#include <utility>



COMPONENT(GameLogic)
    BlockGrid* previews[3];
    BlockGrid* main_grid;
    Selector* selector;
    Cursor* cursor;
    Vector2f velocity{0,0};
    int piece = 0;
    void ready() override;
    void update(float dt) override;
    void set_preview(int index);
    std::pair< int, Vector2i* > get_next_piece();
    void on_selector_update(int selectedIndex);
    void refresh_pieces(bool reselect);
    void place(BlockGrid* grid, Vector2i grid_position);
    ~GameLogic() {}
    GameLogic();
COMPONENT_END()

extern GameLogic* rootGameLogic;