/*
** EPITECH PROJECT, 2022
** NUM_CHAMP_C
** File description:
** num_champ.c
*/

#include "corewar_include/op.h"

static void find_little_number(int valid_num[][4], int *nbr)
{
    int i;

    for (i = 0; i < MAX_ARGS_NUMBER && (*valid_num)[i] == 0; i++);
    *nbr = (*valid_num)[i];
    (*valid_num)[i] = 0;
}

void setup_valid_num(champ_t **info_champ, int valid_num[][4])
{
    champ_t *save = *info_champ;

    while (*info_champ) {
        if ((*info_champ)->param.nb_is_impose)
            (*valid_num)[(*info_champ)->param.champ_nbr - 1] = 0;
        (*info_champ) = (*info_champ)->next;
    }
    (*info_champ) = save;
}

void set_champ_real_num(champ_t **info_champ, int valid_num[][4])
{
    champ_t *save = *info_champ;

    while (*info_champ) {
        if (!(*info_champ)->param.nb_is_impose)
            find_little_number(valid_num, &(*info_champ)->param.champ_nbr);
        (*info_champ) = (*info_champ)->next;
    }
    (*info_champ) = save;
}

int check_same_nbr(param_argv_t *param)
{
    int error = 0;

    for (int i = 0; i < MAX_ARGS_NUMBER + 1; i++) {
        for (int j = i + 1; j < MAX_ARGS_NUMBER + 1 && !error; j++) {
            error = (param->num_impose[i] == param->num_impose[j] &&
            param->num_impose[i] != 0) ? 1 : 0;
        }
        if (error)
            return 1;
    }
    return 0;
}
