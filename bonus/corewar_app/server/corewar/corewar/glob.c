/*
** EPITECH PROJECT, 2022
** GLOB_C
** File description:
** glob.c
*/

#include "corewar_include/op.h"

int *get_cycle_to_die(void)
{
    static int cycle_to_die = CYCLE_TO_DIE;

    return (&cycle_to_die);
}

champ_t **get_champ_struct(void)
{
    static champ_t *champion = NULL;

    return (&champion);
}
