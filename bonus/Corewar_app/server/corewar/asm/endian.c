/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** endian.c
*/

#include "asm.h"

void convert_endian(int *nbr)
{
    int left = (((*nbr >> 24) & 0xff) | ((*nbr << 8) & 0xff0000));
    int right = (((*nbr >> 8) & 0xff00) | ((*nbr << 24) & 0xff000000));

    *nbr = left | right;
}

void convert_endian_short(short *nbr)
{
    short nb = *nbr;
    short swapped = ((nb >> 8) & 0xff) | ((nb << 8) & 0xff00);

    *nbr = swapped;
}
