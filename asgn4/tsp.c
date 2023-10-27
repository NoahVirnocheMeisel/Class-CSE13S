#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <stdio.h>
#include <stdlib.h>
#define OPTIONS "i:o:dh"
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char **argv) {
    uint32_t dfs(Path * p, Graph * g, uint32_t node, Path * best_path);
    bool info = false;
    int opt = 0;
    bool directed = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            if (infile != stdin) {
                fclose(infile);
            }
            infile = fopen(optarg, "r");
            break;
        case 'o':
            if (outfile != stdout) {
                fclose(outfile);
            }
            outfile = fopen(optarg, "w");
            break;
        case 'd': directed = true; break;

        case 'h':
            info = true;
            fprintf(stdout,
                "-i filename: specifies a file to read the graph from. Defaults to stdin.\n-o "
                "filename: specifies a file to write to. Defaults to stdout.\n -d: Specifies "
                "the graph is directed. Defaults is undirected.\n -h: prints a help "
                "message(this message) to stdout\n");
        }
    }

    //Uses fscanf anf fgets to read data from a file to store in the graph.
    //First reads # of vertices, then uses fgets in a for loop to read the names into the graph. Uses scanf again after to get the number of edges, before using another for loop to read the 3 values on each line into 3 temp variables that are passed in to the add_edge function.
    Path *main = path_create(100);
    Path *best = path_create(100);
    uint32_t vertices;
    char *name = calloc(20, sizeof(char *));
    if (infile != NULL && info == false) {
        fscanf(infile, "%u\n", &vertices);
        Graph *system = graph_create(vertices, directed);
        for (uint32_t i = 0; i < vertices; i++) {
            fgets(name, 1024, infile);
            name[strlen(name) - 1] = '\0';
            graph_add_vertex(system, name, i);
        }
        uint32_t v1, v2, weight;
        fscanf(infile, "%u\n", &vertices);
        for (uint32_t i = 0; i < vertices; i++) {
            fscanf(infile, "%u", &v1);
            fscanf(infile, "%u", &v2);
            fscanf(infile, "%u", &weight);
            graph_add_edge(system, v1, v2, weight);
        }
        fclose(infile);

        dfs(main, system, START_VERTEX, best);
        uint32_t end_node = path_remove(best, system);
        path_add(best, end_node, system);
        if (graph_get_weight(system, end_node, START_VERTEX)) {
            path_add(best, START_VERTEX, system);
            path_print(best, outfile, system);
            fprintf(outfile, "Total Distance: %d\n", path_distance(best));
        } else {
            fprintf(outfile, "No path found! Alissa is lost!\n");
        }
        fclose(outfile);
        graph_free(&system);
        free(name);
        path_free(&main);
        path_free(&best);
    } else {
        if (info == false) {

            fprintf(stderr,
                "-i filename: specifies a file to read the graph from. Defaults to stdin.\n-o "
                "filename: specifies a file to write to. Defaults to stdout.\n -d: Specifies "
                "the graph is directed. Defaults is undirected.\n -h: prints a help "
                "message(this message) to stdout\n");
        }
        free(name);
        path_free(&main);
        path_free(&best);
    }
}

uint32_t dfs(Path *p, Graph *g, uint32_t node, Path *best_path) {
    //DFS: Vistits a node and adds it to the path, then visits all adjacent nodes and runs DFS on them as well. then if the current path has total_weight less than the best_path and the current path has the same number of vertices as the graph, it copies the current path into best path. Then it removes the current ndoe from the current path.After all the nodes next to the current node have been visisted, it unvisits the current node and returns the total_weight of the best_path.
    graph_visit_vertex(g, node);
    path_add(p, node, g);
    for (uint32_t i = 0; i < graph_vertices(g); i++) {
        if (graph_get_weight(g, node, i) > 0) {
            if (graph_visited(g, i) == false) {
                dfs(p, g, i, best_path);
                if (path_distance(p) < path_distance(best_path)
                    && (path_vertices(p) == graph_vertices(g))) {
                    path_copy(best_path, p);
                } else if (path_distance(best_path) == 0
                           && (path_vertices(p) == graph_vertices(g))) {
                    path_copy(best_path, p);
                }
                path_remove(p, g);
            }
        }
    }
    graph_unvisit_vertex(g, node);
    return path_distance(best_path);
}
