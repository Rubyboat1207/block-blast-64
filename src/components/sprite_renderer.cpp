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
        if(visible) {
            Vector2f camera_pos = gameObject->gameManager->camera_pos;
            graphics_draw_sprite(gameObject->gameManager->display, globalPos.x + camera_pos.x, globalPos.y + camera_pos.y, sprite);
        }
    #else
        if(visible) {
            graphics_draw_sprite(gameObject->gameManager->display, globalPos.x, globalPos.y, sprite);
        }
    #endif
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
