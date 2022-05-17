/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "corewar.h"

int has_mod_idx(int code)
{
    if (code == 2 || code == 3 || code == 6 || code == 7 || code == 8 ||
    code == 10 || code == 11)
        return 1;
    return 0;
}

void get_indirect_value(champ_t *champ, char *map, int index)
{
    int value = champ->args.args[index];
    int address = champ->pc + (has_mod_idx(champ->args.code)) ?
    value % IDX_MOD : value;

    memcpy_cor(&champ->args.args[index], map, address, REG_SIZE);
    convert_endian(&champ->args.args[index]);
}

void exec_instructions(champ_t *champ, char *map)
{
    int (*fptr[])() = {&i_live, &i_ld, &i_st, &i_add, &i_sub, &i_and, &i_or,
    &i_xor, &i_zjmp, &i_ldi, &i_sti, &i_fork, &i_lld, &i_lldi, &i_lfork,
    &i_aff};

    for (int i = 0; i < 3; i++)
        if (champ->args.type[i] == INDIRECT)
            get_indirect_value(champ, map, i);
    fptr[champ->args.code - 1](champ->args.args, champ, map);
    champ->cycle_to_wait = -1;
    champ->cycle = 0;
    champ->pc = (champ->pc + champ->args.byte_offset) % MEM_SIZE;
}
