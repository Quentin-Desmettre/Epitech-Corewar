/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "op.h"
#include "libmy.h"

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

#define GET_BYTE(x) (((x)) % MEM_SIZE)

static inline int is_special_case(int x)
{
    return (x == 1) || (x == 9) || (x == 12) || (x == 15);
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
        if (!(op_tab[op_code].type[i] & args->type[i]))
            return 0;
    return 1;
}

args_t *dup_args(args_t *base)
{
    args_t *a = malloc(sizeof(args_t));

    my_memcpy(a, base, sizeof(args_t));
    return a;
}

int size_of_arg(int code, int nb, int types[3])
{
    if (types[nb] == T_REG)
        return REG_SIZE;
    if (types[nb] == T_IND)
        return IND_SIZE;
    if (i_has_index(code, nb + 1))
        return IND_SIZE;
    return DIR_SIZE;
}

args_t *copy_args(int code, char *arena, int pc, args_t *args)
{
    int offset = 0;
    int arg_size;
    int nb_arg = number_of_args(args);

    for (int i = 0; i < nb_arg; i++) {
        arg_size = size_of_arg(code, i, args->type);
        my_memcpy(args->args + i,
        arena + ((pc + 2 + offset) % MEM_SIZE), arg_size);
        convert_endian(args->args + i);
        if (arg_size == 2)
            args->args[i] >>= 16;
        offset += arg_size;
    }
    return dup_args(args);
}

args_t *get_next_instruction(char *arena, int pc)
{
    int code = arena[pc];
    int nb_arg;
    args_t args = {};
    int arg_sizes[] = {4, 2, 2, 2};

    if (code < 1 || code > 16)
        return NULL;
    // args.code = code;
    if (!is_special_case(code)) {
        get_coding_byte(arena[GET_BYTE(pc + 1)], &args);
        nb_arg = number_of_args(&args);
        if (nb_arg != op_tab[code].nbr_args)
            return NULL;
        if (!are_types_valid(&args, code, nb_arg))
            return NULL;
    } else {
        my_memcpy(args.args, arena + ((pc + 1) % MEM_SIZE), code == 1 ? 4 : 2);
        return dup_args(&args);
    }
    return copy_args(code, arena, pc, &args);
}

void instruction_reader(champ_t *champ)
{
}
