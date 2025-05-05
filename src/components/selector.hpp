#include "../gameobject.hpp"
#include "transform.hpp"

COMPONENT(Selector)
    Transform* transform;
    int selected = 0;
    void ready() override;
    void update(float dt);
    ~Selector() {}
    void setVisualState();
    void cleanVisualState();
    void setState();
COMPONENT_END()