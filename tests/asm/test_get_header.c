/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** test_get_header.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <wait.h>
#include "asm.h"

Test (has_index, has_index)
{
    cr_assert(has_index("zjmp", 0) == 1);
    cr_assert(has_index("yolo", 1) == 0);
    cr_assert(has_index("ldi", 2) == 1);
    cr_assert(has_index("lldi", 2) == 1);
    cr_assert(has_index("ldi", 3) == 0);
    cr_assert(has_index("lldi", 3) == 0);
    cr_assert(has_index("sti", 1) == 0);
    cr_assert(has_index("sti", 2) == 1);
    cr_assert(has_index("fork", 0) == 1);
    cr_assert(has_index("lfork", 0) == 1);
}

Test (code_of, code_of)
{
    cr_assert(code_of("live") == 1);
    cr_assert(code_of("sti") == 11);
    cr_assert(code_of("error") == -1);
}

Test (type_of_arg, type_of_arg)
{
    char *err_mess = "yolo";

    cr_assert(type_of_arg("r4", &err_mess) == T_REG);
    cr_assert(type_of_arg("%8", &err_mess) == T_DIR);
    cr_assert(type_of_arg(":label", &err_mess) == T_IND);
    cr_assert(type_of_arg("7", &err_mess) == T_IND);

    cr_assert(type_of_arg("aa", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid indirect");

    cr_assert(type_of_arg("r0", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid register");

    cr_assert(type_of_arg("r-1", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid register");

    cr_assert(type_of_arg("r16", &err_mess) == T_REG);
    cr_assert(type_of_arg("r17", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid register");

    cr_assert(type_of_arg("r", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid register");

    cr_assert(type_of_arg("%:hi", &err_mess) == T_DIR);
    cr_assert(type_of_arg("%::hi", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid direct");

    cr_assert(type_of_arg("%89:", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid direct");

    cr_assert(type_of_arg("%:èè", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid direct");

    cr_assert(type_of_arg("%-2", &err_mess) == T_DIR);
    cr_assert(type_of_arg("%:", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid direct");

    cr_assert(type_of_arg("%", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid direct");

    cr_assert(type_of_arg(":", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid indirect");

    cr_assert(type_of_arg(":hi", &err_mess) == T_IND);
    cr_assert(type_of_arg(":", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid indirect");
    cr_assert(type_of_arg(":hi", &err_mess) == T_IND);
    cr_assert(type_of_arg("-7878", &err_mess) == T_IND);
    cr_assert(type_of_arg("--67", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid indirect");
    cr_assert(type_of_arg("::", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid indirect");
    cr_assert(type_of_arg("%-", &err_mess) == T_DIR);
    cr_assert(type_of_arg("6767", &err_mess) == T_IND);
    cr_assert(type_of_arg("-", &err_mess) == T_IND);
    cr_assert(type_of_arg("", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid argument");
}

Test (coding_byte, coding_byte)
{
    char *words[] = {
        "truc", "r2", "23", "%34", NULL
    };
    cr_assert(coding_byte_for(words) == 0x78);

    char *words2[] = {
        "truc", "23", "45", "%34", NULL
    };
    cr_assert(coding_byte_for(words2) == 0xF8);

    char *words3[] = {
        "truc", "r1", "r3", "34", NULL
    };
    cr_assert(coding_byte_for(words3) == 0x5C);
}
