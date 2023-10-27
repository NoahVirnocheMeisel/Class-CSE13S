#include "mathlib.h"

#include <stdio.h>
//#include "newton.c"
static int counter;

double pi_euler(void) {
    counter = 0;
    double k = 1.0;
    double sum = 0.0;
    double term = 0.0;
    do {
        term = 0.0;
        term = (1.0 / (k * k));
        sum += term;
        k++;
        counter++;

    } while (absolute(term) > EPSILON);
    return sqrt_newton((6.0 * sum));
}

int pi_euler_terms(void) {
    return counter;
}
