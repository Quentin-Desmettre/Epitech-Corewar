/*
** EPITECH PROJECT, 2022
** CHECK_INSTRUCTION_C
** File description:
** check_instruction.c
*/

#include "corewar_include/op.h"

void get_coding_byte(char coding_byte, args_t *args)
{
    for (int i = 0; i < 3; i++) {
        if (((coding_byte << 2 * i) & 0x40) == 0x40)
            args->type[i] = T_REG;
        if (((coding_byte << 2 * i) & 0x80) == 0x80)
            args->type[i] = T_DIR;
        if (((coding_byte << 2 * i) & 0xC0) == 0xC0)
            args->type[i] = T_IND;
    }
}

int number_of_args(args_t *args)
{
    int nb = 0;

    while (args->type[nb] && nb < 3)
        nb++;
    return nb;
}

int are_types_valid(args_t *args, int op_code, int nb_arg)
{
    for (int i = 0; i < nb_arg; i++)
        if (!(op_tab[op_code - 1].type[i] & args->type[i]))
            return 0;
    return 1;
}

int size_of_arg(int code, int nb, char types[3])
{
    if (types[nb] == T_REG)
        return 1;
    if (types[nb] == T_IND)
        return IND_SIZE;
    if (i_has_index(code, nb + 1))
        return IND_SIZE;
    return DIR_SIZE;
}
