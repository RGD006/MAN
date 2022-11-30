//
// Created by Simone on 18/05/2022.
//

#pragma once
#include "../../macros.h"


namespace Eloquent {
    namespace Graphics {
        namespace Colormaps {
            class Bone {
            public:

                /**
                 * Convert single byte to RGB color
                 * @param x
                 * @param r
                 * @param g
                 * @param b
                 */
                void convert(uint8_t x, uint8_t *r, uint8_t *g, uint8_t *b) {
                    *r = red[x << 2];
                    *g = green[x << 2];
                    *b = blue[x << 2];
                }

            protected:
                uint8_t red[64] = {0, 3, 7, 10, 14, 17, 21, 24, 28, 31, 35, 38, 42, 46, 49, 53, 56, 60, 63, 67, 70, 74, 77, 81, 85, 88, 92, 95, 99, 102, 106, 109, 113, 116, 120, 123, 127, 131, 134, 138, 141, 145, 148, 152, 155, 159, 162, 166, 171, 177, 183, 188, 194, 199, 205, 210, 216, 221, 227, 232, 238, 243, 249, 255};
                uint8_t green[64] = {0, 3, 7, 10, 14, 17, 21, 24, 28, 31, 35, 38, 42, 46, 49, 53, 56, 60, 63, 67, 70, 74, 77, 81, 86, 91, 96, 100, 105, 110, 115, 120, 125, 130, 135, 139, 144, 149, 154, 159, 164, 169, 173, 178, 183, 188, 193, 198, 201, 205, 208, 212, 216, 219, 223, 226, 230, 233, 237, 240, 244, 247, 251, 255};
                uint8_t blue[64] = {0, 4, 9, 14, 19, 24, 29, 34, 39, 44, 49, 54, 59, 64, 68, 73, 78, 83, 88, 93, 98, 103, 108, 113, 116, 120, 123, 127, 131, 134, 138, 141, 145, 148, 152, 155, 159, 162, 166, 169, 173, 177, 180, 184, 187, 191, 194, 198, 201, 205, 208, 212, 216, 219, 223, 226, 230, 233, 237, 240, 244, 247, 251, 255};
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Graphics::Colormaps::Bone bone);