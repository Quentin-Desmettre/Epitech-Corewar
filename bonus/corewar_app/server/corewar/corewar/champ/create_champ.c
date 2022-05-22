/*
** EPITECH PROJECT, 2022
** CREATE_CHAMP_C
** File description:
** create_champ.c
*/

#include "corewar_include/op.h"

static champ_t *init_node(param_argv_t *param, char *path_file)
{
    champ_t *node = malloc(sizeof(champ_t));

    node->name_champ = path_file;
    if (param->num_impose[param->index]) {
        node->param.nb_is_impose = 1;
        node->param.champ_nbr = param->num_impose[param->index];
    } else {
        node->param.nb_is_impose = 0;
        node->param.champ_nbr = param->num_champ;
        param->num_champ++;
    }
    node->param.adress = param->adress_next;
    node->param.adress_impose = (node->param.adress != -1) ? 1 : 0;
    node->next = NULL;
    return node;
}

static void append_champ(char *path_file,
param_argv_t *param, champ_t **info_champ)
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

void create_champ(char *path_file, param_argv_t *param, champ_t **info_champ)
{
    int fd = open(path_file, O_RDONLY);

    if (fd < 0) {
        write(2, "Error in function open: No such file or directory.\n", 51);
        exit(84);
    }
    close(fd);
    append_champ(path_file, param, info_champ);
    param->index++;
    param->adress_act = -1;
    param->adress_next = -1;
}
