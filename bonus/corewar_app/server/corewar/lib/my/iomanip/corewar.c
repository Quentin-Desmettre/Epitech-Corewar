/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** corewar.c
*/

#include "libmy.h"

unsigned my_pow(unsigned nb, unsigned power)
{
    unsigned res = 1;

    for (unsigned i = 0; i < power; i++)
        res *= nb;
    return res;
}

int getnbr_overflow(char *str)
{
    int nb = 0;
    int len = my_strlen(str);

    for (int i = 0; len - i > 0; i++) {
        if (str[len - i - 1] == '-') {
            nb *= -1;
            break;
        }
        nb += (str[len - i - 1] - '0') * my_pow(10, i);
    }
    return nb;
}

int str_is_num_signed(char const *str)
{
    int start = (str[0] == '-') ? 1 : 0;

    return str_is_num(str + start);
}
