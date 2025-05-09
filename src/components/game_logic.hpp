#pragma once
#include "../gameobject.hpp"
#include "transform.hpp"
#include "sprite_renderer.hpp"
#include "block_grid.hpp"
#include "selector.hpp"
#include "text_renderer.hpp"
#include "clear_anim_manager.hpp"
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
    INVERTED_L,
    BIG_U,




    // do not add anything after this
    Last,
};


COMPONENT(GameLogic)
    // Game Over
    bool is_game_over = false;
    SpriteRenderer* lose_screen;
    void onGameOver();

    // Reset Animation
    bool can_reset = false;
    timer_link_t* reset_timer;
    void reset_timer_timeout();
    int reset_progress = 0;

    // Scores
    TextRenderer* points_renderer;
    TextRenderer* high_score_renderer;
    uint32_t points = 0;
    void set_high_score(uint32_t hs);
    void set_score(uint32_t score);
    int lines_scored_last = 0;
    ClearAnimationManager* clear_anim_manager;
    wav64_t clear_sound;


    // Selectables
    BlockGrid* previews[3];
    Selector* selector;
    void refresh_pieces(bool reselect);
    void on_selector_update(int selectedIndex);
    void set_preview(int index);
    std::pair< int, Vector2i* > get_next_piece();
    std::map<PieceType, int> pieces_since{};


    // Cursor/Grid
    Cursor* cursor;
    BlockGrid* main_grid;
    wav64_t place_sound;
    void place(BlockGrid* grid, Vector2i grid_position);
    bool isValid(BlockGrid* grid, Vector2i grid_position);
    
    void ready() override;
    void update(float dt) override;

    ~GameLogic() {}
    GameLogic();
COMPONENT_END()

extern GameLogic* rootGameLogic;