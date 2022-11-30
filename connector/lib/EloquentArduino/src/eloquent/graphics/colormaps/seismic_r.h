//
// Created by Simone on 18/05/2022.
//

#pragma once
#include "../../macros.h"


namespace Eloquent {
    namespace Graphics {
        namespace Colormaps {
            class Seismic_r {
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
                uint8_t red[64] = {127, 135, 143, 151, 159, 167, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 246, 230, 214, 198, 182, 165, 149, 133, 117, 101, 85, 68, 52, 36, 20, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                uint8_t green[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 20, 36, 52, 68, 85, 101, 117, 133, 149, 165, 182, 198, 214, 230, 246, 246, 230, 214, 198, 182, 165, 149, 133, 117, 101, 85, 68, 52, 36, 20, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                uint8_t blue[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 20, 36, 52, 68, 85, 101, 117, 133, 149, 165, 182, 198, 214, 230, 246, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 246, 235, 223, 212, 201, 189, 178, 167, 155, 144, 133, 121, 110, 99, 87, 76};
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Graphics::Colormaps::Seismic_r seismic_r);