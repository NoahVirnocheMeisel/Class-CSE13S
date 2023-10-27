#include "batcher.h"

//#include "stats.h"

#include <stdio.h>

void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    void comparator(Stats * stats, uint32_t * A, uint32_t x, uint32_t y);

    if (n == 0) {
        return;
    }
    uint32_t t = 0;
    uint32_t f = n;
    while (n > 0) {
        n = n / 2;
        t++;
    }
    n = f;
    uint32_t p = (1 << (t - 1));
    uint32_t q, r, d;
    while (p > 0) {
        q = 1 << (t - 1);
        r = 0;
        d = p;
        while (d > 0) {
            for (uint32_t i = 0; i < (n - d); i++) {
                if ((i & p) == r) {
                    comparator(stats, A, i, i + d);
                }
            }
            d = q - p;
            q = q >> 1;
            r = p;
        }
        p = p >> 1;
    }
}
void comparator(Stats *stats, uint32_t *A, uint32_t x, uint32_t y) {
    if (cmp(stats, A[y], A[x]) < 0) {
        swap(stats, &A[x], &A[y]);
    }
}
