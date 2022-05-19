/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "op.h"

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

args_t *dup_args(args_t *base)
{
    args_t *a = malloc(sizeof(args_t));

    my_memcpy(a, base, sizeof(args_t));
    return a;
}

args_t *copy_args(int code, char *arena, int pc, args_t *args)
{
    int offset = 0;
    int arg_size;
    int nb_arg = number_of_args(args);

    for (int i = 0; i < nb_arg; i++) {
        arg_size = size_of_arg(code, i, args->type);
        memcpy_cor(args->args + i,
        arena, ((pc + 2 + offset) % MEM_SIZE), arg_size);
        if (arg_size > 1)
            convert_endian(args->args + i);
        if (arg_size == 2)
            args->args[i] >>= 16;
        if (arg_size == 1)
            args->args[i] -= 1;
        offset += arg_size;
    }
    args->byte_offset = 2 + offset;
    return dup_args(args);
}

args_t *get_next_instruction(char *arena, int pc)
{
    int code = arena[pc];
    int nb_arg;
    args_t args = {.code = code};

    if (code < 1 || code > 16)
        return NULL;
    if (!IS_SPECIAL_CASE(code)) {
        get_coding_byte(arena[GET_BYTE(pc + 1)], &args);
        nb_arg = number_of_args(&args);
        if (nb_arg != op_tab[code - 1].nbr_args ||
        !are_types_valid(&args, code, nb_arg))
            return NULL;
    } else {
        args.byte_offset = (code == 1 ? 5 : 3);
        memcpy_cor(args.args, arena, ((pc + 1) % MEM_SIZE), code == 1 ? 4 : 2);
        convert_endian(args.args);
        args.args[0] >>= (args.byte_offset == 3) ? 16 : 0;
        return dup_args(&args);
    }
    return copy_args(code, arena, pc, &args);
}

void convert_endian_short(short *nbr)
{
    short nb = *nbr;
    short swapped = ((nb >> 8) & 0xff) | ((nb << 8) & 0xff00);

    *nbr = swapped;
}

int has_mod_idx(int code)
{
    if (code == 2 || code == 3 || code == 6 || code == 7 || code == 8 ||
    code == 10 || code == 11)
        return 1;
    return 0;
}

void get_indirect_value(args_t *arg, char *map, int index, int pc)
{
    int value = arg->args[index];
    int address = pc + (has_mod_idx(arg->code) ?
    value % IDX_MOD : value);

    if (arg->code == 3)
        return;
    memcpy_cor(&arg->args[index], map, address % MEM_SIZE, REG_SIZE);
    convert_endian(&arg->args[index]);
}

void manage_ldi(int pc, args_t *arg, char *arena)
{
    int value = arg->args[0];
    int address = pc + (has_mod_idx(arg->code) ?
    value % IDX_MOD : value);
    int16_t first;
    int sum;

    if (arg->type[0] == T_IND) {
        memcpy_cor(&first, arena, address, IND_SIZE);
        convert_endian_short(&first);
        arg->args[0] = first;
    }
    sum = arg->args[0] + arg->args[1];
    address = pc + sum % IDX_MOD;
    memcpy_cor(&value, arena, address, REG_SIZE);
    convert_endian(&value);
    arg->tmp_ldi = value;
}

void replace_indirects(int pc, args_t *arg, char *arena)
{
    if (arg->code == 0x0e || arg->code == 0x0a)
        return manage_ldi(pc, arg, arena);

    for (int i = 0; i < 3; i++) {
        if (arg->type[i] == T_IND)
            get_indirect_value(arg, arena, i, pc);
    }
}

void instruction_reader(char *arena, champ_t *champ)
{
    args_t *arg = get_next_instruction(arena, champ->pc);

    if (!arg) {
        champ->pc++;
        champ->pc %= MEM_SIZE;
        champ->cycle = 0;
        return;
    }
    replace_indirects(champ->pc, arg, arena);
    champ->args = *arg;
    champ->cycle_to_wait = op_tab[arg->code - 1].nbr_cycles;
    free(arg);
}
