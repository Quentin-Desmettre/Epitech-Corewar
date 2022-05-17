/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "corewar.h"

void exec_instructions(champ_t *champ, char *map)
{
    int (*fptr[])() = {&i_live, &i_ld, &i_st, &i_add, &i_sub, &i_and, &i_or,
    &i_xor, &i_zjmp, &i_ldi, &i_sti, &i_fork, &i_lld, &i_lldi, &i_lfork,
    &i_aff};

    fptr[champ->args.code - 1](champ->args.args, champ, map);
    champ->cycle_to_wait = -1;
    champ->cycle = 0;
    champ->pc = (champ->pc + champ->args.byte_offset) % MEM_SIZE;
}
