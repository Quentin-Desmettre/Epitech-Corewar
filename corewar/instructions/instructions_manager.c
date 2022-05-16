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
    args_t *args = malloc(sizeof(args_t));
    int byte_offset;

    my_memset(args, 0, sizeof(args_t));
    byte_offset = get_instruction_args(mnemonic, instructions + 1, args);
    free(args);
    return (byte_offset);
}

void instruction_reader(char *instructions, champ_t *champ)
{
    int champ_pc = 0;
    char instruction;

    for (int i = champ_pc; i < champ->header.prog_size; i++) {
        instruction = champ->instruction[i];
        if (instruction > 0x00 && instruction <= 0x10)
            i += instruction_manager(instruction, champ->instruction + i);
    }
}
