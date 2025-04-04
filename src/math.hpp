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
};

const float CosCoefficients[2] = { 
    -0.000000011485057369884462f,
     0.000000000021380733869182293f 
};

#define quasi_cos_4(x) (1 + x * x * (CosCoefficients[0] + CosCoefficients[1] * x * x))

Vector2f sincosFOURTHORDER(int16_t int_angle);
