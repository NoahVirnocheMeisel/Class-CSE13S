#include "batcher.h"
#include "gaps.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "aishqbr:n:p:H"
enum options { i, s, h, q, b };
int main(int argc, char **argv) {
    void make_array(uint32_t seed, uint32_t size, uint32_t * ArrayMemory);
    uint32_t seed = 13371453;
    uint32_t size = 100;
    bool help = false;
    Stats information;
    uint32_t elements = 100;
    int opt = 0; //value to take command line arguments using getopt function
    Set commands = set_empty(); //sejt to check if specific command line options are enabled
    while (
        (opt = getopt(argc, argv, OPTIONS))
        != -1) { //runs for all command line options. Adds specified sorts to set and updates specified values.
        switch (opt) {
        case 'a': commands = set_universal(); break;
        case 'i': commands = set_insert(commands, i); break;
        case 's': commands = set_insert(commands, s); break;
        case 'h': commands = set_insert(commands, h); break;
        case 'q': commands = set_insert(commands, q); break;
        case 'b': commands = set_insert(commands, b); break;
        case 'r': seed = strtoull(optarg, NULL, 0); break;
        case 'n': size = strtoull(optarg, NULL, 0); break;
        case 'p': elements = strtoull(optarg, NULL, 0); break;
        case 'H':
            help = true;
            printf("-a: runs all algorithims\n-i: runs Insertion Sort\n -s: runs shell sort\n-h: "
                   "runs Heap Sort\n -q: runs Quick Sort\n-b: runs Batcher sort\n-r seed: sets the "
                   "seed to the given value\n -n size: sets the array size to size\n -p value: "
                   "sets the number of elements to print to value\n -H: prints this message\n");
            break;
        }
    }
    uint32_t *A = (uint32_t *) calloc(size, 32); //allocates memory for an array
    int newline = 0; //variable to track when to use a newline.
    if (commands == set_empty() && help == false) {
        printf("-a: runs all algorithims\n-i: runs Insertion Sort\n -s: runs shell sort\n-h: "
               "runs Heap Sort\n -q: runs Quick Sort\n-b: runs Batcher sort\n-r seed: sets the "
               "seed to the given value\n -n size: sets the array size to size\n -p value: "
               "sets the number of elements to print to value\n -H: prints this message\n");
    }
    //the following sequence of if statements checks the set to see if the specific letter has been added. If so, it creates an array using the memory allocated with calloc(), sorts the array, then prints the array and the number of moves/compares it took to sort it. Then the statement resets satistics. This could likely be made less repetitive by writing it as a function.
    if (set_member(commands, i)) {
        set_remove(commands, i);
        make_array(seed, size, A);
        insertion_sort(&information, A, size);
        print_stats(&information, "Insertion Sort", size);
        for (uint32_t i = 0; (i < elements) && (i < size); i++) {
            printf("%13" PRIu32, A[i]);
            newline++;
            if (newline >= 5) {
                newline = 0;
                printf("\n");
            }
        }
        if (0 < newline && newline < 5) {
            printf("\n");
        }
        reset(&information);
    }
    if (set_member(commands, h)) {
        newline = 0;
        set_remove(commands, h);
        make_array(seed, size, A);
        heap_sort(&information, A, size);
        print_stats(&information, "Heap Sort", size);
        for (uint32_t i = 0; (i < elements) && (i < size); i++) {
            printf("%13" PRIu32, A[i]);
            newline++;
            if (newline >= 5) {
                newline = 0;
                printf("\n");
            }
        }
        if (0 < newline && newline < 5) {
            printf("\n");
        }
        reset(&information);
    }
    if (set_member(commands, s)) {
        newline = 0;
        set_remove(commands, s);
        make_array(seed, size, A);
        shell_sort(&information, A, size);
        print_stats(&information, "Shell Sort", size);
        for (uint32_t i = 0; (i < elements) && (i < size); i++) {
            printf("%13" PRIu32, A[i]);
            newline++;
            if (newline >= 5) {
                newline = 0;
                printf("\n");
            }
        }
        if (0 < newline && newline < 5) {
            printf("\n");
        }
        reset(&information);
    }
    if (set_member(commands, q)) {
        newline = 0;
        set_remove(commands, q);
        make_array(seed, size, A);
        quick_sort(&information, A, size);
        print_stats(&information, "Quick Sort", size);
        for (uint32_t i = 0; (i < elements) && (i < size); i++) {
            printf("%13" PRIu32, A[i]);
            newline++;
            if (newline >= 5) {
                newline = 0;
                printf("\n");
            }
        }
        if (0 < newline && newline < 5) {
            printf("\n");
        }
        reset(&information);
    }
    if (set_member(commands, b)) {
        newline = 0;
        set_remove(commands, b);
        make_array(seed, size, A);
        batcher_sort(&information, A, size);
        print_stats(&information, "Batcher Sort", size);
        for (uint32_t i = 0; (i < elements) && (i < size); i++) {
            printf("%13" PRIu32, A[i]);
            newline++;
            if (newline >= 5) {
                newline = 0;
                printf("\n");
            }
        }
        if (0 < newline && newline < 5) {
            printf("\n");
        }
        reset(&information);
    }
    free(A); //frees memory.
} //make_array creates an array using the memory allocated from calloc() and the random function.
void make_array(uint32_t seed, uint32_t size, uint32_t *ArrayMemory) {
    srandom(seed);
    for (uint32_t i = 0; i < size; i++) {
        ArrayMemory[i] = (random() & 0x3fffffff);
    }
}
