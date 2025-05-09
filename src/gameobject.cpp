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
        if(!components[i]->active) {
            continue;
        }
        components[i]->update(dt);
    }
}

void GameObjects::GameObject::render()
{
    for (int i = 0; i < GAME_OBJECT_COMPONENT_LIMIT; i++)
    {
        if (components[i] == nullptr)
        {
            continue;
        }
        if(!components[i]->active) {
            continue;
        }
        components[i]->render();
    }
}

void GameObjects::GameObject::ready() {
    // maybe do something here eventually
}

void GameObjects::GameObject::queueFree() {
    assert(gameManager != nullptr);
    gameManager->requestFree(this);
    for (int i = 0; i < GAME_OBJECT_CHILD_LIMIT; i++) {
        if (children[i] != nullptr) {
            children[i]->queueFree();
            children[i] = nullptr;
        }
    }
}

bool GameObjects::GameObject::addComponent(Component *component) {
    for (int i = 0; i < GAME_OBJECT_COMPONENT_LIMIT; i++)
    {
        if (components[i] != nullptr)
        {
            continue;
        }
        components[i] = component;
        component->gameObject = this;
        component->active = true;
        componentCount++;
        return true;
    }
    return false;
}

bool GameObjects::GameObject::addChild(GameObject *child) {
    for (int i = 0; i < GAME_OBJECT_CHILD_LIMIT; i++)
    {
        if (children[i] == nullptr)
        {
            children[i] = child;
            child->gameManager = gameManager;
            child->parent = this;
            gameManager->activeObjects.insert(child);
            return true;
        }
    }
    // fell through
    debugf("Attempted to add child, but there was no room. Expect issues.");
    return false;
}

void GameObjects::GameObject::onChildFreed(GameObject *freed_child)
{
    for (int i = 0; i < GAME_OBJECT_COMPONENT_LIMIT - 1; i++)
    {
        if (components[i] == nullptr)
        {
            continue;
        }
        // maybe make this a signal or event that can be listened to instead of this.
        components[i]->onChildFreed(freed_child);
    }
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

void GameObjects::GameManager::requestFree(GameObject *gameObject) {
    freeQueue.emplace(gameObject);
}

void GameObjects::GameManager::update() {
    // game always runs at 60fps presumably, but good to check i guess.
    controller_scan();
    controller_read(&controllerState);
    float fps = display_get_fps();
    if (fps == 0)
    {
        fps = 60;
    }
    for (const auto gameObject : activeObjects)
    {
        if(!gameObject->active) {
            continue;
        }
        gameObject->update(1 / fps);
    }

    for (const auto gameObject : activeObjects)
    {
        if(!gameObject->active) {
            continue;
        }
        gameObject->render();
    }

    for (const auto gameObject : freeQueue)
    {
        activeObjects.erase(gameObject);
        debugf("freeing an object");
        if(gameObject->parent) {
            for(int i = 0; i < GAME_OBJECT_CHILD_LIMIT; i++) {
                if(gameObject->parent->children[i] == gameObject) {
                    gameObject->parent->children[i] = nullptr;
                    break;
                }
            }
        }
        // anybody who owns a stale reference must be real mad right about now.
        delete gameObject;
    }

    freeQueue.clear();
}

void GameObjects::GameManager::setRoot(GameObject *gameObject)
{
    if(root != nullptr) {
        root->queueFree();
    }
    root = gameObject;
}

// void GameObjects::GameManager::addManagedReference(GameObject *refering, GameObject *reference)
// {
//     if(references.contains(reference)) {

//     }
// }
