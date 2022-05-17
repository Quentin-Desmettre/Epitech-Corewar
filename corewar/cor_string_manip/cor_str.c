/*
** EPITECH PROJECT, 2022
** COR_STR_C
** File description:
** cor_str.c
*/

#include "corewar_include/op.h"

void memcpy_cor(void *dest, char *arena, int start, int size)
{
    size_t pos_in_arena = start;

    for (int i = 0; i < size; i++) {
        ((char *)dest)[i] = arena[pos_in_arena];
        pos_in_arena = (pos_in_arena + 1) % MEM_SIZE;
    }
}

char *cor_strcpy(char *str1, const char *str2, const int cc[2], size_t size)
{
    size_t index_str2 = 0;

    for (size_t i = cc[0]; index_str2 < size; i++, index_str2++) {
        if (i >= MEM_SIZE)
            i = 0;
        if (str1[i] != '\0' && cc[1]) {
            free(str1);
            return (NULL);
        }
        str1[i] = str2[index_str2];
    }
    return (str1);
}