#pragma once
#include "../gameobject.hpp"
#include "transform.hpp"
#include "sprite_renderer.hpp"
#include "block_grid.hpp"
#include "selector.hpp"
#include "text_renderer.hpp"
#include "cursor.hpp"
#include <utility>
#include <map>
#include <array>

enum class PieceType {
    BIG_L,
    LITTLE_L,
    SQUARE,
    LINE,
    SINGLE,
    DIAGONAL,
    BIG_SQUARE,
    DUO,
    T_BLOCK,
    SIX_BLOCK,




    // do not add anything after this
    Last,
};


COMPONENT(GameLogic)
    bool is_game_over;
    BlockGrid* previews[3];
    BlockGrid* main_grid;
    Selector* selector;
    Cursor* cursor;
    Vector2f velocity{0,0};
    SpriteRenderer* lose_screen;
    TextRenderer* points_renderer;
    TextRenderer* high_score_renderer;
    uint32_t points = 0;
    uint32_t high_score = 0;
    uint8_t* save_buffer_1 = nullptr;
    int lines_scored_last = 0;
    int piece = 0;
    void ready() override;
    void update(float dt) override;
    void set_preview(int index);
    std::pair< int, Vector2i* > get_next_piece();
    std::map<PieceType, int> pieces_since{};
    void on_selector_update(int selectedIndex);
    void refresh_pieces(bool reselect);
    void place(BlockGrid* grid, Vector2i grid_position);
    bool isValid(BlockGrid* grid, Vector2i grid_position);
    void onGameOver();
    void set_high_score(uint32_t hs);
    void set_score(uint32_t score);
    ~GameLogic() {}
    GameLogic();
COMPONENT_END()

extern GameLogic* rootGameLogic;