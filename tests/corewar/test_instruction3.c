/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** test_instruction3.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "corewar.h"

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

Test (replace_indirects, replace_indirects)
{
    champ_t *c = malloc(sizeof(champ_t));
    char *arena = malloc(10);

    my_memcpy(c->args.type, (char [3]){T_REG, T_IND, T_REG}, 3);
    c->args.code = 3;
    replace_indirects(c, NULL);

    c->pc = 0;

    arena[0] = 0xaa;
    arena[1] = 0xbb;
    arena[2] = 0xcc;
    arena[3] = 0xdd;
    arena[4] = 0xee;
    arena[5] = 0xff;
    arena[6] = 0x11;
    arena[7] = 0x22;

    for (int i = 0; i < 16; i++) {
        if (i == 3 || i == 14 || i == 11 || i == 10)
            continue;
        c->args.code = i;
        c->args.args[1] = 2;
        replace_indirects(c, arena);
        cr_assert(c->args.args[1] == (int)0xccddeeff);
    }
}

Test (replace_indirects_ldi, replace_indirects_ldi)
{
    // ldi
    champ_t *c = malloc(sizeof(champ_t));
    char *arena = malloc(10);

    my_memcpy(c->args.type, (char [3]){T_REG, T_REG, T_REG}, 3);
    c->args.code = 14;
    c->args.args[0] = 0;
    c->args.args[1] = 1;
    c->pc = 0;

    c->registers[0] = 3;
    c->registers[1] = 2;


    arena[5] = 0xaa;
    arena[6] = 0xbb;
    arena[7] = 0xcc;
    arena[8] = 0xdd;
    replace_indirects(c, arena);
    cr_assert(c->args.args[0] == 3 && c->args.args[1] == 2);
    cr_assert(c->args.tmp_ldi == (int)0xaabbccdd);

    c->args.type[0] = T_IND;
    c->args.type[1] = T_DIR;
    c->args.code = 10;

    arena[3] = 0xaa;
    arena[4] = 0xbb;

    replace_indirects(c, arena);
    cr_assert(c->args.args[0] == (short)0xaabb);
}

Test (manage_sti, manage_sti)
{
    // ldi
    champ_t *c = malloc(sizeof(champ_t));
    char *arena = malloc(10);

    my_memcpy(c->args.type, (char [3]){T_REG, T_REG, T_REG}, 3);
    c->args.code = 11;
    c->args.args[1] = 0;
    c->args.args[2] = 1;
    c->pc = 0;

    c->registers[0] = 3;
    c->registers[1] = 2;


    arena[5] = 0xaa;
    arena[6] = 0xbb;
    arena[7] = 0xcc;
    arena[8] = 0xdd;
    replace_indirects(c, arena);
    cr_assert(c->args.args[1] == 3 && c->args.args[2] == 2);
    cr_assert(c->args.tmp_ldi == 5);

    c->args.type[1] = T_IND;
    c->args.type[2] = T_DIR;

    arena[3] = 0xaa;
    arena[4] = 0xbb;

    replace_indirects(c, arena);
    cr_assert(c->args.args[1] == (short)0xaabb);
}
