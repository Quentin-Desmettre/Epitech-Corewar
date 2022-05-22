/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** test_check_dump_args.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "op.h"
#undef exit

Test (check_dump_no_arg, test_check_dump_no_arg, .exit_code = 84,
.init=cr_redirect_stderr)
{
    check_dump(NULL, NULL);
}

Test (check_dump_already_dump, test_check_dump_already_dump, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    check_dump(param, "test");
}

Test (check_bad_dump, test_check_bad_dump, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    param->dump_cycle = -1;
    check_dump(param, "test");
}

Test (check_inf_dump, test_check_inf_dump, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    param->dump_cycle = -1;
    check_dump(param, "13527828763632867867126736");
}

Test (check_nice_dump, test_check_nice_dump, .init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    param->dump_cycle = -1;
    check_dump(param, "50");
    cr_assert(param->dump_cycle == 50);
}
