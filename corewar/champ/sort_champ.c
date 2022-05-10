/*
** EPITECH PROJECT, 2022
** SORT_CHAMP_C
** File description:
** sort_champ.c
*/

#include "corewar_include/op.h"

int find_little_but_higher(champ_t *champ, int int_compare)
{
    int little_int = 8;
    champ_t *save = champ;

    while (champ) {
        if (champ->champ_nbr > int_compare && champ->champ_nbr < little_int)
            little_int = champ->champ_nbr;
        champ = champ->next;
    }
    champ = save;
    return (little_int);
}

champ_t *create_nodes(champ_t *info, int champ)
{
    champ_t *save = info;
    champ_t *return_champ = malloc(sizeof(champ_t));

    while (info->champ_nbr != champ)
        info = info->next;
    return_champ->champ_nbr = info->champ_nbr;
    return_champ->name_champ = info->name_champ;
    return_champ->nb_is_impose = info->  nb_is_impose;
    return_champ->adress = info->adress;
    return_champ->adress_impose = info->adress_impose;
    return_champ->instruction = info->instruction;
    return_champ->header = info->header;
    return_champ->next = NULL;
    info = save;
    return (return_champ);
}

champ_t *append_champ_with_value(champ_t *sorted, int little, champ_t *all)
{
    champ_t *save = sorted;

    if (!sorted) {
        sorted = create_nodes(all, little);
        return sorted;
    }
    while (sorted->next)
        sorted = sorted->next;
    sorted->next = create_nodes(all, little);
    sorted = save;
    return sorted;
}

champ_t *sort_my_list(champ_t *champ)
{
    int num_of_champ = get_num_of_champ(&champ);
    champ_t *sorted = NULL;
    champ_t *tmp = NULL;
    int little = 0;

    for (int i = 0; i < num_of_champ; i++) {
        little = find_little_but_higher(champ, little);
        sorted = append_champ_with_value(sorted, little, champ);
    }
    while (champ) {
        tmp = champ;
        champ = champ->next;
        free(tmp);
    }
    return sorted;
}
