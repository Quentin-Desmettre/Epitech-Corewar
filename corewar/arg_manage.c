/*
** EPITECH PROJECT, 2022
** ARG_MANAGE_C
** File description:
** arg_manage.c
*/

#include "unistd.h"
#include "corewar_include/op.h"
#include "libmy.h"

param_champ_t *init_value(void)
{
    param_champ_t *param = malloc(sizeof(param_champ_t));

    param->adress_act = 0;
    param->adress_next = 0;
    param->index = 0;
    param->last_opt = 0;
    param->num_champ = 1;
    param->num_impose[0] = 0;
    param->num_impose[1] = 0;
    param->num_impose[2] = 0;
    param->num_impose[3] = 0;
    return (param);
}

int check_if_opt(param_champ_t *param, char *str, char *str_next, int *index)
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

void create_champ(char *path_file, param_champ_t *param)
{
    my_putstr("Champ file : ");
    my_putstr(path_file);
    my_putstr("\nAdress Champ : ");
    my_put_nbr(param->adress_act);
    if (param->num_impose[param->index]) {
        my_putstr("\nNum of Champ : ");
        my_put_nbr(param->num_impose[param->index]);
    } else {
        my_putstr("\nNum of Champ : ");
        my_put_nbr(param->num_champ);
    }
    my_putchar('\n');
    param->index++;
    param->num_champ++;
    param->adress_act = param->adress_next;
    param->adress_next = 0;
}

int check_argv(int ac, char **av, int *dump_cycle)
{
    param_champ_t *param = init_value();
    champ_t *info_champ = NULL;

    for (int i = 1; i < ac; i++) {
        if (check_if_opt(param, av[i], av[i + 1], &i))
            continue;
        if (param->index == 4) {
            write(2, "The number of champion load is above the limit.\n", 48);
            exit(84);
        }
        create_champ(av[i], param);
    }
    *dump_cycle = param->dump_cycle;
    return 0;
}