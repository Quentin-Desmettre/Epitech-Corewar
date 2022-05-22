/*
** EPITECH PROJECT, 2022
** CHECK_ARGS_C
** File description:
** check_args.c
*/

#include "corewar_include/op.h"

void check_dump(param_argv_t *param, char *arg)
{
    int error = 0;

    if (!arg) {
        write(2, "Invalid option.\n", 16);
        exit(84);
    }
    if (param->dump_cycle != -1) {
        write(2, "Double definition of option dump.\n", 34);
        exit(84);
    }
    param->dump_cycle = my_getnbr(arg, &error);
    if (error || param->dump_cycle < 0) {
        write(2, "-dump argument ", 15);
        write(2, arg, my_strlen(arg));
        write(2, " is invalid. Please enter a positive number.\n", 45);
        exit(84);
    }
}

void check_num(param_argv_t *param, char *arg)
{
    int error = 0;

    if (!arg) {
        write(2, "Invalid option.\n", 16);
        exit(84);
    }
    if (param->num_impose[param->index] != 0) {
        write(2, "Invalid option.\n", 16);
        exit(84);
    }
    param->num_impose[param->index] = my_getnbr(arg, &error);
    if (error || param->num_impose[param->index] < 0 ||
    param->num_impose[param->index] > 4) {
        write(2, "-n argument ", 12);
        write(2, arg, my_strlen(arg));
        write(2, " is invalid.\n Enter a number between 1 and 4.\n", 46);
        exit(84);
    }
}

void check_address(param_argv_t *param, char *arg)
{
    int error = 0;

    if (!arg) {
        write(2, "Invalid option.\n", 16);
        exit(84);
    }
    if (param->adress_next != -1) {
        write(2, "Invalid option.\n", 16);
        exit(84);
    }
    param->adress_next = my_getnbr(arg, &error);
    if (error || param->adress_next < 0) {
        write(2, "-a argument ", 12);
        write(2, arg, my_strlen(arg));
        write(2, " is invalid.\n Enter a valid memory offset.\n", 43);
        exit(84);
    }
}
