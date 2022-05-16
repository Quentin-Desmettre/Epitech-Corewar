/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "op.h"
#include "libmy.h"

int i_has_index(int mnemonic, int nb_arg)
{
    if (mnemonic == 9)
        return 1;
    if ((mnemonic == 10 || mnemonic == 14) && nb_arg < 3)
        return 1;
    if (mnemonic == 11 && nb_arg > 1)
        return 1;
    if (mnemonic == 12 || mnemonic == 15)
        return 1;
    return 0;
}

int instruction_manager(int mnemonic, char *instructions)
{
    int (*fptr[])()= {&i_live, &i_ld, &i_st, &i_add, &i_sub, &i_and, &i_or,
    &i_xor, &i_zjmp, &i_ldi, &i_sti, &i_fork, &i_lld, &i_lldi, &i_lfork,
    &i_aff};
    args_t *args = malloc(sizeof(args_t));
    int byte_offset;

    my_memset(args, 0, sizeof(args_t));
    fptr[mnemonic - 1](args->args[0], args->args[1], args->args[2]);
    byte_offset = get_instruction_args(mnemonic, instructions + 1, args);
    free(args);
    return (byte_offset);
}

void instruction_reader(champ_t *champ)
{
    int champ_pc = 0;
    char instruction;

    for (int i = champ_pc; i < champ->header.prog_size; i++) {
        instruction = champ->instruction[i];
        if (instruction > 0x00 && instruction <= 0x10)
            i += instruction_manager(instruction, champ->instruction + i);
    }
}
