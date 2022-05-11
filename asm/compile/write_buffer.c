/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** write_buffer.c
*/

#include "asm.h"

static int write_command(command_t *cmd, int fd)
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
