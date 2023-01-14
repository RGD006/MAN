#pragma once
#include <cstdarg>
#include <cstdint>
namespace Eloquent
{
  namespace ML
  {
    namespace Port
    {
      class OneClassSVM
      {
      public:
        /**
         * Predict class for features vector
         */
        int predict(float *x)
        {
          float kernels[6] = {0};
          kernels[0] = compute_kernel(x, -76.0, -81.0, -84.0, -53.0, -61.0, -80.0);
          kernels[1] = compute_kernel(x, -78.0, -81.0, -87.0, -56.0, -62.0, -79.0);
          kernels[2] = compute_kernel(x, -67.0, -81.0, -70.0, -50.0, -61.0, -60.0);
          kernels[3] = compute_kernel(x, -64.0, -89.0, -68.0, -45.0, -64.0, -55.0);
          kernels[4] = compute_kernel(x, -63.0, -86.0, -68.0, -46.0, -63.0, -57.0);
          kernels[5] = compute_kernel(x, -64.0, -89.0, -67.0, -44.0, -63.0, -56.0);
          float decision = -165338.5 - (+kernels[0] + kernels[1] * 0.5 + kernels[2] + kernels[3] + kernels[4] + kernels[5]);

          return decision > 0 ? 0 : 1;
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
            return "bedroom";
          case 1:
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