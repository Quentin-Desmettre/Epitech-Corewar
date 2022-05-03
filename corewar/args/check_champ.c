/*
** EPITECH PROJECT, 2022
** CHECK_CHAMP_C
** File description:
** check_champ.c
*/

#include "corewar_include/op.h"

void delete_champ(champ_t **info_champ)
{
    champ_t *save = *info_champ;
    champ_t *tmp = NULL;

    if ((*info_champ)->champ_nbr >= 5) {
        tmp = (*info_champ)->next;
        free((*info_champ));
        (*info_champ) = tmp;
        save = tmp;
    }
    while (*info_champ) {
        if ((*info_champ)->next && (*info_champ)->next->champ_nbr >= 5) {
            tmp = (*info_champ)->next->next;
            free((*info_champ)->next);
            (*info_champ)->next = tmp;
        }
        (*info_champ) = (*info_champ)->next;
    }
    (*info_champ) = save;
}

int get_num_of_champ(champ_t **info_champ)
{
    champ_t *save = *info_champ;
    int nb = 0;

    while (*info_champ) {
        nb++;
        (*info_champ) = (*info_champ)->next;
    }
    (*info_champ) = save;
    return nb;
}

void check_champ(int nb_to_change, champ_t **info_champ)
{
    int valid_num[4] = {1, 2, 3, 4};

    if (get_num_of_champ(info_champ) < 2) {
        write(2, "Error in function open: No such file or directory.\n", 51);
        exit(84);
    }
    setup_valid_num(info_champ, &valid_num);
    set_champ_real_num(info_champ, &valid_num);
    if (nb_to_change) {
        change_all_nb_champ(info_champ, nb_to_change);
        delete_champ(info_champ);
    }
}
