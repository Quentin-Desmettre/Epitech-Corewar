/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** get_header.c
*/

#include "asm.h"

char code_of(char const *name)
{
    for (int i = 0; op_tab[i].mnemonique; i++)
        if (!my_strcmp(op_tab[i].mnemonique, name))
            return op_tab[i].code;
    return -1;
}

char check_direct_validity(char const *arg, char **err_mess)
{
    int is_valid;

    if (arg[1] == LABEL_CHAR)
        is_valid = (arg[2] && contain_only(arg + 2,
        LABEL_CHARS)) ? T_DIR : T_ERROR;
    else
        is_valid = (arg[1] && str_is_num_signed(arg + 1)) ? T_DIR : T_ERROR;
    *err_mess = is_valid ? *err_mess : "Invalid direct";
    return is_valid;
}

char type_of_arg(char const *arg, char **err_mess)
{
    int is_valid;

    if (!arg[0]) {
        *err_mess = "Invalid argument";
        return T_ERROR;
    }
    if (arg[0] == 'r') {
        is_valid = (arg[1] && str_is_num(arg + 1) && is_in_bounds(my_getnbr(
        arg + 1, NULL), 0, REG_NUMBER + 1));
        *err_mess = is_valid ? *err_mess : "Invalid register";
        return is_valid ? T_REG : T_ERROR;
    }
    if (arg[0] == DIRECT_CHAR)
        return check_direct_validity(arg, err_mess);
    if (arg[0] == LABEL_CHAR)
        is_valid = (arg[1] && contain_only(arg + 1, LABEL_CHARS)) ? 4 : T_ERROR;
    else
        is_valid = str_is_num_signed(arg) ? 4 : T_ERROR;
    *err_mess = is_valid ? *err_mess : "Invalid indirect";
    return is_valid;
}

uint8_t coding_byte_for(char **words)
{
    uint8_t byte = 0;
    uint8_t bit_offset = 6;
    char type;
    char *mess = NULL;

    for (int i = 1; words[i]; i++, bit_offset -= 2) {
        type = type_of_arg(words[i], &mess);
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
