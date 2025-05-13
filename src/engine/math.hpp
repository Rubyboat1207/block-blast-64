/**
 * @file math.hpp
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 * 
 * Copyright (C) 2025 Rubyboat (owner of https://github.com/Rubyboat1207)
 */

#pragma once
#include<stdint.h>
struct Vector2i {
    int x;
    int y;
};

struct Vector2f {
    float x;
    float y;

    inline Vector2f operator+(Vector2f other) const {
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
    inline Vector2f operator-(Vector2f other) const {
        return Vector2f{x - other.x, y - other.y};
    }
    inline Vector2f operator-(Vector2f* other) const{
        return Vector2f{x - other->x, y - other->y};
    }
    inline Vector2f operator*(float scalar) const {
        return Vector2f{x * scalar, y * scalar};
    }
    inline Vector2f operator/(float scalar) const {
        return Vector2f{x / scalar, y / scalar};
    }
    inline void operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
    }

    /// @brief Moves the vector towards a target position, taken from the godot engine
    /// @param to The target position
    /// @param delta How much to move towards the target position
    void moveTowardsWithState(Vector2f to, float delta);
    /// @brief Returns a new vector moved towards a target position, taken from the godot engine
    /// @param to The target position
    /// @param delta How much to move towards the target position
    /// @return A new vector moved towards the target position
    Vector2f vectorMovedTowards(Vector2f to, float delta);
    /// @returns the length of the vector squared (NOTE: much cheaper than length(), use this if you don't need the actual length)
    float lengthSquared() {
        return x * x + y * y;
    }
    /// @returns the length of the vector
    float length();
};

/// @brief Keeps a value between a minimum and maximum value
/// @return value between min and max, inclusive
constexpr float clamp(float value, float min, float max) {
    return (value < min) ? min : (value > max) ? max : value;
}

uint32_t random_u32();
extern uint32_t rng_state;
void set_rng_state(uint32_t state);