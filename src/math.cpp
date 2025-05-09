/**
 * @file math.cpp
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

#include "math.hpp"
#include <math.h>
#include <libdragon.h>

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