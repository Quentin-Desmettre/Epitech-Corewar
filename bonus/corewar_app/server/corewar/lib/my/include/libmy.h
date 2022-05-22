/*
** EPITECH PROJECT, 2021
** my
** File description:
** libmy.h
*/

#ifndef LIBMY_H
    #define LIBMY_H
    #include <stdlib.h>
    #define init_with my_memset
    #include "iomanip.h"
    #include "linked_list.h"
    #include "my_printf.h"
    #include "others.h"
    #include "strmanip.h"

void my_free(void *data);
void my_exit(int code);
void *my_malloc(size_t size);
void flush_garbage(void);

    #define malloc my_malloc
    #define free my_free
    #define exit my_exit

void my_memcpy(void *dest, void *source, size_t size);
unsigned my_pow(unsigned nb, unsigned power);
int getnbr_overflow(char *str);
int str_is_num_signed(char const *str);

#endif
