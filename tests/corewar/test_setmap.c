/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** test_setmap.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "op.h"
#undef exit

Test (check_set_map_func, test_set_map_, .init=cr_redirect_stdout)
{
    champ_t *champ = malloc(sizeof(champ_t));
    char *map = NULL;

    my_memset(champ, 0, sizeof(champ_t));
    champ->instruction = malloc(sizeof(char) * 20);
    my_memset(champ->instruction, 0, sizeof(char) * 20);
    champ->param.champ_nbr = 2;
    champ->header.prog_size = 4;
    champ->next = NULL;
    champ->instruction[0] = 4;
    champ->instruction[1] = 0b01010100;
    champ->instruction[2] = 1;
    champ->instruction[3] = 3;
    champ->instruction[4] = 6;
    map = set_map(&champ, map);
    cr_assert(map[0] = 4);
    cr_assert(map[1] = 0b01010100);
    cr_assert(map[2] = 1);
    cr_assert(map[3] = 3);
    cr_assert(map[4] = 6);
}

Test (check_set_map_func_err, test_set_map_err, .init=cr_redirect_stderr,
.exit_code = 84)
{
    champ_t *champ = malloc(sizeof(champ_t));
    champ_t *champ2 = malloc(sizeof(champ_t));
    char *map = NULL;

    my_memset(champ, 0, sizeof(champ_t));
    my_memset(champ2, 0, sizeof(champ_t));
    champ->instruction = malloc(sizeof(char) * 20);
    champ2->instruction = malloc(sizeof(char) * 20);
    my_memset(champ->instruction, 0, sizeof(char) * 20);
    my_memset(champ2->instruction, 0, sizeof(char) * 20);
    champ->header.prog_size = 4;
    champ2->header.prog_size = 4;
    champ->param.champ_nbr = 2;
    champ2->param.champ_nbr = 1;
    champ->next = champ2;
    champ2->next = NULL;
    champ->instruction[0] = 4;
    champ->instruction[1] = 0b01010100;
    champ->instruction[2] = 1;
    champ->instruction[3] = 3;
    champ->instruction[4] = 6;
    champ2->instruction[0] = 4;
    champ2->instruction[1] = 0b01010100;
    champ2->instruction[2] = 1;
    champ2->instruction[3] = 3;
    champ2->instruction[4] = 6;
    champ2->param.adress = 0;
    champ2->param.adress_impose = 1;
    champ->param.adress = 0;
    champ->param.adress_impose = 1;
    map = set_map(&champ, map);
}
