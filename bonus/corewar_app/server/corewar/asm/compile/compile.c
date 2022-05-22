/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** compile.c
*/

#include "asm.h"

void save_name(header_t *header, char *line)
{
    char *name = get_name(line, PROG_NAME_LENGTH);
    int len = my_strlen(name);

    if (name[len - 1] == '\n')
        name[len - 1] = 0;
    my_strcpy(header->prog_name, name);
    free(name);
}

void get_comment(header_t *header, char *line)
{
    char *comment = get_name(line, COMMENT_LENGTH);
    int len = my_strlen(comment);

    if (comment[len - 1] == '\n')
        comment[len - 1] = 0;
    my_strcpy(header->comment, comment);
    free(comment);
}

char **get_labels(char ***base_words, FILE *f, int *nb_line)
{
    char **words = *base_words;
    char **labels = malloc(sizeof(char *));

    labels[0] = 0;
    while (is_label_valid(words[0])) {
        append_str_array(&labels, my_strdup(words[0]));
        if (words[1]) {
            *base_words = words + 1;
            return labels;
        }
        words = split_next_line(base_words, f, nb_line);
        if (!words)
            return labels;
    }
    *base_words = words;
    return labels;
}

void get_data(char **words, file_buffer_t *buf, char *line)
{
    command_t *tmp;
    char **labels;

    if (!my_strcmp(words[0], ".name"))
        return save_name(&buf->header, line);
    else if (!my_strcmp(words[0], ".comment"))
        return get_comment(&buf->header, line);

    labels = get_labels(&words, buf->f, NULL);
    if (words) {
        tmp = create_command(words,
        buf->commands ? buf->commands->prev->data : NULL);
    } else
        tmp = create_null_command(buf->commands ?
        buf->commands->prev->data : NULL);
    append_node(&buf->commands, tmp);
    for (int i = 0; labels[i]; i++)
        append_node(&buf->labels, create_label(labels[i], tmp));
}

int write_file(FILE *f, char const *output)
{
    char *line;
    char **words;
    file_buffer_t buf;

    my_memset(&buf, 0, sizeof(file_buffer_t));
    buf.header.magic = COREWAR_EXEC_MAGIC_REVERSED;
    buf.f = f;
    while ((line = get_next_line(f, NULL))) {
        replace_comment(line);
        words = my_str_to_word_array(line, ", \t\n");
        if (words[0])
            get_data(words, &buf, line);
        free_str_array(words);
        free(line);
    }
    if (!resolve_labels(&buf))
        return 0;
    return write_buffer(&buf, output);
}
