#include "mathlib.h"

#include <stdio.h>

static int counter = 0;

double pi_bbp(void) {
    counter = 0;
    double k = 0.0;
    double power = 1.0;
    double inside = 0.0;
    double sum = 0.0;
    do {
        power = 1.0;
        for (int i = 0; i < k; i++) {
            power *= 16.0;
        }
        inside = ((4.0 / (8.0 * k + 1.0)) - (2.0 / (8.0 * k + 4.0)) - (1.0 / (8.0 * k + 5.0))
                  - (1.0 / (8.0 * k + 6.0)));
        sum += (1.0 / power) * inside;
        counter++;
        k++;
    } while (absolute((1.0 / power) * inside) > EPSILON);
    return sum;
}

int pi_bbp_terms(void) {
    return counter;
}
