/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** write_buffer.c
*/

#include "asm.h"

command_t *create_command(char **words, command_t *prev)
{
    command_t *c = malloc(sizeof(command_t));

    my_memset(c, 0, sizeof(command_t));
    if (prev) {
        c->offset = prev->offset + prev->cmd_size + 1;
        if (!prev->is_special)
            c->offset++;
    }
    c->code = code_of(words[0]);
    if (!is_special_case(c->code)) {
        c->coding_byte = coding_byte_for(words);
    } else
        c->is_special = 1;
    get_args(c, words);
    return c;
}

command_t *create_null_command(command_t *prev)
{
    command_t *c = malloc(sizeof(command_t));

    my_memset(c, 0, sizeof(command_t));
    if (prev) {
        c->offset = prev->offset + prev->cmd_size + 1;
        if (!prev->is_special)
            c->offset++;
    }
    return c;
}

label_t *create_label(char const *name, command_t *cmd)
{
    label_t *l = malloc(sizeof(label_t));

    l->name = my_strdup(name);
    l->name[my_strlen(l->name) - 1] = 0;
    l->cmd = cmd;
    return l;
}

int write_command(command_t *cmd, int fd)
{
    int size = 0;

    if (cmd->code == 0)
        return 0;
    size += write(fd, &cmd->code, 1);
    if (!is_special_case(cmd->code))
        size += write(fd, &cmd->coding_byte, 1);
    size += write(fd, cmd->params, cmd->cmd_size);
    return size;
}

int write_buffer(file_buffer_t *buf, char const *output)
{
    int fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    list_t *list = buf->commands;
    int i = 0;
    int prog_size = 0;

    if (fd < 0)
        return 0;
    write(fd, &buf->header, sizeof(header_t));
    while (1) {
        if (!list || (i && list == buf->commands))
            break;
        prog_size += write_command(list->data, fd);
        list = list->next;
        i = 1;
    }
    lseek(fd, progsize_offset(), SEEK_SET);
    convert_endian(&prog_size);
    write(fd, &prog_size, 4);
    close(fd);
    return 1;
}
