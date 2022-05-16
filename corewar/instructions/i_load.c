/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "op.h"

int i_ld(int arg[3], champ_t *champ, char *arena)
{
    my_memcpy(&champ->registers[arg[1]],
    arena + (champ->pc + (arg[0] % IDX_MOD)) % MEM_SIZE, 4);
    return (0);
}

int i_ldi(int arg[3], champ_t *champ, char *arena)
{
    print("ldi %d %d %d\n", arg[0], arg[1], arg[2]);
    return (0);
}

int i_lld(int arg[3], champ_t *champ, char *arena)
{
    print("lld %d %d\n", arg[0], arg[1]);
    return (0);
}

int i_lldi(int arg[3], champ_t *champ, char *arena)
{
    print("lldi %d %d\n", arg[0], arg[1]);
    return (0);
}
