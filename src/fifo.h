#ifndef FIFO_H
#define FIFO_H

#include <stddef.h>

struct token
{
    int is_op;
    int value;
};

struct list
{
    struct token data;
    struct list *next;
};

struct fifo
{
    struct list *head;
    struct list *tail;
    size_t size;
};

struct fifo *fifo_init(void);
int get_token_value(struct token t);
int is_op(struct token t);
size_t fifo_size(struct fifo *fifo);
void fifo_push(struct fifo *fifo, int elt, int is_op);
struct token fifo_head(struct fifo *fifo);
void fifo_pop(struct fifo *fifo);
void fifo_clear(struct fifo *fifo);
void fifo_destroy(struct fifo *fifo);
void fifo_print(const struct fifo *fifo);

#endif /* !FIFO_H */
