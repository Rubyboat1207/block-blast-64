#include "math.hpp"
#include <math.h>
#include <libdragon.h>

void Vector2f::moveTowardsWithState(Vector2f to, float delta)
{
    // taken from the godot engine
	Vector2f vd = to - this;
	float len = vd.length();
    if(len <= delta || len < 0.5f ) {
        x = to.x;
        y = to.y;
        return;
    }
    Vector2f addened = vd / len * delta;
    x += addened.x;
    y += addened.y;
}

Vector2f Vector2f::vectorMovedTowards(Vector2f to, float delta)
{
    Vector2f v = *this;
	Vector2f vd = to - v;
	float len = vd.length();
	return len <= delta || len < 0.5f ? to : v + vd / len * delta;
}

float Vector2f::length()
{
    return sqrtf(lengthSquared());
}
