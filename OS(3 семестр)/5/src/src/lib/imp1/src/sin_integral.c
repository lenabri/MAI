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
        return sinf(A) * (B - A);
    }

    float integral = 0;
    while (A + e <= B) {
        integral += sinf(A) * e;
        A += e;
    }

    if (A + e != B) {
        integral += sinf(A) * (B - A);
    }

    return integral;
}
