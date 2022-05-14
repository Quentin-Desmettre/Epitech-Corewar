/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** test_has_error.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <wait.h>
#include "asm.h"

void redirect_stdout()
{
    cr_redirect_stderr();
}

Test (error, error, .init = redirect_stdout)
{
    FILE *f = fopen("/dev/random", "r");
    if (!f)
        return;
    cr_assert(error(f, "test", "file", 0) == 0);
    cr_assert_stderr_eq_str("file: Error on line 0. Reason: test.\n");
}

Test (get_name, get_name)
{
    cr_assert(get_name(".name \"some random name\"", 10) == NULL);
    cr_assert_str_eq(get_name(".name \"abel\"", 10), "abel");
}
