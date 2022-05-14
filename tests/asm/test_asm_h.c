/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** test_asm_h.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <wait.h>
#include "asm.h"

Test (progsize_offset, progsize_offset)
{
    header_t s;
    size_t offset = (void *)&s.prog_size - (void *)&s;

    cr_assert(progsize_offset() == offset);
}

Test (add_int16t, add_int16t)
{
    command_t *c = calloc(1, sizeof(command_t));

    add_int16t(c, 1);
    cr_assert(c->cmd_size == 2);
    cr_assert(*((int16_t *)c->params) == 1);
}

Test (add_int32t, add_int32t)
{
    command_t *c = calloc(1, sizeof(command_t));

    add_int32t(c, 1);
    cr_assert(c->cmd_size == 4);
    cr_assert(*((int32_t *)c->params) == 1);
}

Test (is_special_case, is_special_case)
{
    cr_assert(is_special_case(0) == 0);
    cr_assert(is_special_case(1) == 1);
    cr_assert(is_special_case(9) == 1);
    cr_assert(is_special_case(12) == 1);
    cr_assert(is_special_case(15) == 1);
}
