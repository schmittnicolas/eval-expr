#include <stdio.h>
#include <stdlib.h>

#include "fifo.h"
struct fifo *fifo_init(void)
{
    struct fifo *new = malloc(sizeof(struct fifo));
    if (!new)
        return NULL;

    new->head = NULL;
    new->tail = NULL;
    new->size = 0;
    return new;
}

int get_token_value(struct token t)
{
    return t.value;
}

int is_op(struct token t)
{
    return t.is_op;
}

size_t fifo_size(struct fifo *fifo)
{
    return fifo->size;
}

struct token fifo_head(struct fifo *fifo)
{
    return fifo->head->data;
}

void fifo_pop(struct fifo *fifo)
{
    if (fifo->head == NULL)
        return;

    if (fifo->head == fifo->tail)
    {
        free(fifo->tail);
        fifo->head = NULL;
        fifo->tail = NULL;
        fifo->size = 0;
    }
    else
    {
        struct list *tmp = fifo->head;
        fifo->head = fifo->head->next;
        free(tmp);
        fifo->size--;
    }
}

void fifo_push(struct fifo *fifo, int elt, int is_op)
{
    struct list *new = malloc(sizeof(struct list));
    if (!new)
        return;

    struct token tok = { .is_op = is_op, .value = elt};
    new->data = tok;
    new->next = NULL;

    if (fifo->size == 0)
    {
        fifo->head = new;
    }
    else
    {
        fifo->tail->next = new;
    }

    fifo->tail = new;
    fifo->size++;
}

void fifo_clear(struct fifo *fifo)
{
    while (fifo->size != 0)
        fifo_pop(fifo);
}

void fifo_destroy(struct fifo *fifo)
{
    fifo_clear(fifo);
    free(fifo);
}

void fifo_print(const struct fifo *fifo)
{
    struct list *head = fifo->head;
    while (head != NULL)
    {
        printf("%d\n", head->data.value);
        head = head->next;
    }
}
