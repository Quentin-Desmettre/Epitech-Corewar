/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "op.h"

int i_st(int arg[3], champ_t *champ, char *arena)
{
    if (champ->args.type[1] == REGISTER)
        champ->registers[arg[1]] = champ->registers[arg[0]];
    else
        cpy_in_arena(arena, &champ->registers[arg[0]],
        (champ->pc + arg[1] % IDX_MOD) % MEM_SIZE, 4);
    return (0);
}

int i_sti(int arg[3], champ_t *champ, char *arena)
{
    if (champ->args.type[1] == REGISTER)
        arg[1] = champ->registers[arg[1]];
    if (champ->args.type[2] == REGISTER)
        arg[2] = champ->registers[arg[2]];
    cpy_in_arena(arena, &champ->registers[arg[0]],
    champ->pc + (arg[1] + arg[2]) % IDX_MOD, DIR_SIZE);
    return (0);
}
