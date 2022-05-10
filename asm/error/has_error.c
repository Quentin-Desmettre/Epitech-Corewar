/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** has_error.c
*/

#include "asm.h"

int error(FILE *f, char const *file)
{
    fclose(f);
    dprint(2, "Error in %s.\n", file);
    return 0;
}

char *get_name(char const *line, int max)
{
    char **words = my_str_to_word_array(line, "\"");
    char *new = my_strdup(words[1]);

    free_str_array(words);
    if (my_strlen(new) > max) {
        free(new);
        return NULL;
    }
    return new;
}

int check_comment(FILE *f, char const *file)
{
    char *line;
    char **words;
    int len;

    if (!(line = get_next_line(f)))
        return error(f, file);
    words = my_str_to_word_array(line, " \t\n");
    if (my_strcmp(words[0], ".comment"))
        return fseek(f, -my_strlen(line), SEEK_CUR) ? 1 : 1;
    if (!words[0] || !words[1])
        return error(f, file);
    len = my_str_array_len(words);
    if (count_occurences('"', line) != 2 || words[1][0] != '"' ||
    words[len - 1][my_strlen(words[len - 1]) - 1] != '"')
        return error(f, file);
    line = get_name(line, COMMENT_LENGTH);
    if (!line)
        return error(f, file);
    free(line);
    return 1;
}

int check_name(FILE *f, char const *file)
{
    char *line;
    char **words;
    int len;

    line = get_next_line(f);
    if (!line)
        return error(f, file);
    words = my_str_to_word_array(line, " \t\n");
    if (!words[0] || my_strcmp(words[0], ".name") || !words[1])
        return error(f, file);
    len = my_str_array_len(words);
    if (count_occurences('"', line) != 2 || words[1][0] != '"' ||
    words[len - 1][my_strlen(words[len - 1]) - 1] != '"')
        return error(f, file);
    line = get_name(line, PROG_NAME_LENGTH);
    if (!line)
        return error(f, file);
    free(line);
    return 1;
}

int has_error(char const *file)
{
    FILE *f = fopen(file, "r");

    if (!f)
        return dprint(2, "Error: Cannot open '%s'.\n", file) ? 1 : 1;
    if (!check_name(f, file) || !check_comment(f, file))
        return 1;
    if (get_error_for(f, file))
        return 1;
    return 0;
}
