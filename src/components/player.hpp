#include "../gameobject.hpp"
#include "transform.hpp"

COMPONENT(Player)
private:
    Vector2f velocity;
    Transform* transform;
    float speed = 300.0f;
    float acceleration = 2000.0f;
public:
    void update(float dt) override;
    void ready() override;
};