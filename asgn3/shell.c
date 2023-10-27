#include "shell.h"

#include "gaps.h"
//include "stats.h"

#include <stdio.h>

//Shell Sort Function:  Made using python pseudo code written by Prof. Darrell Long and edited by Dr. Kerry Veenstra and Jess Srinivas. The pseudocode can be found in the Assingment 3 PDF, Sets and Sorting.`
void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t j;
    uint32_t gap;
    uint32_t temp;
    for (int gap_index = 0; gap_index < GAPS; gap_index++) {
        gap = gaps[gap_index];
        for (uint32_t i = gap; i < n; i++) {
            j = i;
            temp = move(stats, A[i]);
            while (j >= gap && (cmp(stats, temp, A[j - gap]) < 0)) {
                A[j] = move(stats, A[j - gap]);
                j -= gap;
            }
            A[j] = move(stats, temp);
        }
    }
}
