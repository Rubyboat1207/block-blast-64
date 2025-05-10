/**
 * @file game_logic.hpp
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 * 
 * Copyright (C) 2025 Rubyboat (owner of https://github.com/Rubyboat1207)
 */

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
#include "timer_manager.hpp"

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


struct GameLogic : public GameObjects::Component, TimerUser {
    uint32_t getType() override {
        return GameObjects::typeIdHasher("GameLogic");
    }

    // Game Over
    bool is_game_over = false;
    SpriteRenderer* lose_screen;
    void onGameOver();

    // Reset Animation
    bool can_reset = false;
    TimerManager* timer_manager;
    void on_timeout() override;
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
};

extern GameLogic* rootGameLogic;