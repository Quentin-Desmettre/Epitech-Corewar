/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** compile.c
*/

#include "asm.h"

int write_file(FILE *f, char const *output)
{
    char *line;
    char **words;

    while ((line = get_next_line(f))) {
        words = my_str_to_word_array(line, ", \t");
        free(line);
        free_str_array(words);
    }
    if (errno) {
        printf("file error\n");
        return 0;
    }
    return 1;
}
