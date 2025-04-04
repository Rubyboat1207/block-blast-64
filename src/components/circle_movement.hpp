#include "../gameobject.hpp"
#include "transform.hpp"

using namespace GameObjects;


COMPONENT(CircleMovement)

    Transform* transform;
    Vector2f center;
    float radius;
    void ready() override;
    void update(float dt) override;
    ~CircleMovement() {}

COMPONENT_END()