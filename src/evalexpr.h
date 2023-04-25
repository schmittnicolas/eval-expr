#ifndef EVALEXPR_H
#define EVALEXPR_H

#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>

#include "stack.h"
#include "fifo.h"

int eval_expr(char *expr, int rpn);

#endif
