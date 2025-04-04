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

    Vector2f moveTowards(Vector2f to, float delta);
    float lengthSquared() {
        return x * x + y * y;
    }
    float length();
};

constexpr float clamp(float value, float min, float max) {
    return (value < min) ? min : (value > max) ? max : value;
}

const float CosCoefficients[2] = { 
    -0.000000011485057369884462f,
     0.000000000021380733869182293f 
};

#define quasi_cos_4(x) (1 + x * x * (CosCoefficients[0] + CosCoefficients[1] * x * x))

Vector2f sincosFOURTHORDER(int16_t int_angle);
