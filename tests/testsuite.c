#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../src/evalexpr.h"

#define RPN_ON 1
#define RPN_OFF 0


void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

//Basic Standard notation
Test(Basic, add1_wspace, .init = redirect_all_stdout)
{
    char expr[100] = "27 + 18";
    eval_expr(expr, RPN_OFF);
    fflush(stdout);
    cr_assert_stdout_eq_str("45\n");
}

Test(Basic, addmany_wspace, .init = redirect_all_stdout)
{
    char expr[100] = "3 + 4 + 7";
    eval_expr(expr, RPN_OFF);
    fflush(stdout);
    cr_assert_stdout_eq_str("14\n");
}

Test(Basic, add1, .init = redirect_all_stdout)
{
    char expr[100] = "27+18";
    eval_expr(expr, RPN_OFF);
    fflush(stdout);
    cr_assert_stdout_eq_str("45\n");
}

Test(Basic, addmany, .init = redirect_all_stdout)
{
    char expr[100] = "3+4+7";
    eval_expr(expr, RPN_OFF);
    fflush(stdout);
    cr_assert_stdout_eq_str("14\n");
}

Test(Basic, mult, .init = redirect_all_stdout)
{
    char expr[100] = "3 * 4";
    eval_expr(expr, RPN_OFF);
    fflush(stdout);
    cr_assert_stdout_eq_str("12\n");
}

Test(Basic, mult_many, .init = redirect_all_stdout)
{
    char expr[100] = "3*4*2";
    eval_expr(expr, RPN_OFF);
    fflush(stdout);
    cr_assert_stdout_eq_str("24\n");
}


Test(Basic, mult_many_wspace, .init = redirect_all_stdout)
{
    char expr[100] = "3 * 4  * 2";
    eval_expr(expr, RPN_OFF);
    fflush(stdout);
    cr_assert_stdout_eq_str("24\n");
}

Test(Basic, div, .init = redirect_all_stdout)
{
    char expr[100] = "4/2";
    eval_expr(expr, RPN_OFF);
    fflush(stdout);
    cr_assert_stdout_eq_str("2\n");
}


Test(Basic, div_wspace, .init = redirect_all_stdout)
{
    char expr[100] = "4 / 2";
    eval_expr(expr, RPN_OFF);
    fflush(stdout);
    cr_assert_stdout_eq_str("2\n");
}

Test(Basic, divmany, .init = redirect_all_stdout)
{
    char expr[100] = "4/2/2";
    eval_expr(expr, RPN_OFF);
    fflush(stdout);
    cr_assert_stdout_eq_str("1\n");
}

// Cannot test empty output with criterion
Test(Basic, div_zero, .init = redirect_all_stdout)
{
    char expr[100] = "1/0";
    eval_expr(expr, RPN_OFF);
    fflush(stdout);
    cr_assert_stdout_eq_str("");
}

Test(Basic, sub, .init = redirect_all_stdout)
{
    char expr[100] = "4-2";
    eval_expr(expr, RPN_OFF);
    fflush(stdout);
    cr_assert_stdout_eq_str("2\n");
}
Test(Basic, submany, .init = redirect_all_stdout)
{
    char expr[100] = "4-2-2";
    eval_expr(expr, RPN_OFF);
    fflush(stdout);
    cr_assert_stdout_eq_str("0\n");
}

Test(Basic, sub_wspace, .init = redirect_all_stdout)
{
    char expr[100] = "4 - 2 - 2";
    eval_expr(expr, RPN_OFF);
    fflush(stdout);
    cr_assert_stdout_eq_str("0\n");
}

Test(Basic, mod, .init = redirect_all_stdout)
{
    char expr[100] = "12%4";
    eval_expr(expr, RPN_OFF);
    fflush(stdout);
    cr_assert_stdout_eq_str("0\n");
}


Test(Basic, mod_wspace, .init = redirect_all_stdout)
{
    char expr[100] = "12 % 4";
    eval_expr(expr, RPN_OFF);
    fflush(stdout);
    cr_assert_stdout_eq_str("0\n");
}

Test(Basic, parenthesis1, .init = redirect_all_stdout)
{
    char expr[100] = "(3 + 4) * 2";
    eval_expr(expr, RPN_OFF);
    fflush(stdout);
    cr_assert_stdout_eq_str("14\n");
}

Test(Basic, add1_wspace_rpn, .init = redirect_all_stdout)
{
    char expr[100] = "18 27 +";
    eval_expr(expr, RPN_ON);
    fflush(stdout);
    cr_assert_stdout_eq_str("45\n");
}

Test(Basic, addmany_wspace_rpn, .init = redirect_all_stdout)
{
    char expr[100] = "3 4 + 7 +";
    eval_expr(expr, RPN_ON);
    fflush(stdout);
    cr_assert_stdout_eq_str("14\n");
}

Test(Basic, add1_rpn, .init = redirect_all_stdout)
{
    char expr[100] = "27 18 +";
    eval_expr(expr, RPN_ON);
    fflush(stdout);
    cr_assert_stdout_eq_str("45\n");
}

Test(Basic, mult_rpn, .init = redirect_all_stdout)
{
    char expr[100] = "3 4 *";
    eval_expr(expr, RPN_ON);
    fflush(stdout);
    cr_assert_stdout_eq_str("12\n");
}

Test(Basic, mult_many_rpn, .init = redirect_all_stdout)
{
    char expr[100] = "3 4 * 2 *";
    eval_expr(expr, RPN_ON);
    fflush(stdout);
    cr_assert_stdout_eq_str("24\n");
}


Test(Basic, mult_many_wspace_rpn, .init = redirect_all_stdout)
{
    char expr[100] = "3 4  * 2 *";
    eval_expr(expr, RPN_ON);
    fflush(stdout);
    cr_assert_stdout_eq_str("24\n");
}

Test(Basic, div_rpn, .init = redirect_all_stdout)
{
    char expr[100] = "4 2 /";
    eval_expr(expr, RPN_ON);
    fflush(stdout);
    cr_assert_stdout_eq_str("2\n");
}


Test(Basic, div_wspace_rpn, .init = redirect_all_stdout)
{
    char expr[100] = "4 2 /";
    eval_expr(expr, RPN_ON);
    fflush(stdout);
    cr_assert_stdout_eq_str("2\n");
}

Test(Basic, divmany_rpn, .init = redirect_all_stdout)
{
    char expr[100] = "4 2 / 2 /";
    eval_expr(expr, RPN_ON);
    fflush(stdout);
    cr_assert_stdout_eq_str("1\n");
}

// Cannot test empty output with criterion
Test(Basic, div_zero_rpn, .init = redirect_all_stdout)
{
    char expr[100] = "1 0 /";
    eval_expr(expr, RPN_ON);
    fflush(stdout);
    cr_assert_stdout_eq_str("");
}


Test(Basic, sub_rpn, .init = redirect_all_stdout)
{
    char expr[100] = "4 2 -";
    eval_expr(expr, RPN_ON);
    fflush(stdout);
    cr_assert_stdout_eq_str("2\n");
}

