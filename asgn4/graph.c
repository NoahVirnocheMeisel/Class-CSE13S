#include "graph.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct graph {
    uint32_t vertices;
    bool directed;
    bool *visited;
    char **names;
    uint32_t **weights;
};

Graph *graph_create(uint32_t vertices, bool directed) {
    Graph *g = calloc(1, sizeof(Graph));
    g->vertices = vertices;
    g->directed = directed;
    g->visited = calloc(vertices, sizeof(bool));
    g->names = calloc(vertices, sizeof(char *));
    g->weights = calloc(vertices, sizeof(g->weights[0]));

    for (uint32_t i = 0; i < vertices; ++i) {
        g->weights[i] = calloc(vertices, sizeof(g->weights[0][0]));
    }
    return g;
}
//graph_free run off the model given for stack_free. Assume it works similarly
void graph_free(Graph **gp) {
    if (gp != NULL && *gp != NULL) {
        if ((*gp)->visited) {
            free((*gp)->visited);
            (*gp)->visited = NULL;
        }
        if ((*gp)->names) {
            for (uint32_t i = 0; i < (*gp)->vertices; i++) {
                free((*gp)->names[i]);
            }
            free((*gp)->names);
            (*gp)->names = NULL;
        }
        if ((*gp)->weights) {
            for (uint32_t i = 0; i < (*gp)->vertices; i++) {
                free((*gp)->weights[i]);
            }
            free((*gp)->weights);
            (*gp)->weights = NULL;
        }
        free(*gp);
    }
    if (gp != NULL) {
        *gp = NULL;
    }
}

uint32_t graph_vertices(const Graph *g) {
    return g->vertices;
}

void graph_add_vertex(Graph *g, const char *name, uint32_t v) {
    if (g->names[v]) {
        free(g->names[v]);
    }

    g->names[v] = strdup(name);
}

const char *graph_get_vertex_name(const Graph *g, uint32_t v) {
    return g->names[v];
}

char **graph_get_names(const Graph *g) {
    return g->names;
}

void graph_add_edge(Graph *g, uint32_t start, uint32_t end, uint32_t weight) {
    g->weights[start][end] = weight;
}

uint32_t graph_get_weight(const Graph *g, uint32_t start, uint32_t end) {
    uint32_t weight1, weight2;
    if (g->directed) {
        return g->weights[start][end];
    } else {
        weight1 = g->weights[start][end];
        weight2 = g->weights[end][start];
        if (weight1 > weight2) {
            return weight1;

        } else {
            return weight2;
        }
    }
}

void graph_visit_vertex(Graph *g, uint32_t v) {
    g->visited[v] = true;
}

void graph_unvisit_vertex(Graph *g, uint32_t v) {
    g->visited[v] = false;
}
bool graph_visited(const Graph *g, uint32_t v) {
    return g->visited[v];
}

void graph_print(const Graph *g) {
    for (uint32_t i = 0; i < graph_vertices(g); i++) {
        for (uint32_t b = 0; b < graph_vertices(g); b++) {
            if (graph_get_weight(g, i, b)) {
                printf("%s --> ", g->names[i]);
                printf(" %d ", graph_get_weight(g, i, b));
                printf("%s\n", g->names[b]);
            }
        }
    }
}
