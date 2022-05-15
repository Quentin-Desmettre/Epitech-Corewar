/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** main2.c
*/

#include "asm.h"

void replace_comment(char *line)
{
    int idx = index_of('#', line);

    if (idx >= 0)
        line[idx] = 0;
}

char **split_next_line(char ***base_words, FILE *f, int *nb_line)
{
    char **words;
    char *line;

    line = get_next_line(f, nb_line);
    if (!line) {
        *base_words = NULL;
        return NULL;
    }
    replace_comment(line);
    words = my_str_to_word_array(line, ", \t\n");
    return words;
}

char *get_next_line(FILE *f, int *nb_line)
{
    char *line = NULL;
    size_t s;
    char **words;

    while (1) {
        if (getline(&line, &s, f) < 0)
            return free(line), NULL;
        re_alloc(&line, my_strdup(line), 1);
        (nb_line) ? (*nb_line) += 1 : 0;
        words = my_str_to_word_array(line, "\t \n");
        if (line[0] == '#' || line[0] == '\n' || !words[0]) {
            free(line);
            line = NULL;
        } else {
            free_str_array(words);
            return line;
        }
        free_str_array(words);
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
    int rval;

    if (!f) {
        dprint(2, "Error while opening '%s'.\n", file);
        return 0;
    }
    if (has_error(file)) {
        fclose(f);
        return 0;
    }
    rval = write_file(f, get_output_file(file));
    fclose(f);
    return rval;
}
