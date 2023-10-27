#include "mathlib.h"

#include <stdio.h>
static int counter = 0;
//returns approximation of e.
double e(void) {
    counter = 0;
    double k = 1.0;
    double s = 1.0;
    double factorial = 1.0;
    double previous_factorial = 0.0;
    do {
        previous_factorial = factorial;
        factorial = k;
        factorial = factorial * previous_factorial;
        s += (1.0 / factorial);
        counter++;
        k++;
    } while (absolute((1.0 / factorial)) > EPSILON);
    return s;
}
//returns number of terms it took to get e
int e_terms(void) {
    return counter;
}
