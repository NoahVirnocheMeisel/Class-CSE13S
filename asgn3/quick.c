#include "quick.h"

//#include "stats.h"

#include <stdio.h>

//Quick Sort Function and helper functions. Pseudocode for all functions written by Prof. Darrell Long and edited by Dr. Kerry Veenstra and Jess Srinivas. The exact pseduocode can be found in the document Assginment 3: Sets and Sorting.

//main function called by sorting.c. Takes pointer statistics structure, pointer to an array, and a number n(WHAT IS N AHAHH).
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    void quick_sorter(Stats * stats, uint32_t * A, uint32_t n, uint32_t low, uint32_t high);
    quick_sorter(stats, A, n, 1, n);
}
//Recursive helper function for quick_sort. Takes the exact same arguments as quick_sort.
void quick_sorter(Stats *stats, uint32_t *A, uint32_t n, uint32_t low, uint32_t high) {
    int partition(Stats * stats, uint32_t * A, uint32_t low, uint32_t high);
    int p;
    if (low < high) {
        p = partition(stats, A, low, high);
        quick_sorter(stats, A, n, low, p - 1);
        quick_sorter(stats, A, n, p + 1, high);
    }
}

int partition(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {
    uint32_t i = low - 1;
    for (uint32_t j = low; j < high; j++) {
        if (cmp(stats, A[j - 1], A[high - 1]) < 0) {
            i += 1;
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }
    swap(stats, &A[i], &A[high - 1]);
    return (i + 1);
}
