#pragma once
#include <set>
#include "math.hpp"
#include <libdragon.h>
#define USING_CAMERA false


/// @brief Namespace containing primary gameobject related core functionality
namespace GameObjects {
    #define GAME_OBJECT_CHILD_LIMIT 16
    #define GAME_OBJECT_COMPONENT_LIMIT 8
    #define GAME_OBJECT_MANAGED_REFERNECE_LIMIT 4

    // uses FNV-1a hash algorithm
    // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
    constexpr uint32_t typeIdHasher(const char* str, uint32_t hash = 2166136261u) {
        return (*str) ? typeIdHasher(str + 1, (hash ^ static_cast<uint32_t>(*str)) * 16777619u) : hash;
    }

    struct Component;
    struct GameObject;

    /// @brief Handles game object management
    struct GameManager {
        std::set<GameObject*> active_objects;
        std::set<GameObject*> free_queue;
        surface_t* display;
        #if USING_CAMERA
        Vector2f camera_pos;
        #endif

        void request_free(GameObject* gameObject);
        void update();
    };

    struct Component {
        int framesActive = 0;
        GameObject* gameObject;
        virtual void update(float dt) {
            framesActive++;
            if(framesActive == 1) {
                ready();
            }
        }
        virtual void ready() {

        }
        bool active;
        virtual ~Component() {

        }
        virtual uint32_t getType() = 0;
    };

    struct GameObject {
        int framesActive;
        Component* components[GAME_OBJECT_COMPONENT_LIMIT];
        GameObject* children[GAME_OBJECT_CHILD_LIMIT];
        GameObject* parent;
        GameObject* managedReferences[GAME_OBJECT_MANAGED_REFERNECE_LIMIT];
        GameManager* gameManager;
        bool active;

        void update(float dt);
        void ready();
        void queue_free();

        template <typename T>
        T* getComponent(const char* name) {
            for (int i = 0; i < GAME_OBJECT_COMPONENT_LIMIT; i++)
            {
                if(components[i] == nullptr)
                {
                    continue;
                }
                if(components[i]->getType() == typeIdHasher(name))
                {
                    return static_cast<T*>(components[i]);
                }
            }
            return nullptr;
        }
        bool add_component(Component* component);
        bool add_child(GameObject* child);
        ~GameObject();
        GameObject();
    };

    #define COMPONENT(type) struct type : public GameObjects::Component { \
        uint32_t getType() override { \
            return GameObjects::typeIdHasher(#type); \
        }
    
    #define GET_COMPONENT(type) getComponent<type>(#type)
};