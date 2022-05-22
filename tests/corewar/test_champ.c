/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** test_champ.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "op.h"
#undef exit

Test (corewar_alive, test_corewar_alive, .exit_code = 0,
.init=cr_redirect_stdout)
{
    champ_t *to_cmp = malloc(sizeof(champ_t));
    champ_t *ouais = malloc(sizeof(champ_t));
    champ_t *test = NULL;
    char *map = malloc(sizeof(char) * (MEM_SIZE + 1));
    my_memset(map, 0, MEM_SIZE);
    my_memset(to_cmp, 0, sizeof(champ_t));
    my_memset(ouais, 1, sizeof(champ_t));
    ouais->next = to_cmp;

    cr_assert(last_to_live(test) == test);
    cr_assert(last_to_live(to_cmp) == to_cmp);
    ouais->is_alive = 0;
    check_alive_champ(&ouais, -1, map);
}

Test (corewar_alive_champ, test_corewar_alive_champ, .exit_code = 0,
.init=cr_redirect_stdout)
{
    champ_t *to_cmp = malloc(sizeof(champ_t));
    champ_t *ouais = malloc(sizeof(champ_t));
    char *map = malloc(sizeof(char) * (MEM_SIZE + 1));
    my_memset(map, 0, MEM_SIZE);
    my_memset(to_cmp, 0, sizeof(champ_t));

    ouais->next = to_cmp;
    to_cmp->next = NULL;
    ouais->is_alive = 1;

    last_to_live(ouais);
    check_alive_champ(&ouais, 0, map);
}

Test (glob_var, test_glob_var, .init=cr_redirect_stdout)
{
    int cmp = CYCLE_TO_DIE;
    champ_t *to_cmp = NULL;

    cr_assert(*get_cycle_to_die() == cmp);
    cr_assert(*get_champ_struct() == to_cmp);
}

Test (check_endian_convertor, test_check_endian_convertor,
.init=cr_redirect_stdout)
{
    int test = 0x12345678;

    convert_endian(&test);
    cr_assert(test == 0x78563412);
    convert_endian(&test);
    cr_assert(test == 0x12345678);
}

Test (check_short_endian_convertor, test_check_short_endian_convertor,
.init=cr_redirect_stdout)
{
    short test = 0x1234;

    convert_endian_short(&test);
    cr_assert(test == 0x3412);
    convert_endian_short(&test);
    cr_assert(test == 0x1234);
}
