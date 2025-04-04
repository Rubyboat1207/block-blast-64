#pragma once
#include<stdint.h>
struct Vector2i {
    int x;
    int y;
};

struct Vector2f {
    float x;
    float y;

    inline Vector2f operator+(Vector2f other) {
        return Vector2f{x + other.x, y + other.y};
    }

    inline void operator+=(Vector2f other) {
        x += other.x;
        y += other.y;
    }
    inline void operator-=(Vector2f other) {
        x -= other.x;
        y -= other.y;
    }
    inline Vector2f operator-(Vector2f other) {
        return Vector2f{x - other.x, y - other.y};
    }
    inline Vector2f operator-(Vector2f* other) {
        return Vector2f{x - other->x, y - other->y};
    }
    inline Vector2f operator*(float scalar) {
        return Vector2f{x * scalar, y * scalar};
    }
    inline Vector2f operator/(float scalar) {
        return Vector2f{x / scalar, y / scalar};
    }
    inline void operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
    }

    void moveTowardsWithState(Vector2f to, float delta);
    Vector2f vectorMovedTowards(Vector2f to, float delta);
    float lengthSquared() {
        return x * x + y * y;
    }
    float length();
};

constexpr float clamp(float value, float min, float max) {
    return (value < min) ? min : (value > max) ? max : value;
}
