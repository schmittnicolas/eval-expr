#include "evalexpr.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    // rpn is set to 1 if the program is called with -rpn, 0 otherwise.
    int rpn = 0;
    if (argc > 2)
        return 4;

    if (argc == 2)
    {
        if (strcmp(argv[1], "-rpn") == 0)
        {
            rpn = 1;
        }
        else
        {
            return 4;
        }
    }

    // Get the expression.
    char *line = NULL;
    size_t len = 0;
    ssize_t read = getline(&line, &len, stdin);
    if (read == -1)
        return -1;

    if (read == 0)
        return 0;

    // Evaluate the expression.
    int res = eval_expr(line, rpn);
    return res;
}
