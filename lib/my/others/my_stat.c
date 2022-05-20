/*
** EPITECH PROJECT, 2022
** MY_STAT_C
** File description:
** my_stat.c
*/

#include <stdio.h>
#include <stdlib.h>

long long int my_stat(char *file, int nbline_or_nbchar)
{
    FILE *fd = fopen(file, "r");
    size_t bufsize = 0;
    char *buf = NULL;
    int len = 0;
    long long int nb_char = 0;
    long long int return_getline = 1;

    if (!fd)
        return (-1);
    while (return_getline > 0) {
        return_getline = getline(&buf, &bufsize, fd);
        free(buf);
        buf = NULL;
        nb_char += return_getline;
        len++;
    }
    fclose(fd);
    return (nbline_or_nbchar == 0 ? len - 1 : nb_char + 1);
}
