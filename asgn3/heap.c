#include "heap.h"

#include <stdio.h>
//#include "stats.h"
#include <stdbool.h>

//Heap Sort Function. All of the pseudocode for this function was provided by Prof. Darrell Long and edited by Dr. Kerry Veenstra and Jess Srinivas in Assingment 3 document Sets and Sorts.

int max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    if ((right <= last) && (cmp(stats, A[left - 1], A[right - 1]) < 0)) {
        return right;
    }
    return left;
}

void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    int max_child(Stats * stats, uint32_t * A, uint32_t first, uint32_t last);

    bool found = false;
    uint32_t mother = first;
    uint32_t great = max_child(stats, A, mother, last);

    while ((mother <= last / 2) && (found != true)) {
        if (cmp(stats, A[mother - 1], A[great - 1]) < 0) {
            swap(stats, &A[mother - 1], &A[great - 1]);
            mother = great;
            great = max_child(stats, A, mother, last);
        } else {
            found = true;
        }
    }
}

void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    void fix_heap(Stats * stats, uint32_t * A, uint32_t first, uint32_t last);
    for (uint32_t father = last / 2; father > first - 1; father--) {
        fix_heap(stats, A, father, last);
    }
}

void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    void build_heap(Stats * stats, uint32_t * A, uint32_t first, uint32_t last);
    void fix_heap(Stats * stats, uint32_t * A, uint32_t first, uint32_t last);
    build_heap(stats, A, first, last);
    for (uint32_t leaf = last; leaf > first; leaf--) {
        swap(stats, &A[first - 1], &A[leaf - 1]);
        fix_heap(stats, A, first, leaf - 1);
    }
}
