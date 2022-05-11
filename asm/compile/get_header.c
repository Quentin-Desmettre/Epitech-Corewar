/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** get_header.c
*/

#include "asm.h"

size_t progsize_offset(void)
{
    return (size_t)(&((header_t *)NULL)->prog_size);
}

char code_of(char const *name)
{
    for (int i = 0; op_tab[i].mnemonique; i++)
        if (!my_strcmp(op_tab[i].mnemonique, name))
            return op_tab[i].code;
    return -1;
}

char type_of_arg(char const *arg)
{
    if (!arg[0])
        return T_ERROR;
    if (arg[0] == 'r')
        return (arg[1] && str_is_num(arg + 1) && is_in_bounds(my_getnbr(
        arg + 1, NULL), 0, REG_NUMBER + 1)) ? T_REG : T_ERROR;
    if (arg[0] == DIRECT_CHAR) {
        if (arg[1] == LABEL_CHAR)
            return (arg[2] && contain_only(arg + 2,
            LABEL_CHARS)) ? T_DIR : T_ERROR;
        return (arg[1] && str_is_num_signed(arg + 1)) ? T_DIR : T_ERROR;
    }
    if (arg[0] == LABEL_CHAR)
        return (arg[1] && contain_only(arg + 1, LABEL_CHARS)) ? T_IND : T_ERROR;
    return str_is_num_signed(arg) ? T_IND : T_ERROR;
}

uint8_t coding_byte_for(char **words)
{
    uint8_t byte = 0;
    uint8_t bit_offset = 6;
    char type;

    for (int i = 1; words[i]; i++, bit_offset -= 2) {
        type = type_of_arg(words[i]);
        if (type == T_REG)
            byte |= 0b01 << bit_offset;
        if (type == T_DIR)
            byte |= 0b10 << bit_offset;
        if (type == T_IND)
            byte |= 0b11 << bit_offset;
    }
    return byte;
}

int has_index(char *name, int nb_arg)
{
    int code = code_of(name);

    if (code == 9)
        return 1;
    if ((code == 10 || code == 14) && nb_arg < 3)
        return 1;
    if (code == 11 && nb_arg > 1)
        return 1;
    if (code == 12 || code == 15)
        return 1;
    return 0;
}
