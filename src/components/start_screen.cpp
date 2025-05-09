#include "start_screen.hpp"
#include "../scenes/scenes.hpp"

void StartScreen::update(float dt)
{
    if(gameObject->gameManager->controllerState.c->start) {
        // prayge to god this works.
        rng_state += framesActive;
        init_main_scene(gameObject->gameManager);
    }
}