/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "op.h"

int i_st(int arg[3], champ_t *champ, char *arena)
{
    corewar_grap_t *graph = get_graph_struct();


    int to_copy = champ->registers[arg[0]];

    if (champ->args.type[1] == T_REG) {
        champ->registers[arg[1]] = to_copy;
    } else {
        graph->writing = champ->param.champ_nbr;
        convert_endian(&to_copy);
        cpy_in_arena(arena, &to_copy,
        (champ->pc + arg[1] % IDX_MOD) % MEM_SIZE, 4);
    }
    return (0);
}

int i_sti(int arg[3], champ_t *champ, char *arena)
{
    int to_copy = champ->registers[arg[0]];
    corewar_grap_t *graph = get_graph_struct();

    convert_endian(&to_copy);
    graph->writing = champ->param.champ_nbr;
    cpy_in_arena(arena, &to_copy, champ->args.tmp_ldi, REG_SIZE);
    return (0);
}
