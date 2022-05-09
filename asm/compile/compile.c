/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** compile.c
*/

#include "asm.h"

typedef struct {
    char code;
    uint8_t coding_byte;
    uint8_t params[MAX_ARGS_NUMBER * DIR_SIZE];
    int offset;
    int cmd_size;
    char *label;
} command_t;
/*

How to store a command:
    - store it's code
    - store it's coding byte
    - store it's params
    - compute the command size (sizeof(code) + sizeof(coding byte) + sizeof(params))
    - tell that the next command offset is my_offset + cmd_size

*/
typedef struct {
    command_t *cmd;
    char *name;
} label_t;

typedef struct {
    header_t header;
    list_t *commands;
    list_t *labels;
} file_buffer_t;

/*

steps:
    -log all commands, with their coding bytes and their parameters
        - if the command modifies the header, modify it

        - store the command in a command_t, and push it to the command_list.
            if the command is associated with a label, push to the label list:
                - the label name
                - the command_t previously pushed
            if the command contains a reference to a label, store the label name in the command_t
*/
/*

Once every command has been written, resolve labels.

    -for each command, if it has a label:
        - find the label in the label list;
            as each label in the list contains the command it is associated with, you can retrieve THE ADDRESS of the command it has to go to.
            so, when you have found the label, change in the command the value for the index to be THE ADDRESS

*/


size_t progsize_offset(void)
{
    return (size_t)(&((header_t *)NULL)->prog_size);
}

char code_of(char const *name)
{
    for (int i = 0; op_tab[i].mnemonique; i++)
        if (!my_strcmp(op_tab[i].mnemonique, name))
            return op_tab[i].code;
    return -1;
}

char type_of_arg(char const *arg)
{
    int error = 0;
    int nb;

    if (arg[0] == 'r')
        return T_REG;
    if (arg[0] == DIRECT_CHAR)
        return T_DIR;
    if (arg[0] == LABEL_CHAR || contain("12345678", arg[0]))
        return T_IND;
    return T_ERROR;
}

uint8_t coding_byte_for(char **words)
{
    uint8_t byte = 0;
    uint8_t bit_offset = 6;
    char type;

    for (int i = 1; words[i]; i++, bit_offset -= 2) {
        type = type_of_arg(words[i]);
        if (type == T_REG)
            byte |= 0b01 << bit_offset;
        if (type == T_DIR)
            byte |= 0b10 << bit_offset;
        if (type == T_IND)
            byte |= 0b11 << bit_offset;
    }
    return byte;
}

command_t *create_command(char **words, command_t *prev)
{
    command_t *c = malloc(sizeof(command_t));

    c->offset = (prev ? prev->offset + prev->cmd_size : 0);
    c->code = code_of(words[0]);
    c->coding_byte = coding_byte_for(words);
    return c;
}

int write_buffer(file_buffer_t *buf, char const *output)
{
    int fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0)
        return 0;
    write(fd, &buf->header, sizeof(header_t));
    close(fd);
    return 1;
}

int write_file(FILE *f, char const *output)
{
    char *line;
    char **words;
    file_buffer_t buf;
    command_t *tmp;

    my_memset(&buf, 0, sizeof(file_buffer_t));
    while ((line = get_next_line(f))) {
        words = my_str_to_word_array(line, ", \t");
        tmp = create_command(words, buf.commands ? buf.commands->prev->data : NULL);
    }
    if (errno) {
        printf("file error\n");
        return 0;
    }
    return write_buffer(&buf, output);
}
