/*
** EPITECH PROJECT, 2022
** my_exit.c
** File description:
** my_exit
*/

#include "../../include/corewar_include/op.h"
#include "../../lib/my/include/strmanip.h"

champ_t **get_champ_t(void)
{
    static champ_t *champ = NULL;

    return (&champ);
}

void my_exit(int status)
{
    champ_t **champ = get_champ_t();

    if (!get_champ_t())
        exit(status);
    for (int i = 0, champ[i]; i++)
        free(*champ[i]);
    free(champ);
    exit(status);
}

char *cor_strcpy(char *str1, char *str2, int cc[2], size_t size)
{
    int index_str2 = 0;

    for (int i = cc[0]; i < size; i++) {
        if (i > MEM_SIZE)
            i = 0;
        if (str1[i] != '\0' && cc[1])
            return NULL;
        str1[i] = str2[index_str2];
        index_str2++;
    }
    return str2;
}
