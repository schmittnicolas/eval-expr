#include "evalexpr.h"

#include <stdio.h>

int is_operator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%'
            || c == '(' || c == ')');
}

int is_digit(char c)
{
    return ('0' <= c && c <= '9');
}

int precedence(int op)
{
    switch (op)
    {
    case '^':
        return 4;
    case '*':
        return 3;
    case '/':
        return 3;
    case '-':
        return 2;
    case '+':
        return 2;
    default:
        return 0;
    }
}

int get_token(char *expr, int i, struct token *token)
{
    while (isspace(expr[i]))
        i++;

    if (is_digit(expr[i]))
    {
        token->is_op = 0;
        token->value = 0;
        while (is_digit(expr[i]))
        {
            token->value = token->value * 10 + (expr[i] - '0');
            i++;
        }
    }
    else if (is_operator(expr[i]))
    {
        token->is_op = 1;
        token->value = expr[i];
        i++;
    }
    else if (expr[i] == '\n' || expr[i] == '\0')
    {
        return 0;
    }
    else
    {
        return -1;
    }

    return i;
}

int my_pow(int a, int b)
{
    if (b == 0)
        return 1;

    if (b == 1)
        return a;

    if (b % 2 == 0)
        return my_pow(a, b / 2) * my_pow(a, b / 2);
    return a * my_pow(a, b - 1);
}

// Return 1 if errors, 0 otherwise
int evaluate_errors(int b, char op)
{
    if (op == '/' && b == 0)
        return 1;
    if (op == '%' && b == 0)
        return 1;
    return 0;
}

int evaluate(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return my_pow(a, b);
    case '%':
        return a % b;
    default:
        return 0;
    }
}

int compute_the_output(struct fifo *output)
{
    // Compute the result.
    int res;
    struct stack *stack = NULL;
    while (fifo_size(output) > 0)
    {
        // Pop the queue and get the value
        struct token tok = fifo_head(output);
        fifo_pop(output);

        if (is_op(tok))
        {
            if (stack == NULL)
            {
                fifo_destroy(output);
                return 2;
            }
            int rhs = stack_peek(stack);
            stack = stack_pop(stack);
            if (stack == NULL)
            {
                fifo_destroy(output);
                return 2;
            }
            int lhs = stack_peek(stack);
            stack = stack_pop(stack);

            if (evaluate_errors(rhs, get_token_value(tok)))
            {
                while (stack != NULL)
                    stack = stack_pop(stack);
                fifo_destroy(output);
                return 3;
            }

            res = evaluate(lhs, rhs, get_token_value(tok));
            stack = stack_push(stack, res);
        }
        else
        {
            int elt = get_token_value(tok);
            stack = stack_push(stack, elt);
        }
    }

    res = stack_peek(stack);
    stack = stack_pop(stack);

    int err = 0;
    if (stack != NULL)
        err = 2;
    while (stack != NULL)
        stack = stack_pop(stack);
    fifo_destroy(output);

    if (err == 2)
        return 2;

    printf("%d\n", res);
    return err;
}

int eval_rpn(char *expr)
{
    struct stack *stack = NULL;
    struct token token;
    int res;
    int i = 0;

    while ((i = get_token(expr, i, &token)) != 0)
    {
        if (i == -1)
        {
            while (stack != NULL)
                stack = stack_pop(stack);
            return 1;
        }

        if (is_op(token))
        {
            if (stack == NULL)
                return 2;
            int rhs = stack_peek(stack);
            stack = stack_pop(stack);
            if (stack == NULL)
                return 2;
            int lhs = stack_peek(stack);
            stack = stack_pop(stack);

            if (evaluate_errors(rhs, get_token_value(token)))
            {
                while (stack)
                    stack = stack_pop(stack);
                return 3;
            }
            res = evaluate(lhs, rhs, get_token_value(token));
            stack = stack_push(stack, res);
        }
        else
        {
            int elt = get_token_value(token);
            stack = stack_push(stack, elt);
        }
    }

    res = stack_peek(stack);
    stack = stack_pop(stack);

    int err = 0;
    if (stack != NULL)
        err = 2;
    while (stack != NULL)
        stack = stack_pop(stack);

    if (err == 2)
        return 2;
    printf("%d\n", res);
    return 0;
}

int eval_std(char *expr)
{
    struct token token;
    struct fifo *output = fifo_init();
    struct stack *ops = NULL;

    int i = 0;

    // Shunting Yard Algorithm
    while ((i = get_token(expr, i, &token)) != 0)
    {
        if (i == -1)
        {
            fifo_destroy(output);
            while (ops != NULL)
                ops = stack_pop(ops);
            return 1;
        }

        if (is_op(token)) // Operator
        {
            char op = get_token_value(token);

            if (op == '(') // Left parenthesis
            {
                ops = stack_push(ops, op);
            }
            else if (op == ')') // Right parenthesis
            {
                while (ops != NULL && stack_peek(ops) != '(')
                {
                    // Pop o1 from the operator stacks.
                    int op1 = stack_peek(ops);
                    ops = stack_pop(ops);

                    // Push o1 in the output queue.
                    fifo_push(output, op1, 1);
                }
                if (ops != NULL && stack_peek(ops) == '(')
                    ops = stack_pop(ops);
            }
            else // "+" or  "-" or "*" or "/" or "^" or "%"
            {
                int op1 = get_token_value(token);
                if (ops != NULL)
                {
                    int op2 = stack_peek(ops);
                    while ((ops != NULL && op2 != '(')
                           && (precedence(op2) > precedence(op1)
                               || (precedence(op2) == precedence(op1)
                                   && op1 != '^')))
                    {
                        // Pop o2 from the operator stacks.
                        op2 = stack_peek(ops);
                        ops = stack_pop(ops);

                        // Push o2 in the output queue.
                        fifo_push(output, op2, 1);
                    }
                }
                // Push o1 onto the operator stack
                ops = stack_push(ops, op1);
            }
        }
        else // Number
        {
            int n = get_token_value(token);
            fifo_push(output, n, 0);
        }
    }

    // Pop the remaining operators into the output queue.
    while (ops != NULL)
    {
        char op = stack_peek(ops);
        ops = stack_pop(ops);
        if (op != '(')
        fifo_push(output, op, 1);
    }
    free(ops);

    // Compute the ouput;
    int res = compute_the_output(output);
    if (res == 3)
        return 3;
    if (res == 2)
        return 2;
    return 0;
}

int eval_expr(char *expr, int rpn)
{
    if (expr == NULL)
        return 0;
    int res;
    if (rpn)
    {
        res = eval_rpn(expr);
    }
    else
    {
        res = eval_std(expr);
    }

    return res;
}
