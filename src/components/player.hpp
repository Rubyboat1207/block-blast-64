#include "../gameobject.hpp"
#include "transform.hpp"

COMPONENT(Player)
private:
    Vector2f velocity;
    Transform* transform;
    float speed = 100.0f;
    float acceleration = 1000.0f;
public:
    void update(float dt) override;
    void ready() override;
};