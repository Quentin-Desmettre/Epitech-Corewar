/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** compile.c
*/

#include "asm.h"

int is_label_valid(char const *arg);

static void save_name(header_t *header, char *line)
{
    char *name = get_name(line, PROG_NAME_LENGTH);
    int len = my_strlen(name);

    if (name[len - 1] == '\n')
        name[len - 1] = 0;
    my_strcpy(header->prog_name, name);
    free(name);
}

static void get_comment(header_t *header, char *line)
{
    char *comment = get_name(line, COMMENT_LENGTH);
    int len = my_strlen(comment);

    if (comment[len - 1] == '\n')
        comment[len - 1] = 0;
    my_strcpy(header->comment, comment);
    free(comment);
}

static label_t *create_label(char const *name, command_t *cmd)
{
    label_t *l = malloc(sizeof(label_t));

    l->name = my_strdup(name);
    l->name[my_strlen(l->name) - 1] = 0;
    l->cmd = cmd;
    return l;
}

char **split_next_line(FILE *f, int *nb_line)
{
    char *line = get_next_line(f, NULL);
    char **words = my_str_to_word_array(line, ", \t\n");

    while (!words[0]) {
        free(line);
        free_str_array(words);
        line = get_next_line(f, nb_line);
        if (!line)
            return NULL;
        words = my_str_to_word_array(line, ", \t\n");
    }
    free(line);
    return words;
}

static void get_data(char **words, file_buffer_t *buf, char *line)
{
    command_t *tmp;
    int is_label = 0;
    char *label_name;

    if (!my_strcmp(words[0], ".name"))
        save_name(&buf->header, line);
    else if (!my_strcmp(words[0], ".comment"))
        get_comment(&buf->header, line);
    else {
        // get_labels
        is_label = is_label_valid(words[0]);
        if (is_label && !words[1]) {
            label_name = my_strdup(words[0]);
            words = split_next_line(buf->f, NULL) - 1;
        } else if (is_label)
            label_name = my_strdup(words[0]);
        // create_command, starting after the last label
        tmp = create_command(words + is_label,
        buf->commands ? buf->commands->prev->data : NULL);
        append_node(&buf->commands, tmp);
        // add all the labels
        if (is_label)
            append_node(&buf->labels, create_label(label_name, tmp));
    }
}

void replace_comment(char *line)
{
    int idx = index_of('#', line);

    if (idx >= 0)
        line[idx] = 0;
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
    if (errno)
        return dprint(2, "Error while reading file.\n") ? 0 : 0;
    if (!resolve_labels(&buf))
        return 0;
    return write_buffer(&buf, output);
}
