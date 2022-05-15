/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** main.c
*/

#include "asm.h"

int main(int ac, char **av)
{
    int rval = 0;

    if (ac == 1)
        return print("Usage: ./asm file_name[.s]\n") ? 84 : 84;
    for (int i = 1; i < ac; i++) {
        if (!compile_file(av[i]))
            rval = 84;
        flush_garbage();
    }
    exit(rval);
}
