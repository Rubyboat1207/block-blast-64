#pragma once
#include <set>
#include <map>
#include "math.hpp"
#include <libdragon.h>
#define USING_CAMERA true


/**
 * @brief Contains primary GameObject functionality
 */
namespace GameObjects {
    // Limits
    #define GAME_OBJECT_CHILD_LIMIT 16
    #define GAME_OBJECT_COMPONENT_LIMIT 8
    #define GAME_OBJECT_MANAGED_REFERNECE_LIMIT 4

    // uses FNV-1a hash algorithm
    // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
    constexpr uint32_t typeIdHasher(const char* str, uint32_t hash = 2166136261u) {
        return (*str) ? typeIdHasher(str + 1, (hash ^ static_cast<uint32_t>(*str)) * 16777619u) : hash;
    }

    // Prototypes
    struct Component;
    struct GameObject;

    /**
     * @brief Handles game object management
     */
    struct GameManager {
        std::set<GameObject*> activeObjects = {};
        std::set<GameObject*> freeQueue = {};
        controller_data controllerState;
        surface_t* display;
        #if USING_CAMERA
        Vector2f camera_pos;
        #endif

        /**
         * @brief Requests the destruction of a game object next frame
         * @param gameObject The object to destroy
         */
        void requestFree(GameObject* gameObject);

        /**
         * @brief Update method
         */
        void update();
        
        void setRoot();
    };

    /**
     * @brief Component of a game object
     */
    struct Component {
        // Frames active
        int framesActive = 0;

        // Game object parent
        GameObject* gameObject;
        
        // Component active 
        bool active;

        /**
         * @brief Update method for a component
         * @param dt Delta time
         */
        virtual void update(float dt) {
            framesActive++;
            if(framesActive == 1) {
                ready();
            }
        }

        /**
         * @brief Render method
         */
        virtual void render() {

        }

        /**
         * @brief Ready method
         */
        virtual void ready() {

        }

        /**
         * @brief Called on child freed
         */
        virtual void onChildFreed(GameObject* freed_child) {
            
        }

        virtual ~Component() {

        }

        virtual uint32_t getType() = 0;
    };

    struct GameObject {
        // Frames active
        int framesActive;
        
        // List of child components
        Component* components[GAME_OBJECT_COMPONENT_LIMIT];

        // List of child game objects
        GameObject* children[GAME_OBJECT_CHILD_LIMIT];
        
        // Parnet gameobject (can be NULL)
        GameObject* parent;

        // List of managed references
        GameObject* managedReferences[GAME_OBJECT_MANAGED_REFERNECE_LIMIT];
        
        // Parent game manager
        GameManager* gameManager;
        
        // List of components
        int componentCount = 0;

        // Active
        bool active;

        /**
         * @brief Update method
         * @param dt Delta time
         */
        void update(float dt);

        /**
         * @brief Render method
         */
        void render();
        
        /**
         * @brief Ready method
         */
        void ready();

        /**
         * @brief Called on queue free
         */
        void queueFree();

        /**
         * @brief Get component by name
         * @param name The name of the component to search for
         */
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

        /**
         * @brief Add a component
         * @returns true on success, false otherwise
         */
        bool addComponent(Component* component);

        /**
         * @brief Add a child game object
         * @returns true on success, false otherwise
         */
        bool addChild(GameObject* child);

        /**
         * @brief Called on child free
         * @param freed_child The child which was freed
         */
        void onChildFreed(GameObject* freed_child);

        ~GameObject();
        GameObject();
    };


    // TODO: (Sam) This is kinda ugly. We should find a better way to replace it so VS Code doesn't scream about the ended brace
    // Defines a component and ends its type
    #define COMPONENT(type) struct type : public GameObjects::Component { \
        uint32_t getType() override { \
            return GameObjects::typeIdHasher(#type); \
        } 

    #define COMPONENT_END() };
    
    #define GET_COMPONENT(type) getComponent<type>(#type)
};