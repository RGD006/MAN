//
// Created by Simone on 18/05/2022.
//

#pragma once
#include "../../macros.h"


namespace Eloquent {
    namespace Graphics {
        namespace Colormaps {
            class Jet {
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
                uint8_t red[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 25, 38, 51, 64, 77, 90, 103, 116, 129, 142, 156, 169, 182, 195, 208, 221, 234, 247, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 237, 219, 201, 182, 164, 145, 127};
                uint8_t green[64] = {0, 0, 0, 0, 0, 0, 0, 0, 2, 18, 34, 50, 66, 82, 99, 115, 131, 147, 163, 180, 196, 212, 228, 244, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 244, 229, 214, 199, 184, 169, 154, 139, 124, 109, 94, 79, 64, 49, 34, 19, 4, 0, 0, 0, 0, 0, 0};
                uint8_t blue[64] = {127, 145, 164, 182, 201, 219, 237, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 247, 234, 221, 208, 195, 182, 169, 156, 142, 129, 116, 103, 90, 77, 64, 51, 38, 25, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Graphics::Colormaps::Jet jet);