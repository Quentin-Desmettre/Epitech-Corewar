/*
** EPITECH PROJECT, 2022
** CHECK_CHAMP_C
** File description:
** check_champ.c
*/

#include "corewar_include/op.h"

int get_alive_champs(champ_t *champs)
{
    int ids[4] = {0, 0, 0, 0};
    int nb = 0;

    while (champs) {
        ids[champs->param.champ_nbr]++;
        champs = champs->next;
    }
    for (int i = 0; i < 4; i++)
        nb += (ids[i] ? 1 : 0);
    return nb;
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

void setup_all_champ_for_game(champ_t **info_champ)
{
    champ_t *save = *info_champ;
    champ_t **tmp = NULL;

    while (save) {
        save->cycle = 0;
        save->cycle_to_wait = -1;
        my_memset(save->registers, 0, sizeof(int) * REG_NUMBER);
        save->registers[0] = save->param.champ_nbr;
        save->is_alive = 0;
        save->carry = 0;
        free(save->instruction);
        save->instruction = NULL;
        my_memset(&save->args, 0, sizeof(args_t));
        save = save->next;
    }
    tmp = get_champ_struct();
    *tmp = *info_champ;
}

void check_champ(champ_t **info_champ)
{
    int valid_num[4] = {1, 2, 3, 4};
    int number_of_champ = get_num_of_champ(info_champ);

    if (number_of_champ < 2) {
        write(2, "Error in function open: No such file or directory.\n", 51);
        exit(84);
    }
    setup_valid_num(info_champ, &valid_num);
    set_champ_real_num(info_champ, &valid_num);
    fill_header_champ(info_champ);
}
