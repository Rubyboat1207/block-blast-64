#include "game_logic.hpp"
#include <cstdlib>
#include <ctime>
#include <climits>
#include <vector>

GameLogic *rootGameLogic = nullptr;

void GameLogic::ready()
{
}

void GameLogic::update(float dt)
{
    Component::update(dt);
    if (framesActive == 2)
    {
        refresh_pieces(false);
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
    {1, 2}
};
static Vector2i LITTLE_L[]{
    {0, 0},
    {0, 1},
    {1, 1}
};
static Vector2i SQUARE[]{
    {0, 0},
    {0, 1},
    {1, 0},
    {1, 1}
};
static Vector2i LINE[]{
    {0, 0},
    {1, 0},
    {2, 0}
};
static Vector2i SINGLE[]{
    {0, 0}
};
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

// ────────────────────────────────────────────────────────────────────────────────
// Simple xorshift random generator (no srand needed).
static uint32_t rng_state = 0x12345678; // arbitrary nonzero seed

static uint32_t random_u32()
{
    uint32_t x = rng_state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    rng_state = x;
    return x;
}

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

#define PIECE_CASE(p, size) case(PieceType::p): base = p; count = size; break;

#define ADD_PIECE(p) allowed_types[allowed_count++] = p;
#define ADD_PIECE_AFTER_COUNT(p, count) if(pieces_since[p] > count) { ADD_PIECE(p) }
#define ADD_PIECE_UNIQUE_TO_SET(p) ADD_PIECE_AFTER_COUNT(p, 3)

std::pair<int, Vector2i *> GameLogic::get_next_piece()
{
    static Vector2i rotated[9]; // largest piece size is 9 cells
    const Vector2i *base = nullptr;
    std::array<PieceType, static_cast<int>(PieceType::Last)> allowed_types{};
    int allowed_count = 0;
    
    ADD_PIECE_UNIQUE_TO_SET(PieceType::BIG_L)
    ADD_PIECE_AFTER_COUNT(PieceType::BIG_SQUARE, 6)
    ADD_PIECE(PieceType::DIAGONAL)
    ADD_PIECE_AFTER_COUNT(PieceType::DUO, 1)
    ADD_PIECE(PieceType::LINE)
    ADD_PIECE_AFTER_COUNT(PieceType::LITTLE_L, 2)
    ADD_PIECE_AFTER_COUNT(PieceType::SINGLE, 4)
    ADD_PIECE(PieceType::SQUARE)

    PieceType piece_type = allowed_types[(random_u32() + framesActive) % allowed_count];
    Vector2i* piece = nullptr;
    int count = 0;

    switch(piece_type) {
        PIECE_CASE(BIG_L, 4)
        PIECE_CASE(LITTLE_L, 3)
        PIECE_CASE(SQUARE, 4)
        PIECE_CASE(LINE, 3)
        PIECE_CASE(SINGLE, 1)
        PIECE_CASE(DIAGONAL, 2)
        PIECE_CASE(BIG_SQUARE, 9)
        PIECE_CASE(DUO, 2)
        default: assert(false);
    }

    for(int i = 0; i < (int) PieceType::Last; i++) {
        pieces_since[(PieceType) i]++;
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
    switch ((framesActive + index) % 4)
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
    for (int x = 0; x < previews[selectedIndex]->size.x; x++)
    {
        for (int y = 0; y < previews[selectedIndex]->size.y; y++)
        {
            cursor->display_grid->setState({x, y}, previews[selectedIndex]->state[x][y]);
        }
    }
    cursor->update_collision();
}

void GameLogic::place(BlockGrid *grid, Vector2i grid_position)
{
    bool fail = false;
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
                fail = true;
                break;
            }
            int final_y = y + grid_position.y;
            if (final_y < 0 || final_y >= main_grid->size.y)
            {
                fail = true;
                break;
            }

            if (main_grid->state[final_x][final_y] != BlockState::EMPTY)
            {
                fail = true;
                break;
            }
        }
    }

    if (!fail)
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
                int final_y = y + grid_position.y;

                main_grid->state[final_x][final_y] = grid->state[x][y];
            }
        }

        // Check for vertical and horizontal rows to remove – simultaneously
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

        // 2. Detect full rows
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

        // 3. Clear all marked columns
        for (int x : columns_to_clear)
        {
            for (int y = 0; y < main_grid->size.y; ++y)
                main_grid->state[x][y] = BlockState::EMPTY;
        }

        // 4. Clear all marked rows
        for (int y : rows_to_clear)
        {
            for (int x = 0; x < main_grid->size.x; ++x)
                main_grid->state[x][y] = BlockState::EMPTY;
        }

        previews[selector->selected]->visible = false;

        bool was_able_to_select = false;
        for (int i = 0; i < 3; i++)
        {
            if (previews[i]->visible)
            {
                was_able_to_select = true;
                selector->select(i);
            }
        }

        if (!was_able_to_select)
        {
            refresh_pieces(true);
        }
    }
}
