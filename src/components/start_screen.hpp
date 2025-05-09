#include "../gameobject.hpp"
#include "transform.hpp"

COMPONENT(StartScreen)

    void update(float dt) override;
    ~StartScreen() {}

COMPONENT_END()