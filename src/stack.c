#include "stack.h"

#include <stddef.h>
#include <stdlib.h>
struct stack *stack_push(struct stack *s, int e)
{
    struct stack *new = malloc(sizeof(struct stack));
    new->data = e;
    new->next = s;

    return new;
}

struct stack *stack_pop(struct stack *s)
{
    if (!s)
        return NULL;

    struct stack *new = s->next;
    free(s);
    return new;
}

int stack_peek(struct stack *s)
{
    return s->data;
}
