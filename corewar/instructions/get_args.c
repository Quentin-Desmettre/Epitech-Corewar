/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "op.h"

int get_args(char *instructions, args_t *args, int mnemonic)
{
    int byte_offset = 0;

    for (int i = 0; args->type[i] != EMPTY; i++) {
        if (args->type[i] == REGISTER) {
            my_memcpy(&args->args[i], &instructions[byte_offset], 1);
            byte_offset += 1;
        }
        if (args->type[i] == INDIRECT) {
            my_memcpy(&args->args[i], &instructions[byte_offset], IND_SIZE);
            convert_endian(&args->args[i]);
            args->args[i] >>= 16;
            byte_offset += IND_SIZE;
        }
        if (args->type[i] == DIRECT && !i_has_index(mnemonic, i + 1)) {
            my_memcpy(&args->args[i], &instructions[byte_offset], DIR_SIZE);
            convert_endian(&args->args[i]);
            byte_offset += DIR_SIZE;
        }
        if (args->type[i] == DIRECT && i_has_index(mnemonic, i + 1)) {
            my_memcpy(&args->args[i], &instructions[byte_offset], IND_SIZE);
            convert_endian(&args->args[i]);
            args->args[i] >>= 16;
            byte_offset += IND_SIZE;
        }
    }
    return (byte_offset);
}

int get_coding_byte(char coding_byte, args_t *args)
{
    for (int i = 0; i < 3; i++) {
        if (((coding_byte << 2 * i) & 0x40) == 0x40)
            args->type[i] = REGISTER;
        if (((coding_byte << 2 * i) & 0x80) == 0x80)
            args->type[i] = DIRECT;
        if (((coding_byte << 2 * i) & 0xC0) == 0xC0)
            args->type[i] = INDIRECT;
    }
    return (0);
}

int get_instruction_args(int mnemonic, char *instructions, args_t *args)
{
    int exception[4] = {0x01, 0x09, 0x0c, 0x0f};
    int byte_offset[4] = {4, 2, 2, 2};

    for (int i = 0; i < 4; i++)
        if (mnemonic == exception[i]) {
            my_memcpy(&args->args[0], &instructions[0], byte_offset[i]);
            convert_endian(&args->args[0]);
            args->args[0] >>= (byte_offset[i] == 2) ? 16 : 0;
            args->args[0] = (!i) ? args->args[0] : (short)args->args[0];
            return (byte_offset[i]);
        }
    get_coding_byte(instructions[0], args);
    return (get_args(instructions + 1, args, mnemonic) + 1);
}
