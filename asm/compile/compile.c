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
    char *labels[3];
    int nb_label;
} command_t;

int is_in_bounds(int nb, int low, int up);

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

int str_is_num_signed(char const *str)
{
    int start = (str[0] == '-') ? 1 : 0;

    return str_is_num(str + start);
}

char type_of_arg(char const *arg)
{
    if (!arg[0])
        return T_ERROR;
    if (arg[0] == 'r')
        return (arg[1] && str_is_num(arg + 1) && is_in_bounds(my_getnbr(
        arg + 1, NULL), 0, REG_NUMBER + 1)) ? T_REG : T_ERROR;
    if (arg[0] == DIRECT_CHAR) {
        if (arg[1] == LABEL_CHAR)
            return (arg[2] && contain_only(arg + 2,
            LABEL_CHARS)) ? T_DIR : T_ERROR;
        return (arg[1] && str_is_num_signed(arg + 1)) ? T_DIR : T_ERROR;
    }
    if (arg[0] == LABEL_CHAR)
        return (arg[1] && contain_only(arg + 1, LABEL_CHARS)) ? T_IND : T_ERROR;
    return str_is_num_signed(arg) ? T_IND : T_ERROR;
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

void convert_endian(int *nbr)
{
    int left = (((*nbr >> 24) & 0xff) | ((*nbr << 8) & 0xff0000));
    int right = (((*nbr >> 8) & 0xff00) | ((*nbr << 24) & 0xff000000));

    *nbr = left | right;
}

unsigned my_pow(unsigned nb, unsigned power)
{
    unsigned res = 1;

    for (unsigned i = 0; i < power; i++)
        res *= nb;
    return res;
}

int getnbr_overflow(char *str)
{
    int nb = 0;
    int len = my_strlen(str);

    for (int i = 0; len - i > 0; i++) {
        if (str[len - i - 1] == '-') {
            nb *= -1;
            break;
        }
        nb += (str[len - i - 1] - '0') * my_pow(10, i);
    }
    return nb;
}

void convert_endian_short(short *nbr)
{
    short swapped = (*nbr >> 8) | (*nbr << 8);

    *nbr = swapped;
}

int has_index(char **words, int nb_arg)
{
    int code = code_of(words[0]);

    if (code == 9)
        return 1;
    if ((code == 10 || code == 14) && nb_arg < 3)
        return 1;
    if (code == 11 && nb_arg > 1)
        return 1;
    if (code == 12 || code == 15)
        return 1;
    return 0;
}

void get_args(command_t *c, char **words)
{
    char type;
    char tmp_char;
    uint16_t tmp_16t = 0;
    int32_t tmp;

    for (int i = 1; words[i]; i++) {
        type = type_of_arg(words[i]);
        if (type == T_REG) {
            tmp_char = my_getnbr(words[i] + 1, NULL);
            my_memcpy(c->params + c->cmd_size, &tmp_char, 1);
            c->cmd_size += 1;
        }
        if (type == T_DIR) {
            if (words[i][1] == LABEL_CHAR) {
                tmp_16t = 0;
                my_memcpy(c->params + c->cmd_size, &tmp_16t, IND_SIZE);
                c->cmd_size += IND_SIZE;
                c->labels[c->nb_label] = my_strdup(words[i] + 2);
                c->nb_label++;
            } else {
                tmp = getnbr_overflow(words[i] + 1);
                if (has_index(words, i)) {
                    tmp_16t = tmp;
                    my_memcpy(c->params + c->cmd_size, &tmp_16t, IND_SIZE);
                    c->cmd_size += IND_SIZE;
                } else {
                    convert_endian(&tmp);
                    my_memcpy(c->params + c->cmd_size, &tmp, DIR_SIZE);
                    c->cmd_size += DIR_SIZE;
                }
            }
        }
        if (type == T_IND) {
            if (words[i][0] == LABEL_CHAR) {
                tmp_16t = 0;
                my_memcpy(c->params + c->cmd_size, &tmp_16t, IND_SIZE);
                c->cmd_size += IND_SIZE;
                c->labels[c->nb_label] = my_strdup(words[i] + 2);
                c->nb_label++;
            } else {
                tmp_16t = getnbr_overflow(words[i]);
                convert_endian_short(&tmp_16t);
                my_memcpy(c->params + c->cmd_size, &tmp_16t, IND_SIZE);
                c->cmd_size += IND_SIZE;
            }
        }
    }
}

int is_special_case(int code)
{
    return (code == 1) || (code == 9) || (code == 12) || (code == 15);
}

command_t *create_command(char **words, command_t *prev)
{
    command_t *c = malloc(sizeof(command_t));

    c->offset = (prev ? prev->offset + prev->cmd_size : 0);
    c->code = code_of(words[0]);
    if (!is_special_case(c->code))
        c->coding_byte = coding_byte_for(words);
    get_args(c, words);
    return c;
}

int write_command(command_t *cmd, int fd)
{
    int size = 0;

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

static void save_name(header_t *header, char *line)
{
    char *name = get_name(line, PROG_NAME_LENGTH);

    my_strcpy(header->prog_name, name);
    free(name);
}

void get_comment(header_t *header, char *line)
{
    char **words = my_str_to_word_array(line, "\"");

    my_strcpy(header->comment, words[1]);
    free_str_array(words);
}

int write_file(FILE *f, char const *output)
{
    char *line;
    char **words;
    file_buffer_t buf;
    command_t *tmp;

    my_memset(&buf, 0, sizeof(file_buffer_t));
    buf.header.magic = COREWAR_EXEC_MAGIC;
    convert_endian(&buf.header.magic);
    while ((line = get_next_line(f))) {
        words = my_str_to_word_array(line, ", \t\n");
        if (!my_strcmp(words[0], ".name"))
            save_name(&buf.header, line);
        else if (!my_strcmp(words[0], ".comment"))
            get_comment(&buf.header, line);
        else {
            tmp = create_command(words, buf.commands ? buf.commands->prev->data : NULL);
            append_node(&buf.commands, tmp);
        }
        free_str_array(words);
        free(line);
    }
    if (errno) {
        printf("file error\n");
        return 0;
    }
    //resolve_labels(&buf);
    return write_buffer(&buf, output);
}
