/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** test_check_command.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <wait.h>
#include "asm.h"

Test (check_command, check_command)
{
    char *args[] = {
        ".comment",
        NULL
    };
    char *err_mess;

    cr_assert(check_command(args, &err_mess) == 0);
    cr_assert_str_eq(err_mess, "Invalid op code");

    char *args2[] = {
        "live",
        "r3",
        "r4",
        NULL
    };
    cr_assert(check_command(args2, &err_mess) == 0);

    char *args3[] = {
        "live",
        "r2",
        NULL
    };
    cr_assert(check_command(args3, &err_mess) == 0);

    char *args4[] = {
        "live",
        "%234",
        NULL
    };
    cr_assert(check_command(args4, &err_mess) == 1);

    char *args5[] = {
        "live",
        "234",
        NULL
    };
    cr_assert(check_command(args5, &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Incompatible argument type");

}

Test (is_label_valid, is_label_valid)
{
    cr_assert(is_label_valid("") == 0);
    cr_assert(is_label_valid("a") == 0);
    cr_assert(is_label_valid("::") == 0);
    cr_assert(is_label_valid("é:") == 0);
    cr_assert(is_label_valid("e:") == 1);
}
