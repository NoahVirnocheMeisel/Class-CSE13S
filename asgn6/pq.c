#include "pq.h"

#include "io.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>

bool pq_less_than(Node *n1, Node *n2);

typedef struct ListElement ListElement;

struct ListElement {
    Node *tree;
    ListElement *next;
};
struct PriorityQueue {
    ListElement *list;
};

PriorityQueue *pq_create(void) {
    PriorityQueue *pq = calloc(1, sizeof(PriorityQueue));
    return pq;
}

void pq_free(PriorityQueue **q) {
    free(*q);
    *q = NULL;
}

bool pq_is_empty(PriorityQueue *q) {
    if (q->list == NULL) {
        return true;
    }
    return false;
}

bool pq_size_is_1(PriorityQueue *q) {
    if (pq_is_empty(q) == false) {
        if ((q->list)->next == NULL) {
            return true;
        }
    }
    return false;
}

void enqueue(PriorityQueue *q, Node *tree) {

    ListElement *e = calloc(1, sizeof(ListElement));
    //creates a new ListElement and stores tree in it/
    e->tree = tree;
    //ListElement *store = calloc(1, sizeof(ListElement));
    //creates a placeholder ListElement and sets it equal to the first element in q
    bool set = false;
    if (pq_is_empty(q)) {
        q->list = e;
    } else if (pq_less_than(e->tree, (q->list)->tree)) {
        //puts list_element into the front of the queue.
        e->next = q->list;
        q->list = e;
    } else {
        ListElement *store = (q->list);
        while ((q->list)->next != NULL) {
            if (pq_less_than(e->tree, (((q->list)->next)->tree))) {
                e->next = ((q->list)->next);
                ((q->list)->next) = e;
                set = true;
                break;
            }
            if (set == false) {
                q->list = (q->list)->next;
            }
        }
        if (set == false) {
            e->next = ((q->list)->next);
            ((q->list)->next) = e;
        }

        q->list = store;
    }

    //free(e);
    //e = NULL;
}

bool dequeue(PriorityQueue *q, Node **tree) {
    if (pq_is_empty(q)) {
        return false;
    } else {
        ListElement *e = q->list;
        q->list = q->list->next;
        *tree = e->tree;
        free(e);
        return true;
    }
}

//prints a queue. taken from asgn6 doc.
void pq_print(PriorityQueue *q) {
    assert(q != NULL);
    ListElement *e = q->list;
    int position = 1;
    while (e != NULL) {
        if (position++ == 1) {
            printf("=============================================\n");
        } else {
            printf("---------------------------------------------\n");
        }
        node_print_tree(e->tree, '<', 2);
        e = e->next;
    }
    printf("=============================================\n");
}

bool pq_less_than(Node *n1, Node *n2) {
    if ((n1->weight) < (n2->weight)) {
        return true;
    }
    if ((n1->weight) > (n2->weight)) {
        return false;
    }
    return (n1->symbol) < (n2->symbol);
}
