#pragma once
#include "../gameobject.hpp"
#include "transform.hpp"
#include <libdragon.h>

COMPONENT(SpriteRenderer)

private:
    const char* spritePath;
    sprite_t* sprite;
    Transform* transform;
public:
    bool useTransparency = false;
    rdpq_blitparms_t * rdpq_blitparams = NULL;
    bool visible = true;
    void render() override;
    void ready() override;
    void setSprite(const char* spritePath);
    const char* getSpritePath();
    sprite_t* getSprite();
    ~SpriteRenderer() {}
    
COMPONENT_END()