/*
** EPITECH PROJECT, 2022
** CHECK_CHAMP_C
** File description:
** check_champ.c
*/

#include "corewar_include/op.h"

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

    while (save) {
        save->cycle = 0;
        save->cycle_to_wait = 0;
        my_memset(save->registers, 0, REG_NUMBER);
        save->is_alive = 0;
        free(save->instruction);
        save->instruction = NULL;
        save = save->next;
    }
}

void check_champ(int nb_to_change, champ_t **info_champ)
{
    int valid_num[4] = {1, 2, 3, 4};
    int number_of_champ = get_num_of_champ(info_champ);

    if (number_of_champ < 2) {
        write(2, "Error in function open: No such file or directory.\n", 51);
        exit(84);
    }
    setup_valid_num(info_champ, &valid_num);
    set_champ_real_num(info_champ, &valid_num);
    if (nb_to_change) {
        change_all_nb_champ(info_champ, nb_to_change);
        delete_champ(info_champ);
    }
    fill_header_champ(info_champ);
    setup_all_champ_for_game(info_champ);
}
