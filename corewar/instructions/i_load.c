/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "op.h"

/*

les instructions prennent des param:

//ld prend en param un indirect ;

on les read au moment d'exec l'instruction (cycle 20), ou dès qu'on a load l'instruction (cycle 0) ?

*/

int i_ld(int arg[3], champ_t *champ, __attribute__((unused)) char *arena)
{
    champ->registers[arg[1]] = arg[0];
    champ->carry = champ->registers[arg[1]] ? 0 : 1;
    return (0);
}

int i_ldi(int arg[3], champ_t *champ, __attribute__((unused)) char *arena)
{
    champ->registers[arg[2]] = champ->args.tmp_ldi;
    champ->carry = champ->registers[arg[2]] ? 0 : 1;
    return (0);
}

int i_lld(int arg[3], champ_t *champ, __attribute__((unused)) char *arena)
{
    champ->registers[arg[1]] = arg[0];
    champ->carry = champ->registers[arg[1]] ? 0 : 1;
    return (0);
}

int i_lldi(int arg[3], champ_t *champ, __attribute__((unused)) char *arena)
{
    champ->registers[arg[2]] = champ->args.tmp_ldi;
    champ->carry = champ->registers[arg[2]] ? 0 : 1;
    return (0);
}
