#include <libdragon.h>
#include "gameobject.hpp"

void GameObjects::GameObject::update(float dt) {
    framesActive++;
    for (int i = 0; i < GAME_OBJECT_COMPONENT_LIMIT; i++)
    {
        if (components[i] == nullptr)
        {
            continue;
        }
        components[i]->update(dt);
    }
    for (int i = 0; i < GAME_OBJECT_CHILD_LIMIT; i++)
    {
        if (children[i] == nullptr)
        {
            continue;
        }
        children[i]->update(dt);
    }
}

void GameObjects::GameObject::ready() {
    // maybe do something here eventually
}

void GameObjects::GameObject::queue_free() {
    assert(gameManager != nullptr);
    gameManager->request_free(this);
}

bool GameObjects::GameObject::add_component(Component *component) {
    for (int i = 0; i < GAME_OBJECT_COMPONENT_LIMIT; i++)
    {
        if (components[i] != nullptr)
        {
            continue;
        }
        components[i] = component;
        component->gameObject = this;
        component->active = true;
        return true;
    }
    return false;
}

bool GameObjects::GameObject::add_child(GameObject *child) {
    for (int i = 0; i < GAME_OBJECT_CHILD_LIMIT; i++)
    {
        if (children[i] == nullptr)
        {
            children[i] = child;
            child->gameManager = gameManager;
            child->parent = this;
            gameManager->active_objects.insert(child);
            return true;
        }
    }
    // fell through
    debugf("Attempted to add child, but there was no room. Expect issues.");
    return false;
}

GameObjects::GameObject::~GameObject() {
    for (int i = 0; i < GAME_OBJECT_COMPONENT_LIMIT - 1; i++)
    {
        if (components[i] == nullptr)
        {
            continue;
        }
        delete components[i];
    }
    for (int i = 0; i < GAME_OBJECT_CHILD_LIMIT - 1; i++)
    {
        if (children[i] == nullptr)
        {
            continue;
        }
        delete children[i];
    }
}

GameObjects::GameObject::GameObject() {
    framesActive = 0;
    active = true;
    for (int i = 0; i < GAME_OBJECT_COMPONENT_LIMIT; i++)
    {
        components[i] = nullptr;
    }
    for (int i = 0; i < GAME_OBJECT_CHILD_LIMIT; i++)
    {
        children[i] = nullptr;
    }
    for (int i = 0; i < GAME_OBJECT_MANAGED_REFERNECE_LIMIT; i++)
    {
        managedReferences[i] = nullptr;
    }
    parent = nullptr;
    gameManager = nullptr;
}

void GameObjects::GameManager::request_free(GameObject *gameObject) {
    free_queue.emplace(gameObject);
}

void GameObjects::GameManager::update() {
    for (const auto gameObject : active_objects)
    {
        // game always runs at 60fps presumably, but good to check i guess.
        float fps = display_get_fps();
        if (fps == 0)
        {
            fps = 60;
        }
        gameObject->update(1 / fps);
    }

    for (const auto gameObject : free_queue)
    {
        active_objects.erase(gameObject);
        // anybody who owns a stale reference must be real mad right about now.
        delete gameObject;
    }
}
