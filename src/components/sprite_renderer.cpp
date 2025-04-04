#include "../gameobject.hpp"
#include <libdragon.h>
#include "transform.hpp"
#include "sprite_renderer.hpp"

using namespace GameObjects;

void SpriteRenderer::render() {
    Component::render();
    if(!visible) {
        return;
    }
    Vector2f globalPos = transform->getGlobalPosition();
    #if USING_CAMERA
    globalPos += gameObject->gameManager->camera_pos;
    #endif

    if(useTransparency) {
        graphics_draw_sprite_trans(gameObject->gameManager->display, globalPos.x, globalPos.y, sprite);
    }else {
        graphics_draw_sprite(gameObject->gameManager->display, globalPos.x, globalPos.y, sprite);
    }
}

void SpriteRenderer::ready() {
    Component::ready();
    if(gameObject == nullptr) {
        return;
    }
    transform = gameObject->GET_COMPONENT(Transform);
}

void SpriteRenderer::setSprite(const char *spritePath) {
    this->spritePath = spritePath;

    sprite = sprite_load(spritePath);
}

const char *SpriteRenderer::getSpritePath()
{
    return spritePath;
}

sprite_t *SpriteRenderer::getSprite()
{
    return sprite;
}
