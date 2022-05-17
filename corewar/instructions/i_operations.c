/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "op.h"

int i_add(int arg[3], champ_t *champ, __attribute__((unused))char *arena)
{
    int first = champ->registers[arg[0]];
    int second = champ->registers[arg[1]];

    champ->registers[arg[3]] = first + second;
    champ->carry = !champ->carry;
    return (0);
}

int i_sub(int arg[3], champ_t *champ, __attribute__((unused))char *arena)
{
    int first = champ->registers[arg[0]];
    int second = champ->registers[arg[1]];

    champ->registers[arg[3]] = first - second;
    champ->carry = !champ->carry;
    return (0);
}
