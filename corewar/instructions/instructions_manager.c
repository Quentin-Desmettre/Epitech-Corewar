/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "op.h"
#include "libmy.h"

<<<<<<< HEAD
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

=======
>>>>>>> 4b320e593700cf3843d8b2379c1cf4a910ade9e9
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
