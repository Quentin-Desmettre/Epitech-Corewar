/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "op.h"

int i_and(int arg[3], champ_t *champ, __attribute__((unused))char *arena)
{
    int first = arg[0];
    int second = arg[1];

    champ->registers[arg[2]] = 0;
    champ->registers[arg[2]] |= first & second;
    champ->carry = !champ->carry;
    return (0);
}

int i_or(int arg[3], champ_t *champ, __attribute__((unused))char *arena)
{
    int first = arg[0];
    int second = arg[1];

    champ->registers[arg[2]] = 0;
    champ->registers[arg[2]] |= first | second;
    champ->carry = !champ->carry;
    return (0);
}

int i_xor(int arg[3], champ_t *champ, char *arena)
{
    int first = arg[0];
    int second = arg[1];

    champ->registers[arg[2]] = 0;
    champ->registers[arg[2]] |= first ^ second;
    champ->carry = !champ->carry;
    return (0);
}
