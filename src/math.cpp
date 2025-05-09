#include "math.hpp"
#include <math.h>
#include <libdragon.h>

void Vector2f::moveTowardsWithState(Vector2f to, float delta)
{
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

uint32_t rng_state = 0x12345678; // arbitrary nonzero seed

uint32_t random_u32()
{
    uint32_t x = rng_state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    rng_state = x;
    return x;
}
void set_rng_state(uint32_t state) {
    rng_state = state;
}