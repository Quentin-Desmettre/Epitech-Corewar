/*
** EPITECH PROJECT, 2022
** my_exit.c
** File description:
** my_exit
*/

#include "corewar_include/op.h"

champ_t **get_champ_t(void)
{
    static champ_t *champ = NULL;

    return (&champ);
}

void my_exit(int status)
{
    champ_t **champ = get_champ_t();
    champ_t *tmp = NULL;

    if (!get_champ_t())
        exit(status);
    while (*champ) {
        tmp = *champ;
        *champ = (*champ)->next;
        free(tmp);
        tmp = NULL;
    }
    free(tmp);
    exit(status);
}

char *cor_strcpy(char *str1, const char *str2, int cc[2], size_t size)
{
    int index_str2 = 0;

    for (size_t i = cc[0]; i <= size; i++, index_str2++) {
        if (i > MEM_SIZE)
            i = 0;
        if (str1[i] != '\0' && cc[1]) {
            free(str1);
            return (NULL);
        }
        if ((size_t)index_str2 >= size)
            break;
        str1[i] = str2[index_str2];
    }
    return (str1);
}
