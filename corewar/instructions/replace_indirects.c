/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** replace_indirects.c
*/

#include "corewar.h"

static int has_mod_idx(int code)
{
    if (code == 2 || code == 3 || code == 6 || code == 7 || code == 8 ||
    code == 10 || code == 11)
        return 1;
    return 0;
}

static void get_indirect_value(args_t *arg, char *map, int index, int pc)
{
    int value = arg->args[index];
    int address = pc + (has_mod_idx(arg->code) ?
    value % IDX_MOD : value);

    if (arg->code == 3)
        return;
    memcpy_cor(&arg->args[index], map, address % MEM_SIZE, REG_SIZE);
    convert_endian(&arg->args[index]);
}

static void manage_ldi(int pc, args_t *arg, char *arena, int registers[16])
{
    int value = arg->args[0];
    int address = pc + (has_mod_idx(arg->code) ? value % IDX_MOD : value);
    int16_t first;
    int sum;

    if (arg->type[0] == T_IND) {
        memcpy_cor(&first, arena, address, IND_SIZE);
        convert_endian_short(&first);
        arg->args[0] = first;
    }
    if (arg->type[0] == T_REG)
        arg->args[0] = registers[arg->args[0]];
    if (arg->type[1] == T_REG)
        arg->args[1] = registers[arg->args[1]];

    sum = arg->args[0] + arg->args[1];
    address = pc + sum % IDX_MOD;
    memcpy_cor(&value, arena, address, REG_SIZE);
    convert_endian(&value);
    arg->tmp_ldi = value;
}

static void manage_sti(int pc, args_t *arg, char *arena, int registers[16])
{
    int value = arg->args[1];
    int address = pc + (has_mod_idx(arg->code) ? value % IDX_MOD : value);
    int16_t first;
    int sum;

    if (arg->type[1] == T_IND) {
        memcpy_cor(&first, arena, address, IND_SIZE);
        convert_endian_short(&first);
        arg->args[1] = first;
    }
    if (arg->type[1] == T_REG)
        arg->args[1] = registers[arg->args[1]];
    if (arg->type[2] == T_REG)
        arg->args[2] = registers[arg->args[2]];

    sum = arg->args[2] + arg->args[1];
    address = pc + sum % IDX_MOD;
    arg->tmp_ldi = address;
}

void replace_indirects(champ_t *champ, char *arena)
{
    args_t *args = &champ->args;

    if (args->code == 0x0e || args->code == 0x0a)
        return manage_ldi(champ->pc, args, arena, champ->registers);
    if (args->code == 0x0b)
        return manage_sti(champ->pc, args, arena, champ->registers);

    for (int i = 0; i < 3; i++) {
        if (args->type[i] == T_IND)
            get_indirect_value(args, arena, i, champ->pc);
    }
}
