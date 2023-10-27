#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct stack {
    uint32_t capacity;
    uint32_t top;
    uint32_t *items;
} Stack;

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->capacity = capacity;
    s->top = 0;

    s->items = calloc(s->capacity, sizeof(uint32_t));

    return s;
}

void stack_free(Stack **sp) {
    if (sp != NULL && *sp != NULL) {
        if ((*sp)->items) {
            free((*sp)->items);
            (*sp)->items = NULL;
        }
        free(*sp);
    }
    if (sp != NULL) {
        *sp = NULL;
    }
}

bool stack_push(Stack *s, uint32_t val) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = val;
    s->top++;
    return true;
}

bool stack_pop(Stack *s, uint32_t *val) {
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *val = s->items[s->top];
    return true;
}

bool stack_peek(const Stack *s, uint32_t *val) {
    if (stack_empty(s)) {
        return false;
    }
    *val = s->items[(s->top) - 1];
    return true;
}

bool stack_empty(const Stack *s) {
    if (s->top == 0) {
        return true;
    }
    return false;
}
bool stack_full(const Stack *s) {
    if (s->top >= s->capacity) {
        return true;
    }
    return false;
}
uint32_t stack_size(const Stack *s) {
    return ((s->top));
}

void stack_copy(Stack *dst, const Stack *src) {
    uint32_t index = 0;
    dst->top = 0;
    if (dst->capacity >= src->capacity) {
        while (dst->top < src->top) {
            dst->items[dst->top] = src->items[index];
            dst->top++;
            index++;
        }
    }
}

void stack_print(const Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i++) {
        fprintf(outfile, "%s\n", cities[s->items[i]]);
    }
}
