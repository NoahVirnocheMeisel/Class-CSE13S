#include "mathlib.h"

#include <stdio.h>
//#include "newton.c"
static int counter = 0;

double pi_madhava(void) {
    counter = 0;
    double top_value = 0.0;
    double k = 0.0;
    double sum = 0.0;
    double bottom_value = 0.0;
    do {
        top_value = 1;
        for (int i = 0; i < k; i++) {
            top_value *= 1.0 / -3;
        }
        bottom_value = (2 * k + 1);
        sum += (top_value) / (bottom_value);
        counter++;
        k++;
    } while (absolute((top_value) / (bottom_value)) > EPSILON);
    double return_value = sqrt_newton(12) * sum;
    return return_value;
}

int pi_madhava_terms(void) {
    return counter;
}
