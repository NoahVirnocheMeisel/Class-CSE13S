#include "mathlib.h"

#include <stdio.h>
static int counter = 0;

double pi_wallis(void) {
    counter = 0;
    double k = 1.0;
    double top;
    double bottom;
    double product = 1;
    do {
        top = 4.0 * (k * k);
        bottom = 4.0 * (k * k) - 1.0;
        product *= (top / bottom);
        k++;
        counter++;
    } while (absolute(1.0 - (top / bottom)) > EPSILON);
    return 2.0 * product;
}

int pi_wallis_factors(void) {
    return counter;
}
