#include "game_logic.hpp"
#include <cstdlib>
#include <ctime>
#include <climits>
#include <vector>
#include <string>
#include "../save_manager.hpp"

GameLogic *rootGameLogic = nullptr;

void GameLogic::ready()
{
    wav64_open(&clear_sound, "rom:/audio/cleared_sound.wav64");
    wav64_open(&place_sound, "rom:/audio/place_blocks.wav64");

    high_score_renderer->text = std::to_string(save_manager->high_score);
}

void GameLogic::update(float dt)
{
    Component::update(dt);
    if (framesActive == 2)
    {
        refresh_pieces(false);
    }

    if (is_game_over && can_reset)
    {
        if (gameObject->gameManager->controllerState.c->start)
        {
            main_grid->clear();
            refresh_pieces(false);
            lose_screen->visible = false;
            is_game_over = false;
            set_score(0);
            cursor->display_grid->visible = true;
            cursor->preview_grid->visible = true;
            cursor->handRenderer->visible = true;
            main_grid->alpha = 255;
        }
    }
}

void GameLogic::refresh_pieces(bool reselect)
{
    for (int i = 0; i < 3; i++)
    {
        set_preview(i);
    }

    on_selector_update(selector->selected);
}

GameLogic::GameLogic()
{
    rootGameLogic = this;
}

static Vector2i BIG_L[]{
    {0, 0},
    {0, 1},
    {0, 2},
    {1, 2}};
static Vector2i LITTLE_L[]{
    {0, 0},
    {0, 1},
    {1, 1}};
static Vector2i SQUARE[]{
    {0, 0},
    {0, 1},
    {1, 0},
    {1, 1}};
static Vector2i LINE[]{
    {0, 0},
    {1, 0},
    {2, 0}};
static Vector2i SINGLE[]{
    {0, 0}};
static Vector2i DIAGONAL[]{
    {0, 0},
    {1, 1},
};
static Vector2i BIG_SQUARE[]{
    {0, 0},
    {1, 0},
    {2, 0},
    {0, 1},
    {1, 1},
    {2, 1},
    {0, 2},
    {1, 2},
    {2, 2},
};
static Vector2i DUO[]{
    {0, 0},
    {0, 1},
};
static Vector2i T_BLOCK[]{
    {0, 0},
    {1, 0},
    {2, 0},
    {1, 1},
};
static Vector2i SIX_BLOCK[]{
    {0, 0},
    {1, 0},
    {2, 0},
    {0, 1},
    {1, 1},
    {2, 1},
};
static Vector2i INVERTED_L[]{
    {1, 0},
    {1, 1},
    {1, 2},
    {0, 2},
};
static Vector2i BIG_U[]{
    {0, 0},
    {2, 0},
    {0, 1},
    {2, 1},
    {0, 2},
    {1, 2},
    {2, 2}
};

// ────────────────────────────────────────────────────────────────────────────────
// Helper: rotate an array of Vector2i “count” cells by 0–3 quarter‑turns.
static void rotate_piece(const Vector2i *src, int count, Vector2i *dst, int rotations)
{
    for (int i = 0; i < count; ++i)
    {
        Vector2i p = src[i];
        for (int r = 0; r < rotations; ++r)
            p = {-p.y, p.x};
        dst[i] = p;
    }

    int minX = INT_MAX, minY = INT_MAX;
    for (int i = 0; i < count; ++i)
    {
        if (dst[i].x < minX)
            minX = dst[i].x;
        if (dst[i].y < minY)
            minY = dst[i].y;
    }
    for (int i = 0; i < count; ++i)
    {
        dst[i].x -= minX;
        dst[i].y -= minY;
    }
}

#define PIECE_CASE(p, size) \
    case (PieceType::p):    \
        base = p;           \
        count = size;       \
        break;

#define ADD_PIECE(p) allowed_types[allowed_count++] = p;
#define ADD_PIECE_AFTER_COUNT(p, count) \
    if (pieces_since[p] > count)        \
    {                                   \
        ADD_PIECE(p)                    \
    }
#define ADD_PIECE_UNIQUE_TO_SET(p) ADD_PIECE_AFTER_COUNT(p, 3)
#define ADD_PIECE_AFTER_COUNT_4(p, count, other_p, other_count)         \
    if (pieces_since[p] > count &&                                      \
        (pieces_since[other_p] > other_count))         \
    {                                                                   \
        ADD_PIECE(p)                                                    \
    }
#define ADD_PIECE_AFTER_COUNT_6(p, count, other_p, other_count, third_p, third_count) \
    if (pieces_since[p] > count &&                                                   \
        (pieces_since[other_p] > other_count) &&                    \
        (pieces_since[third_p] > third_count))                      \
    {                                                                                \
        ADD_PIECE(p)                                                                 \
    }



std::pair<int, Vector2i *> GameLogic::get_next_piece()
{
    static Vector2i rotated[9]; // largest piece size is 9 cells
    const Vector2i *base = nullptr;
    std::array<PieceType, static_cast<int>(PieceType::Last)> allowed_types{};
    int allowed_count = 0;

    ADD_PIECE_UNIQUE_TO_SET(PieceType::BIG_L)
    ADD_PIECE_UNIQUE_TO_SET(PieceType::INVERTED_L)
    ADD_PIECE_AFTER_COUNT_4(PieceType::BIG_SQUARE, 6, PieceType::BIG_U, 3)
    ADD_PIECE(PieceType::DIAGONAL)
    ADD_PIECE_AFTER_COUNT(PieceType::DUO, 1)
    ADD_PIECE(PieceType::LINE)
    ADD_PIECE_AFTER_COUNT(PieceType::LITTLE_L, 2)
    ADD_PIECE_AFTER_COUNT(PieceType::SINGLE, 4)
    ADD_PIECE(PieceType::SQUARE)
    ADD_PIECE_AFTER_COUNT(PieceType::T_BLOCK, 2)
    ADD_PIECE_AFTER_COUNT(PieceType::SIX_BLOCK, 4)
    ADD_PIECE_AFTER_COUNT_4(PieceType::BIG_U, 5, PieceType::BIG_SQUARE, 3)


    PieceType piece_type = allowed_types[(random_u32() + framesActive + (uint8_t) display_get_fps()) % allowed_count];
    int count = 0;

    switch (piece_type)
    {
        PIECE_CASE(BIG_L, 4)
        PIECE_CASE(LITTLE_L, 3)
        PIECE_CASE(SQUARE, 4)
        PIECE_CASE(LINE, 3)
        PIECE_CASE(SINGLE, 1)
        PIECE_CASE(DIAGONAL, 2)
        PIECE_CASE(BIG_SQUARE, 9)
        PIECE_CASE(DUO, 2)
        PIECE_CASE(T_BLOCK, 4)
        PIECE_CASE(SIX_BLOCK, 6)
        PIECE_CASE(INVERTED_L, 4)
        PIECE_CASE(BIG_U, 7)
    default:
        assert(false);
    }

    for (int i = 0; i < (int)PieceType::Last; i++)
    {
        pieces_since[(PieceType)i]++;
    }
    pieces_since[piece_type] = 0;

    int rotations = random_u32() & 3; // 0,1,2,3 quarter‑turns
    rotate_piece(base, count, rotated, rotations);

    return {count, rotated};
}

void GameLogic::set_preview(int index)
{
    previews[index]->clear();
    BlockState state = BlockState::EMPTY;
    switch ((framesActive + index) % 6)
    {
    case (0):
        state = BlockState::BLUE;
        break;
    case (1):
        state = BlockState::RED;
        break;
    case (2):
        state = BlockState::PURPLE;
        break;
    case (3):
        state = BlockState::ORANGE;
        break;
    case (4):
        state = BlockState::GREEN;
        break;
    case (5):
        state = BlockState::YELLOW;
        break;
    }

    auto piece = get_next_piece();
    for (int j = 0; j < piece.first; j++)
    {
        previews[index]->setState(piece.second[j], state);
    }
    previews[index]->visible = true;
    auto bounds = previews[index]->getBounding();

    previews[index]->transform->localPosition.x = 58 / 2 - bounds.x / 2;
    previews[index]->transform->localPosition.y = 58 / 2 - bounds.y / 2;
}

void GameLogic::on_selector_update(int selectedIndex)
{
    cursor->preview_grid->clear();
    for (int x = 0; x < previews[selectedIndex]->size.x; x++)
    {
        for (int y = 0; y < previews[selectedIndex]->size.y; y++)
        {
            cursor->display_grid->setState({x, y}, previews[selectedIndex]->state[x][y]);
        }
    }
    cursor->update_collision();
    cursor->update_preview_grid(nullptr, true);
}

void GameLogic::place(BlockGrid *grid, Vector2i grid_position)
{
    if(!isValid(grid, grid_position)) {
        return;
    }
    int total_added_points = 0;

    // -- Actually Place the blocks -- //
    for (int x = 0; x < grid->size.x; x++)
    {
        for (int y = 0; y < grid->size.y; y++)
        {
            if (grid->state[x][y] == BlockState::EMPTY)
            {
                continue;
            }

            int final_x = x + grid_position.x;
            int final_y = y + grid_position.y;

            main_grid->state[final_x][final_y] = grid->state[x][y];
            total_added_points += 10;
        }
    }

    // -- Detect & Clear any needed columns & rows -- //
    std::vector<int> columns_to_clear;
    std::vector<int> rows_to_clear;

    // 1. Detect full columns
    for (int x = 0; x < main_grid->size.x; ++x)
    {
        bool col_full = true;
        for (int y = 0; y < main_grid->size.y; ++y)
        {
            if (main_grid->state[x][y] == BlockState::EMPTY)
            {
                col_full = false;
                break;
            }
        }
        if (col_full)
            columns_to_clear.push_back(x);
    }

    for (int y = 0; y < main_grid->size.y; ++y)
    {
        bool row_full = true;
        for (int x = 0; x < main_grid->size.x; ++x)
        {
            if (main_grid->state[x][y] == BlockState::EMPTY)
            {
                row_full = false;
                break;
            }
        }
        if (row_full)
            rows_to_clear.push_back(y);
    }

    for (int x : columns_to_clear)
    {
        for (int y = 0; y < main_grid->size.y; ++y) {
            if(main_grid->state[x][y] == BlockState::EMPTY) {
                total_added_points += 50;
            }
            main_grid->state[x][y] = BlockState::EMPTY;
        }
    }

    for (int y : rows_to_clear)
    {
        for (int x = 0; x < main_grid->size.x; ++x)
            main_grid->state[x][y] = BlockState::EMPTY;
    }

    size_t lines_scored = rows_to_clear.size() + columns_to_clear.size();

    if(lines_scored > 0) {
        size_t v_anims = 0;
        size_t h_anims = 0;
        for(int i = 0; i < CLEAR_ANIM_MAX_COUNT_ACTIVE; i++) {
            if(clear_anim_manager->clear_animations[i] != nullptr) {
                continue;
            }

            if(h_anims < rows_to_clear.size()) {
                clear_anim_manager->clear_animations[i] = new ClearAnimation(rows_to_clear[h_anims], false);
                h_anims++;
                continue;
            }
            if(v_anims < columns_to_clear.size()) {
                clear_anim_manager->clear_animations[i] = new ClearAnimation(columns_to_clear[v_anims], true);
                v_anims++;
                continue;
            }
            if(v_anims + h_anims == lines_scored) {
                break;
            }
        }
        mixer_ch_stop(0);
        wav64_play(&clear_sound, 0);
    }

    mixer_ch_stop(2);
    wav64_play(&place_sound, 2);
    

    if(lines_scored > 0) {
        total_added_points += pow(2, lines_scored) * 25;
    }

    if(columns_to_clear.size() > 0 || rows_to_clear.size() > 0) {
        total_added_points += lines_scored_last + lines_scored * 15;
    }
    lines_scored_last = lines_scored;

    // -- Maybe a losing Condition -- //
    previews[selector->selected]->visible = false;
    int avaliable_previews = 0;
    for (int i = 0; i < 3; i++)
    {
        if (previews[i]->visible)
        {
            avaliable_previews++;
        }
    }

    // -- Select a new preview -- //

    if (avaliable_previews == 0)
    {
        refresh_pieces(true);
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            if (previews[i]->visible)
            {
                selector->select(i);
            }
        }
    }

    bool can_place_any = false;
    for (int i = 0; i < 3; i++)
    {
        if (!previews[i]->visible)
            continue;

        for (int x = 0; x < main_grid->size.x; x++)
        {
            for (int y = 0; y < main_grid->size.y; y++)
            {
                if (isValid(previews[i], {x, y}))
                {
                    can_place_any = true;
                    break;
                }
            }
            if (can_place_any)
                break;
        }
        if (can_place_any)
            break;
    }

    set_score(total_added_points + points);

    if (!can_place_any)
    {
        // Trigger losing condition
        onGameOver();
        return;
    }
}

bool GameLogic::isValid(BlockGrid *grid, Vector2i grid_position)
{
    for (int x = 0; x < grid->size.x; x++)
    {
        for (int y = 0; y < grid->size.y; y++)
        {
            if (grid->state[x][y] == BlockState::EMPTY)
            {
                continue;
            }

            int final_x = x + grid_position.x;
            if (final_x < 0 || final_x >= main_grid->size.x)
            {
                return false;
            }
            int final_y = y + grid_position.y;
            if (final_y < 0 || final_y >= main_grid->size.y)
            {
                return false;
            }

            if (main_grid->state[final_x][final_y] != BlockState::EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}

void timer_timeout(int ovfl) {
    rootGameLogic->reset_timer_timeout();
}

void GameLogic::onGameOver()
{
    // lose_screen->visible = true;
    can_reset = false;
    is_game_over = true;

    cursor->transform->localPosition = {192/2, 192/2};

    if(points > save_manager->high_score) {
        set_high_score(points);
    }else {
        // update rng state
        save_manager->save();
    }
    cursor->display_grid->visible = false;
    cursor->preview_grid->visible = false;
    cursor->handRenderer->visible = false;


    reset_progress = 0;
    reset_timer = new_timer(TIMER_TICKS(250 * 1000), TF_CONTINUOUS, timer_timeout);
}

void GameLogic::set_high_score(uint32_t hs)
{
    save_manager->high_score = hs;
    save_manager->save();

    high_score_renderer->text = std::to_string(hs);
}

void GameLogic::set_score(uint32_t score) {
    points = score;

    points_renderer->text = std::to_string(score);
}

void GameLogic::reset_timer_timeout()
{
    if(reset_progress % 2 == 0) {
        mixer_ch_stop(2);
        wav64_play(&place_sound, 2);
    }
    
    for(int x = 0; x < main_grid->size.x; x++) {
        if(main_grid->state[x][reset_progress] == BlockState::EMPTY) {
            switch(random_u32() % 6) {
                case(0): main_grid->state[x][reset_progress] = BlockState::BLUE; break;
                case(1): main_grid->state[x][reset_progress] = BlockState::PURPLE; break;
                case(2): main_grid->state[x][reset_progress] = BlockState::RED; break;
                case(3): main_grid->state[x][reset_progress] = BlockState::YELLOW; break;
                case(4): main_grid->state[x][reset_progress] = BlockState::GREEN; break;
                case(5): main_grid->state[x][reset_progress] = BlockState::ORANGE; break;
            }
        }else {
            main_grid->state[x][reset_progress] = BlockState::GRAY;
        }
    }
    main_grid->alpha = (uint8_t) (main_grid->alpha * 0.97f);
    if(++reset_progress >= main_grid->size.y) {
        can_reset = true;
        delete_timer(reset_timer);
        reset_timer = nullptr;
        lose_screen->visible = true;
        return;
    }
}
