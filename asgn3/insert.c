#include "insert.h"

//#include "stats.h"

#include <stdio.h>

//Insertion Sort Algorithim. Made using python pseudo code written by Prof. Darrell Long and edited by Dr. Kerry Veenstra and Jess Srinivas. The pseudocode can be found in the Assingment 3 PDF, Sets and Sorting.
void insertion_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    uint32_t j;
    uint32_t temp;
    for (uint32_t k = 1; k < length; k++) {
        j = k;
        temp = move(stats, arr[k]);
        while (j > 0 && (cmp(stats, temp, arr[j - 1]) < 0)) {
            arr[j] = move(stats, arr[j - 1]);
            j -= 1;
        }
        arr[j] = move(stats, temp);
    }
}
