#pragma once
#include <memory>
#include <set>

namespace GameObjects {
    #define GAME_OBJECT_CHILD_LIMIT 16
    #define GAME_OBJECT_COMPONENT_LIMIT 8
    #define GAME_OBJECT_MANAGED_REFERNECE_LIMIT 4

    struct Component;
    struct GameObject;

    struct GameManager {
        std::set<GameObject*> active_objects;
        std::set<GameObject*> free_queue;

        void request_free(GameObject* gameObject);
        void update();
    };

    struct GameObject {
        std::unique_ptr<Component> components[GAME_OBJECT_COMPONENT_LIMIT];
        std::unique_ptr<GameObject> children[GAME_OBJECT_CHILD_LIMIT];
        GameObject* parent;
        // this is for if you want to reference another object between frames and recieve a notification if it becomes stale.
        GameObject* managed_references[GAME_OBJECT_MANAGED_REFERNECE_LIMIT];

        void update(float dt);
        void ready();
        void queue_free();

        template <typename T>
        T get_component();
        template <typename T>
        void add_component(T component);
        void add_child(GameObject* child);
    };

    struct Component {
        GameObject* gameObject;
        void update(float dt);
        void ready();
    };
}