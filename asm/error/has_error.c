/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** has_error.c
*/

#include "asm.h"

int error(FILE *f, char const *mess, char const *file, int line)
{
    fclose(f);
    dprint(2, "%s: Error on line %d. Reason: %s.\n", file, line, mess);
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

int check_comment(FILE *f, char const *file, int *nb_line)
{
    char *line;
    char **words;
    int len;

    if (!(line = get_next_line(f, nb_line)))
        return dprint(2, "%s: Warning: Missing comment.\n", file) ? 1 : 1;
    words = my_str_to_word_array(line, " \t\n");
    if (my_strcmp(words[0], ".comment"))
        return (dprint(2, "%s: Warning: Missing comment.\n", file) *
        fseek(f, -my_strlen(line), SEEK_CUR) * 0) + 1;
    len = my_str_array_len(words);
    if (count_occurences('"', line) != 2 || words[1][0] != '"' ||
    words[len - 1][my_strlen(words[len - 1]) - 1] != '"')
        return error(f, "Invalid comment", file, *nb_line);
    line = get_name(line, COMMENT_LENGTH);
    if (!line)
        return error(f, "Invalid comment", file, *nb_line);
    free(line);
    return 1;
}

int check_name(FILE *f, char const *file, int *nb_line)
{
    char *line;
    char **words;
    int len;

    line = get_next_line(f, nb_line);
    if (!line)
        return error(f, "Invalid name", file, *nb_line);
    words = my_str_to_word_array(line, " \t\n");
    if (my_strcmp(words[0], ".name") || !words[1])
        return error(f, "Invalid name", file, *nb_line);
    len = my_str_array_len(words);
    if (count_occurences('"', line) != 2 || words[1][0] != '"' ||
    words[len - 1][my_strlen(words[len - 1]) - 1] != '"')
        return error(f, "Invalid name", file, *nb_line);
    line = get_name(line, PROG_NAME_LENGTH);
    if (!line)
        return error(f, "Invalid name", file, *nb_line);
    free(line);
    return 1;
}

int has_error(char const *file)
{
    FILE *f = fopen(file, "r");
    int line = 0;

    if (!f)
        return dprint(2, "Error: Cannot open '%s'.\n", file) ? 1 : 1;
    if (!check_name(f, file, &line) || !check_comment(f, file, &line) ||
    get_error_for(f, file, &line))
        return 1;
    fclose(f);
    return 0;
}
