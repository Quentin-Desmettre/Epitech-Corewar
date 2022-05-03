/*
** EPITECH PROJECT, 2022
** CREATE_CHAMP_C
** File description:
** create_champ.c
*/

#include "corewar_include/op.h"

champ_t *init_node(param_champ_t *param, char *path_file)
{
    champ_t *node = malloc(sizeof(champ_t));

    node->name_champ = path_file;
    if (param->num_impose[param->index]) {
        node->nb_is_impose = 1;
        node->champ_nbr = param->num_impose[param->index];
    } else {
        node->nb_is_impose = 0;
        node->champ_nbr = param->num_champ;
        param->num_champ++;
    }
    node->adress = param->adress_act;
    node->adress_impose = (node->adress != -1) ? 1 : 0;
    node->next = NULL;
    return node;
}

void append_champ(char *path_file, param_champ_t *param, champ_t **info_champ)
{
    champ_t *save = *info_champ;

    if (*info_champ) {
        while ((*info_champ)->next != NULL)
            *info_champ = (*info_champ)->next;
        (*info_champ)->next = init_node(param, path_file);
        (*info_champ) = save;
    } else {
        *info_champ = init_node(param, path_file);
    }
}

void create_champ(char *path_file, param_champ_t *param, champ_t **info_champ)
{
    int fd = open(path_file, O_RDONLY);

    if (fd < 0) {
        write(2, "Error in function open: No such file or directory.\n", 51);
        exit(84);
    }
    close(fd);
    append_champ(path_file, param, info_champ);
    param->index++;
    param->adress_act = param->adress_next;
    param->adress_next = -1;
}
