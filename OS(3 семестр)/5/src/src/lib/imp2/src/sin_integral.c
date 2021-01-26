#include <math.h>


#include "../sin_integral.h"


float SinIntegral(float A, float B, float e) {
    if (A == B || e <= 0) {
        return 0;
    }

    if (A > B) {
        float tmp = B;
        B = A;
        A = tmp;
    }

    if (B - A <= e) {
        float y1 = sinf(A);
        float y2 = sinf(B);
        return (y1 + y2) / 2 * (B - A);
    }

    float integral = 0;
    while (A + e <= B) {
        float y1 = sinf(A);
        float y2 = sinf(B);
        integral += (y1 + y2) / 2 * e;
        A += e;
    }

    if (A + e != B) {
        float y1 = sinf(A);
        float y2 = sinf(B);
        integral += (y1 + y2) / 2 * (B - A);
    }

    return integral;
}
