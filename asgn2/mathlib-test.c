#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#define OPTIONS "aebmrvwnsh"
int main(int argc, char **argv) {
    void data_printer(double function, int terms, int s, char *name);
    int statistics = 0; //boolean to check if statistics is enabled
    int opt = 0; //value to take command line arguments using getopt function
    int checkers[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0 }; //array of booleans to check if specific command line options are enabled
    while ((opt = getopt(argc, argv, OPTIONS))
           != -1) { //assigns 1's to corresponding positions in array depending on if their
        //command was specified. a = index 0, e = index 1, etc...
        switch (opt) {
        case 'a': checkers[0] = 1; break;
        case 'e': checkers[1] = 1; break;
        case 'b': checkers[2] = 1; break;
        case 'm': checkers[3] = 1; break;
        case 'r': checkers[4] = 1; break;
        case 'v': checkers[5] = 1; break;
        case 'w': checkers[6] = 1; break;
        case 'n': checkers[7] = 1; break;
        case 's': checkers[8] = 1; break;
        case 'h': checkers[9] = 1; break;
        }
    } //help case. Prints if h specified or no functions specified.
    if (checkers[9] == 1
        || (checkers[0] == 0 && checkers[1] == 0 && checkers[2] == 0 && checkers[3] == 0
            && checkers[4] == 0 && checkers[5] == 0 && checkers[6] == 0 && checkers[7] == 0)) {
        printf("Run this file by typing one of the following after the executable in console "
               "\n-a to run all tests\n-e to run the e approximation test\n-b to run the "
               "Bailey-Browen-Ploufe approximation\n-m to run the Madhava approximation\n-r to "
               "run the Euler approximation\n-v to run the Viete approximation\n-w to run the "
               "Wallis approximation\n-n to run the Newton-Raphson squareroot approximation "
               "for\nintegers from 0 to 10\n-s to enable the printing of terms/factors for "
               "all\ntested functions\n-h to print this message again.\n");
        checkers[9] = 0;
    } //statistics checker
    if (checkers[8] == 1) {
        statistics = 1;
    } //a check. if a entered, sets all functions checkers value to 1.
    if (checkers[0] == 1) {
        for (int d = 1; d < 8; d++) {
            checkers[d] = 1;
        }
    } //e() function case
    if (checkers[1] == 1) {
        double e_diff = M_E - e();
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, e_diff);
        if (statistics == 1) {
            printf("e() terms = %d\n", e_terms());
        }
    } // pi_bbp() function case
    if (checkers[2] == 1) {
        data_printer(pi_bbp(), pi_bbp_terms(), statistics, "pi_bbp()");
    } //pi_madhava function case
    if (checkers[3] == 1) {
        data_printer(pi_madhava(), pi_madhava_terms(), statistics, "pi_madhava()");
    } //pi_euler() function case
    if (checkers[4] == 1) {
        data_printer(pi_euler(), pi_euler_terms(), statistics, "pi_euler()");
    } //pi_viete() function case
    if (checkers[5] == 1) {
        data_printer(pi_viete(), pi_viete_factors(), statistics, "pi_viete()");
    } //pi_wallis() function case
    if (checkers[6] == 1) {
        data_printer(pi_wallis(), pi_wallis_factors(), statistics, "pi_wallis()");
    } //sqrt_newton() function case. runs for values [0,10] with a step of .1
    if (checkers[7] == 1) {
        for (double i = 0; i < 9.95; i += .1) {
            double newton_diff = sqrt(i) - sqrt_newton(i);
            printf("sqrt_newton(%.2lf) = %16.15lf, sqrt(%.2lf) = %16.15lf, diff = "
                   "%16.15lf\n",
                i, sqrt_newton(i), i, sqrt(i), newton_diff);
            if (statistics == 1) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }

    return 0;
}
//function to format the output for each pi function. no function for e() and sqrt_newton().
void data_printer(double function, int terms, int s, char *name) {
    double diff = M_PI - function;
    printf("%s = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", name, function, M_PI, diff);
    if (s == 1) {
        printf("%s terms = %d\n", name, terms);
    }
}
