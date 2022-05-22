/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** globals.c
*/

#include "corewar.h"

champ_t *last_to_live(champ_t *new)
{
    static champ_t *live = NULL;

    if (new)
        live = new;
    return live;
}

champ_t **all_champs(champ_t **new)
{
    static champ_t **c = NULL;

    if (new)
        c = new;
    return c;
}

champ_t **fork_list(void)
{
    static champ_t *list = NULL;

    return &list;
}

void increase_counter(void)
{
    static int nbr_lives_done = 0;
    int *cycle_to_die;

    nbr_lives_done++;
    while (nbr_lives_done >= NBR_LIVE) {
        cycle_to_die = get_cycle_to_die();
        *cycle_to_die -= CYCLE_DELTA;
        nbr_lives_done -= NBR_LIVE;
    }
}
