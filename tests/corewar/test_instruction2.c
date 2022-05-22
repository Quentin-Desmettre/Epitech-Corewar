/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** test_instruction2.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "corewar.h"

Test (st, st)
{
    char *arena = malloc(sizeof(char) * 10);
    champ_t *c = malloc(sizeof(champ_t));

    c->pc = 0;
    c->registers[0] = 69;
    c->registers[1] = 96;
    c->args.type[1] = T_REG;
    memset(arena, 0, sizeof(char) * 10);
    i_st((int[3]){0, 1}, c, NULL);
    cr_assert(c->registers[1] == 69);
    c->args.type[1] = T_IND;
    i_st((int[3]){0, 1}, c, arena);

    int checker = *((int *)(arena + 1));

    convert_endian(&checker);
    cr_assert(checker == 69);
}

Test (sti, sti)
{
    char *arena = malloc(sizeof(char) * 10);
    champ_t *c = malloc(sizeof(champ_t));

    c->pc = 0;
    c->registers[0] = 69;
    c->args.tmp_ldi = 6;
    memset(arena, 0, sizeof(char) * 10);

    i_sti((int[3]){0}, c, arena);

    int check = *((int *)(arena + 6));
    cr_assert(check == 0x45000000);
}

Test (load, load)
{
    int arg[3] = {0, 1};
    champ_t *c = malloc(sizeof(champ_t));

    c->registers[0] = 0;
    c->registers[1] = 1;
    i_ld(arg, c, NULL);
    cr_assert(c->carry == 1 && c->registers[1] == 0);
    arg[0] = 2;
    i_lld(arg, c, NULL);
    cr_assert(c->carry == 0);
    cr_assert(c->registers[1] == 2);
}

Test (load_index, load_index)
{
    int arg[3] = {0, 1, 3};
    champ_t *c = malloc(sizeof(champ_t));

    c->registers[3] = 60;
    c->args.tmp_ldi = 13;
    i_ldi(arg, c, NULL);
    cr_assert(c->carry == 0 && c->registers[3] == 13);
    c->args.tmp_ldi = 0;
    i_lldi(arg, c, NULL);
    cr_assert(c->carry == 1);
    cr_assert(c->registers[3] == 0);
}

Test (and, and)
{
    champ_t *c = malloc(sizeof(champ_t));
    int arg[3] = {0, 1, 2};

    c->registers[0] = 13;
    c->registers[1] = 69;
    c->registers[2] = 0;
    c->args.type[0] = T_REG;
    c->args.type[1] = T_REG;

    i_and(arg, c, NULL);
    cr_assert(c->registers[2] == (13 & 69), "actual = %d.\n", c->registers[2]);

    arg[1] = 22;
    c->args.type[1] = T_IND;
    i_and(arg, c, NULL);
    cr_assert(c->registers[2] == (22 & 13));

    arg[0] = 69;
    c->args.type[0] = T_IND;
    i_and(arg, c, NULL);
    cr_assert(c->registers[2] == (22 & 69));
}
