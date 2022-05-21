/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** test_quentin.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "corewar.h"

Test (i_live, i_live, .init=cr_redirect_stdout)
{
    champ_t *champ1 = malloc(sizeof(champ_t));
    champ_t *champ2 = malloc(sizeof(champ_t));

    champ1->next = champ2;
    champ1->is_alive = 0;
    champ1->param.champ_nbr = 3;

    champ2->param.champ_nbr = 5;
    champ2->is_alive = 0;
    champ2->next = NULL;
    my_strcpy(champ2->header.prog_name, "yolo");

    all_champs(&champ1);
    cr_assert(i_live((int [3]){5, 0, 0}, champ1, NULL) == 0);
    cr_assert(i_live((int [3]){9, 0, 0}, champ1, NULL) == 0);
}

Test (zjmp, zjmp)
{
    champ_t *champ1 = malloc(sizeof(champ_t));

    champ1->carry = 0;
    i_zjmp(NULL, champ1, NULL);
    champ1->carry = 1;
    champ1->pc = 10;
    champ1->args.byte_offset = 12;
    i_zjmp((int [3]){3, 0, 0}, champ1, NULL);
    cr_assert(champ1->pc == 1);
    i_zjmp((int [3]){3000, 0, 0}, champ1, NULL);
    cr_assert(champ1->pc == 1 + 3000%512 - 12);
}

Test (aff, aff)
{
    champ_t *c = malloc(sizeof(champ_t));

    c->registers[0] = 8;
    i_aff((int [3]){0, 0, 0}, c, NULL);
}

Test (fork, fork)
{
    champ_t *c = malloc(sizeof(champ_t));

    c->pc = 0;
    i_fork((int [3]){-1000}, c, NULL);
    i_lfork((int [3]){-1000}, c, NULL);

    cr_assert((*fork_list())->pc = -1000);
    cr_assert((*fork_list())->cycle == 0);
    cr_assert((*fork_list())->is_alive == 0);
    cr_assert((*fork_list())->cycle_to_wait == -1);
}

Test (add, add)
{
    champ_t *c = malloc(sizeof(champ_t));

    c->registers[0] = 1;
    c->registers[1] = 2;
    c->registers[3] = 69;
    c->carry = 1;

    i_add((int [3]){0, 1, 3}, c, NULL);
    cr_assert(c->registers[0] == 1);
    cr_assert(c->registers[1] == 2);
    cr_assert(c->registers[3] == 3);
    cr_assert(c->carry == 0);

    i_sub((int [3]){0, 1, 3}, c, NULL);
    cr_assert(c->registers[0] == 1);
    cr_assert(c->registers[1] == 2);
    cr_assert(c->registers[3] == -1);
    cr_assert(c->carry == 0);

    c->registers[1] = -1;

    i_add((int [3]){0, 1, 3}, c, NULL);
    cr_assert(c->registers[0] == 1);
    cr_assert(c->registers[1] == -1);
    cr_assert(c->registers[3] == 0);
    cr_assert(c->carry == 1);
}

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

Test (or, or)
{
    champ_t *c = malloc(sizeof(champ_t));
    int arg[3] = {0, 1, 2};

    c->registers[0] = 13;
    c->registers[1] = 69;
    c->registers[2] = 0;
    c->args.type[0] = T_REG;
    c->args.type[1] = T_REG;

    i_or(arg, c, NULL);
    cr_assert(c->registers[2] == (13 | 69));

    arg[1] = 22;
    c->args.type[1] = T_IND;
    i_or(arg, c, NULL);
    cr_assert(c->registers[2] == (22 | 13));

    arg[0] = 69;
    c->args.type[0] = T_IND;
    i_or(arg, c, NULL);
    cr_assert(c->registers[2] == (22 | 69));
}

Test (xor, xor)
{
    champ_t *c = malloc(sizeof(champ_t));
    int arg[3] = {0, 1, 2};

    c->registers[0] = 13;
    c->registers[1] = 69;
    c->registers[2] = 0;
    c->args.type[0] = T_REG;
    c->args.type[1] = T_REG;

    i_xor(arg, c, NULL);
    cr_assert(c->registers[2] == (13 ^ 69));

    arg[1] = 22;
    c->args.type[1] = T_IND;
    i_xor(arg, c, NULL);
    cr_assert(c->registers[2] == (22 ^ 13));

    arg[0] = 69;
    c->args.type[0] = T_IND;
    i_xor(arg, c, NULL);
    cr_assert(c->registers[2] == (22 ^ 69));
}
