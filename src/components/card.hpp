#include "../gameobject.hpp"
#include "transform.hpp"

using namespace GameObjects;


COMPONENT(Card)
public:
    Transform* transform;
    
COMPONENT_END()