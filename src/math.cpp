#include "math.hpp"
#include <math.h>
#include <libdragon.h>

// Vector2f sincosFOURTHORDER(int16_t int_angle) {
//     int32_t shifter = (int_angle ^ (int_angle << 1)) & 0xC000;
//     float cosx = quasi_cos_4((float)(((int_angle + shifter) << 17) >> 16));
//     debugf("cosx: %f", cosx);
//     float sinx = sqrtf(1 - cosx * cosx);

//     if (shifter & 0x4000) {
//         float temp = cosx;
//         cosx = sinx;
//         sinx = temp;
//     }

//     if (int_angle < 0) {
//         sinx = -sinx;
//     }

//     if (shifter & 0x8000) {
//         cosx = -cosx;
//     }

//     return Vector2f{sinx, cosx};
// }