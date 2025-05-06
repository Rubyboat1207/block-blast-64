#include "text_renderer.hpp"

void TextRenderer::ready() {
    Component::ready();
    if(gameObject == nullptr) {
        return;
    }
    transform = gameObject->GET_COMPONENT(Transform);
}

void TextRenderer::render() {
    auto position = transform->getGlobalPosition();
    rdpq_set_mode_standard();
    rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
    rdpq_set_prim_color(RGBA32(255,255,255,255));
    rdpq_text_print(NULL, 1, position.x, position.y, text.c_str());
}