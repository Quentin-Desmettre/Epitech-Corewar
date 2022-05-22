/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** test_check_adress.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "op.h"
#undef exit

Test (check_no_arg_adress, test_check_no_arg_adress, .exit_code = 84,
.init=cr_redirect_stderr)
{
    check_address(NULL, NULL);
}

Test (check_adress_specifie, test_check_adress_specifie, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    param->adress_next = 10;
    check_address(param, "50");
}

Test (check_bad_adress_impose, test_check_bad_adress_impose, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    param->adress_next = -1;
    check_address(param, "-50");
}

Test (check_alpha_adress_impose, test_check_alpha_adress_impo, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    param->adress_next = -1;
    check_address(param, "78163761978635967153967153");
}

Test (check_nice_adress, test_check_nice_adress, .init=cr_redirect_stdout)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    param->adress_next = -1;
    check_address(param, "3");
    cr_assert(param->adress_next == 3);
}
