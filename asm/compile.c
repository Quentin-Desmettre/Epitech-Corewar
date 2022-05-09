/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** main2.c
*/

#include "asm.h"

char *get_next_line(FILE *f)
{
    char *line = NULL;
    size_t s;

    while (1) {
        if (getline(&line, &s, f) < 0) {
            free(line);
            return NULL;
        }
        if (line[0] == '#' || line[0] == '\0') {
            free(line);
            continue;
        } else
            return line;
    }
}

char const *get_output_file(char const *file)
{
    int len = my_strlen(file);
    char *dup = my_strdup(file);
    char *output;

    if (!my_strcmp(file + len - 2, ".s")) {
        dup[len - 2] = 0;
        output = str_concat(2, dup, ".cor");
        free(dup);
        return output;
    }
    return str_concat(2, file, ".cor");
}

int compile_file(char const *file)
{
    FILE *f = fopen(file, "r");

    if (!f) {
        dprint(2, "Error while opening '%s'.\n", file);
        return 0;
    }
    if (has_error(file))
        return 0;
    return write_file(f, get_output_file(file));
}
