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
    bool visible = true;
    void render() override;
    void ready() override;
    void setSprite(const char* spritePath);
    const char* getSpritePath();
    sprite_t* getSprite();
    ~SpriteRenderer() {}
    
COMPONENT_END()