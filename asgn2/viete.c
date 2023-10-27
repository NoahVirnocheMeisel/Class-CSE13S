#include "mathlib.h"

#include <stdio.h>

//#include "newton.c"
static int counter = 0;

double pi_viete(void) {
    counter = 0;
    double pi_viet_square_root(double number);
    double term;
    double k = 1.0;
    double product = 1.0;
    do {
        term = pi_viet_square_root(k) / 2.0;
        product *= term;
        k++;
        counter++;
    } while (absolute(1.0 - term) > EPSILON);
    return 2.0 / product;
}

int pi_viete_factors(void) {
    return counter;
}

double pi_viet_square_root(double number) {
    if (number == 1) {
        return sqrt_newton(2);
    } else {
        return sqrt_newton(2 + pi_viet_square_root(number - 1));
    }
}
