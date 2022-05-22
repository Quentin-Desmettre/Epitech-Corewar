/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** test_check_num.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "op.h"
#undef exit

Test (check_no_arg_num, test_check_no_arg_num, .exit_code = 84,
.init=cr_redirect_stderr)
{
    check_num(NULL, NULL);
}

Test (check_num_specifie, test_check_num_specifie, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    param->num_impose[0] = 10;
    check_num(param, "50");
}

Test (check_bad_num_impose, test_check_bad_num_impose, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    check_num(param, "-50");
}

Test (check_bad_alpha_impose, test_check_bad_alpha_impose, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    check_num(param, "78163761978635967153967153");
}

Test (check_nice_num, test_check_nice_num, .init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    check_num(param, "3");
    cr_assert(param->num_impose[0] == 3);
}
