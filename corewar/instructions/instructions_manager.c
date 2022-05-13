/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "op.h"
#include "libmy.h"

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

int get_args(char *instructions, args_t *args, int mnemonic)
{
    int byte_offset = 0;

    for (int i = 0; args->type[i] != EMPTY; i++) {
        print("TYPE : %d\n", args->type[i]);
        if (args->type[i] == INDIRECT) {
            my_memcpy((void *) &args->args[i], (void *)&instructions[i], IND_SIZE);
            byte_offset += IND_SIZE;
        }
        if (args->type[i] == REGISTER) {
            my_memcpy((void *) &args->args[i], (void *)&instructions[i], 1);
            byte_offset += 1;
        }
        if (args->type[i] == DIRECT || !i_has_index(mnemonic, i + 1)) {
            my_memcpy((void *) &args->args[i], (void *)&instructions[i], DIR_SIZE);
            convert_endian(&args->args[i]);
            byte_offset += DIR_SIZE;
        } else {
            my_memcpy((void *) &args->args[i], (void *)&instructions[i], IND_SIZE);
            byte_offset += IND_SIZE;
        }
    }
    return (byte_offset);
}

int get_instruction_args(int mnemonic, char *instructions, args_t *args)
{
    int exception[4] = {0x01, 0x09, 0x0c, 0x0f};

    for (int i = 0; i < 4; i++)
        if (mnemonic == exception[i]) {
            my_memcpy((void *) &args->args[i], (void *) &instructions[i], 2);
            return (1);
        }
    get_coding_byte(instructions[1], args);
    return (get_args(instructions + 2, args, mnemonic) + 1);
}

int get_args_count(char type[3])
{
    int count = 0;

    for (int i = 0; i < 3; i++)
        if (type[i] != EMPTY)
            count++;
    return (count);
}

int instruction_manager(int mnemonic, char *instructions)
{
    int (*fptr[])()= {&i_live, &i_ld, &i_st, &i_add, &i_sub, &i_and, &i_or,
    &i_xor, &i_zjmp, &i_ldi, &i_sti, &i_fork, &i_lld, &i_lldi, &i_lfork,
    &i_aff};
    args_t *args = malloc(sizeof(args_t));
    int byte_offset;

    my_memset(args, 0, sizeof(args_t));
    byte_offset = get_instruction_args(mnemonic, instructions, args);
    fptr[mnemonic - 1](args->args[0], args->args[1], args->args[2]);
    for (int i = 0; i < 3; i++) {
        printf("%d\t%d\t", mnemonic, args->args[i]);
        printf("%s\n", args->type[i] == REGISTER ? "REGISTER" : args->type[i] == DIRECT ? "DIRECT" : args->type[i] == INDIRECT ? "INDIRECT" : "EMPTY");
    }
    printf("============== %d =============\n", byte_offset);
    free(args);
    return (byte_offset);
//    return (fptr[mnemonic - 1](?));
}

void instruction_reader(champ_t *champ)
{
    int champ_pc = 0;
    char instruction;

    for (int i = champ_pc; i < champ->header.prog_size; i++) {
        instruction = champ->instruction[i];
        if (instruction > 0x00 && instruction <= 0x10) {
            print("%d\n", i);
            i += instruction_manager(instruction, champ->instruction + i);
        }
    }
}
