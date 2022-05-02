/*
** EPITECH PROJECT, 2022
** CHECK_ARGS_C
** File description:
** check_args.c
*/

#include "unistd.h"
#include "corewar_include/op.h"
#include "libmy.h"

void check_dump(param_champ_t *param, char *arg)
{
    int error = 0;

    if (param->dump_cycle) {
        write(2, "Double definition of option dump.\n", 34);
        exit(84);
    }
    param->dump_cycle = my_getnbr(arg, &error);
    if (error || param->dump_cycle)
        param->dump_cycle = 1;
}

void check_num(param_champ_t *param, char *arg)
{
    int error = 0;

    if (param->num_impose[param->index] != 0) {
        write(2, "Invalid option.\n", 16);
        exit(84);
    }
    param->num_impose[param->index] = my_getnbr(arg, &error);
    if (error || param->num_impose[param->index] < 0 ||
    param->num_impose[param->index] > 4) {
        write(2, "-n argument ", 12);
        my_putstr(arg);
        write(2, " is invalid.\n Enter a number between 1 and 4.", 45);
        exit(84);
    }
}

void check_address(param_champ_t *param, char *arg)
{
    int error = 0;

    if (param->adress_next != 0) {
        write(2, "Invalid option.\n", 16);
        exit(84);
    }
    param->adress_next = my_getnbr(arg, &error);
    if (error) {
        write(2, "-a argument ", 12);
        my_putstr(arg);
        write(2, " is invalid.\n Enter a valid memory offset.\n", 43);
        exit(84);
    }
}