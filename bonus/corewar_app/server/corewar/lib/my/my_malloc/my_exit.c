/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** my_exit.c
*/

#include <stdlib.h>

void flush_garbage(void);

void my_exit(int code)
{
    flush_garbage();
    exit(code);
}
