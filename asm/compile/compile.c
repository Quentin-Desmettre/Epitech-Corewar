/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** compile.c
*/

#include "asm.h"

static void save_name(header_t *header, char *line)
{
    char *name = get_name(line, PROG_NAME_LENGTH);

    my_strcpy(header->prog_name, name);
    free(name);
}

static void get_comment(header_t *header, char *line)
{
    char *comment = get_name(line, COMMENT_LENGTH);

    my_strcpy(header->comment, comment);
    free(comment);
}

static void get_data(char **words, file_buffer_t *buf, char *line)
{
    command_t *tmp;

    if (!my_strcmp(words[0], ".name"))
        save_name(&buf->header, line);
    else if (!my_strcmp(words[0], ".comment"))
        get_comment(&buf->header, line);
    else {
        tmp = create_command(words,
        buf->commands ? buf->commands->prev->data : NULL);
        append_node(&buf->commands, tmp);
    }
}

int write_file(FILE *f, char const *output)
{
    char *line;
    char **words;
    file_buffer_t buf;

    my_memset(&buf, 0, sizeof(file_buffer_t));
    buf.header.magic = COREWAR_EXEC_MAGIC;
    convert_endian(&buf.header.magic);
    while ((line = get_next_line(f))) {
        words = my_str_to_word_array(line, ", \t\n");
        get_data(words, &buf, line);
        free_str_array(words);
        free(line);
    }
    if (errno)
        return dprint(2, "Error while reading file.\n") ? 0 : 0;
    resolve_labels(&buf);
    return write_buffer(&buf, output);
}
