/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "op.h"

int i_ld(int arg[3], champ_t *champ, char *arena)
{
    memcpy_cor(&champ->registers[arg[1]], arena,
    (champ->pc + arg[0] % IDX_MOD) % MEM_SIZE, 4);
    return (0);
}

int i_ldi(int arg[3], champ_t *champ, char *arena)
{
    int sum = 0;

    memcpy_cor(&sum, arena, (champ->pc + arg[0] % IDX_MOD) % MEM_SIZE,
    IND_SIZE);
    sum += arg[1];
    memcpy_cor(&champ->registers[arg[2]], arena,
    (champ->pc + sum % IDX_MOD) % MEM_SIZE, REG_SIZE);
    champ->carry = !champ->carry;
    return (0);
}

int i_lld(int arg[3], champ_t *champ, char *arena)
{
    memcpy_cor(&champ->registers[arg[1]], arena,
    (champ->pc + arg[0]) % MEM_SIZE, 4);
    champ->carry = !champ->carry;
    return (0);
}

int i_lldi(int arg[3], champ_t *champ, char *arena)
{
    int sum = 0;

    memcpy_cor(&sum, arena, ((champ->pc + arg[0]) % IDX_MOD) % MEM_SIZE,
    IND_SIZE);
    sum += arg[1];
    memcpy_cor(&champ->registers[arg[2]], arena,
    (champ->pc + sum) % MEM_SIZE, REG_SIZE);
    champ->carry = !champ->carry;
    return (0);
}
