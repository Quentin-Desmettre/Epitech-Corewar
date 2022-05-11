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
        if (line[0] == '#' || line[0] == '\n') {
            free(line);
            line = NULL;
        } else
            return line;
    }
}

char const *get_output_file(char const *file)
{
    char **words = my_str_to_word_array(file, "/");
    char *dup = words[my_str_array_len(words) - 1];
    char *output;
    int len = my_strlen(dup);

    if (len >= 2 && !my_strcmp(dup + len - 2, ".s")) {
        dup[len - 2] = 0;
        output = str_concat(2, dup, ".cor");
        free_str_array(words);
        return output;
    }
    output = str_concat(2, dup, ".cor");
    free_str_array(words);
    return output;
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
