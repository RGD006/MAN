#pragma once
#include <cstdarg>
#include <iostream>
namespace Eloquent
{
    namespace ML
    {
        namespace Port
        {
            class SVM
            {
            public:
                /**
                 * Predict class for features vector
                 */
                int predict(float *x)
                {
                    float kernels[14] = {0};
                    float decisions[3] = {0};
                    int votes[3] = {0};
                    kernels[0] = compute_kernel(x, -72.0, -77.0, -79.0, -65.0, -66.0, -74.0);
                    kernels[1] = compute_kernel(x, -67.0, -80.0, -89.0, -51.0, -68.0, -71.0);
                    kernels[2] = compute_kernel(x, -73.0, -81.0, -74.0, -60.0, -71.0, -79.0);
                    kernels[3] = compute_kernel(x, -64.0, -85.0, -81.0, -59.0, -61.0, -67.0);
                    kernels[4] = compute_kernel(x, -75.0, -85.0, -84.0, -71.0, -70.0, -80.0);
                    kernels[5] = compute_kernel(x, -74.0, -81.0, -68.0, -53.0, -71.0, -53.0);
                    kernels[6] = compute_kernel(x, -84.0, -88.0, -69.0, -67.0, -82.0, -69.0);
                    kernels[7] = compute_kernel(x, -70.0, -74.0, -84.0, -76.0, -69.0, -79.0);
                    kernels[8] = compute_kernel(x, -72.0, -88.0, -77.0, -56.0, -66.0, -68.0);
                    kernels[9] = compute_kernel(x, -66.0, -88.0, -76.0, -46.0, -60.0, -56.0);
                    kernels[10] = compute_kernel(x, -63.0, -84.0, -58.0, -45.0, -72.0, -59.0);
                    kernels[11] = compute_kernel(x, -61.0, -87.0, -73.0, -51.0, -73.0, -57.0);
                    kernels[12] = compute_kernel(x, -79.0, -93.0, -74.0, -55.0, -74.0, -61.0);
                    kernels[13] = compute_kernel(x, -65.0, -87.0, -68.0, -65.0, -58.0, -63.0);
                    decisions[0] = 20.639668981443 + kernels[0] * 0.026621373096 + kernels[1] * 0.005999530575 + kernels[2] * 0.005510420346 + kernels[3] * -0.011264931857 + kernels[4] * -0.020301032477 + kernels[5] * -0.006565359683;
                    decisions[1] = 23.072807025433 + kernels[0] * 0.112837984683 + kernels[1] * 0.008172942813 + kernels[7] * -0.070513480263 + kernels[8] * -0.030391316155 + kernels[9] * -0.013839404736 + kernels[10] * -0.006266726342;
                    decisions[2] = 4.104702627784 + kernels[3] + kernels[4] * 0.965401725738 + kernels[5] * 0.587309284404 + kernels[6] * 0.460408813416 - kernels[7] + kernels[8] * -0.763502077583 + kernels[11] * -0.105540295304 + kernels[12] * -0.907784652752 + kernels[13] * -0.236292797919;
                    votes[decisions[0] > 0 ? 0 : 1] += 1;
                    votes[decisions[1] > 0 ? 0 : 2] += 1;
                    votes[decisions[2] > 0 ? 1 : 2] += 1;
                    int val = votes[0];
                    int idx = 0;

                    for (int i = 1; i < 3; i++)
                    {
                        if (votes[i] > val)
                        {
                            val = votes[i];
                            idx = i;
                        }
                    }

                    return idx;
                }

                /**
                 * Predict readable class name
                 */
                const char *predictLabel(float *x)
                {
                    return idxToLabel(predict(x));
                }

                /**
                 * Convert class idx to readable name
                 */
                const char *idxToLabel(uint8_t classIdx)
                {
                    switch (classIdx)
                    {
                    case 0:
                        return "bedroom_my";
                    case 1:
                        return "bedroom_parents";
                    case 2:
                        return "living_room";
                    default:
                        return "Houston we have a problem";
                    }
                }

            protected:
                /**
                 * Compute kernel between feature vector and support vector.
                 * Kernel type: linear
                 */
                float compute_kernel(float *x, ...)
                {
                    va_list w;
                    va_start(w, 6);
                    float kernel = 0.0;

                    for (uint16_t i = 0; i < 6; i++)
                    {
                        kernel += x[i] * va_arg(w, double);
                    }

                    return kernel;
                }
            };
        }
    }
}