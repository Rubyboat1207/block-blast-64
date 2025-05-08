#pragma once
#include "../gameobject.hpp"

#define CLEAR_ANIM_HORIZONTAL_ORIGIN 64
#define CLEAR_ANIM_VERTICAL_ORIGIN 0
#define CLEAR_ANIM_TOTAL_FRAMES 11
#define CLEAR_ANIM_MAX_COUNT_ACTIVE 12
#define CLEAR_ANIM_TOTAL_HOLD_FRAMES 6

struct ClearAnimation {
    uint8_t index;
    bool vertical;
    uint8_t animation_progress;
    uint8_t hold_time;

    inline ClearAnimation(uint8_t index, bool vertical): index(index), vertical(vertical), animation_progress(0), hold_time(0) {}
};

COMPONENT(ClearAnimationManager)
    ClearAnimation* clear_animations[CLEAR_ANIM_MAX_COUNT_ACTIVE] = {};
    sprite_t* clear_anim_sprite;

    void ready() override;
    void render();
    ~ClearAnimationManager() {}
COMPONENT_END()