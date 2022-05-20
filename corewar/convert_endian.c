/*
** EPITECH PROJECT, 2022
** CONVERT_ENDIAN_C
** File description:
** convert_endian.c
*/

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
