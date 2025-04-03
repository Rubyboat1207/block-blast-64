#include<libdragon.h>
#include "gameobject.hpp"

void GameObjects::GameObject::update(float dt)
{
    for(int i = 0; i < GAME_OBJECT_COMPONENT_LIMIT; i++) {
        if(components[i] == nullptr) {
            continue;
        }
        components[i]->update(dt);
    }
    for(int i = 0; i < GAME_OBJECT_CHILD_LIMIT; i++) {
        if(children[i] == nullptr) {
            continue;
        }
        children[i]->update(dt);
    }
}

void GameObjects::GameObject::ready()
{
    for(int i = 0; i < GAME_OBJECT_COMPONENT_LIMIT; i++) {
        if(components[i] == nullptr) {
            continue;
        }
        components[i]->ready();
    }
    for(int i = 0; i < GAME_OBJECT_CHILD_LIMIT; i++) {
        if(children[i] == nullptr) {
            continue;
        }
        children[i]->ready();
    }
}

void GameObjects::GameManager::request_free(GameObject *gameObject)
{
    free_queue.emplace(gameObject);
}

void GameObjects::GameManager::update()
{
    for(const auto gameObject : active_objects) {
        // game always runs at 60fps presumably, but good to check i guess.
        gameObject->update(1/display_get_fps());
    }

    for(const auto gameObject : free_queue) {
        active_objects.erase(gameObject);
        // anybody who owns a stale reference must be real mad right about now.
        delete gameObject;
    }
}
