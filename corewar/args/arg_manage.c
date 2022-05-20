/*
** EPITECH PROJECT, 2022
** ARG_MANAGE_C
** File description:
** arg_manage.c
*/

#include "corewar_include/op.h"

static param_argv_t *init_value(void)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    param->adress_act = 0;
    param->adress_next = -1;
    param->dump_cycle = -1;
    param->index = 0;
    param->last_opt = 0;
    param->num_champ = 1;
    param->num_impose[0] = 0;
    param->num_impose[1] = 0;
    param->num_impose[2] = 0;
    param->num_impose[3] = 0;
    param->num_impose[4] = 0;
    return (param);
}

static int check_if_opt(param_argv_t *param,
char *str, char *str_next, int *index)
{
    char *cmp_str[] = {"-dump", "-n", "-a"};
    void (*fun[])() = {&check_dump, &check_num, &check_address};

    for (int i = 0; i < 3; i++) {
        if (my_strcmp(str, cmp_str[i]) == 0) {
            fun[i](param, str_next);
            (*index)++;
            return (1);
        }
    }
    return (0);
}

static void error_on_check_argv(param_argv_t *param)
{
    if (check_same_nbr(param)) {
        write(2, "double definition of prog_number.\n", 34);
        exit(84);
    }
    if (param->adress_next != -1 || param->num_impose[param->index]) {
        write(2, "Invalid option.\n", 16);
        exit(84);
    }
}

void check_argv(int *ac, char **av, int *dump_cycle, champ_t **info_champ)
{
    param_argv_t *param = init_value();

    for (int i = 1; i < *ac; i++) {
        if (check_if_opt(param, av[i], av[i + 1], &i))
            continue;
        if (param->index == MAX_ARGS_NUMBER) {
            write(2, "The number of champion load is above the limit.\n", 48);
            exit(84);
        }
        create_champ(av[i], param, info_champ);
    }
    error_on_check_argv(param);
    *ac = param->num_impose[param->index];
    *dump_cycle = param->dump_cycle;
    free(param);
}
