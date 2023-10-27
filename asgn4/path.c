#include "path.h"

#include "stack.h"

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->vertices = stack_create(capacity);
    p->total_weight = 0;
    return p;
}

void path_free(Path **pp) {
    if (pp != NULL && *pp != NULL) {
        stack_free(&(*pp)->vertices);
        free(*pp);
    }
    if (pp != NULL) {
        *pp = NULL;
    }
}

uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}
uint32_t path_distance(const Path *p) {
    return p->total_weight;
}
void path_add(Path *p, uint32_t val, const Graph *g) {
    if (stack_empty(p->vertices) == false) {
        uint32_t top = 0;
        stack_peek(p->vertices, &top);
        p->total_weight += graph_get_weight(g, top, val);
    }
    stack_push(p->vertices, val);
}
//returns the graph inde
uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t top = 0;
    uint32_t new_top = 0;
    stack_pop(p->vertices, &top);

    if (stack_empty(p->vertices)) {
        p->total_weight = 0;
    } else {
        stack_peek(p->vertices, &new_top);
        p->total_weight -= graph_get_weight(g, new_top, top);
    }
    return top;
}

void path_copy(Path *dst, const Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->total_weight = src->total_weight;
}

void path_print(const Path *p, FILE *outfile, const Graph *g) {
    fprintf(outfile, "Alissa starts at:\n");
    stack_print(p->vertices, outfile, graph_get_names(g));
}
