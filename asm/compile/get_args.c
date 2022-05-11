/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** get_args.c
*/

#include "asm.h"

static void get_reg(char *word, command_t *c)
{
    int8_t tmp = my_getnbr(word + 1, NULL);

    my_memcpy(c->params + c->cmd_size, &tmp, 1);
    c->cmd_size += 1;
}

static void get_ind(command_t *c, char *word)
{
    int16_t tmp = 0;

    if (word[0] == LABEL_CHAR) {
        add_int16t(c, 0);
        c->label_sizes[c->nb_label] = 2;
        c->labels[c->nb_label] = my_strdup(word + 1);
        c->label_pos[c->nb_label] = c->cmd_size - 2;
        c->nb_label++;
    } else {
        tmp = getnbr_overflow(word);
        convert_endian_short(&tmp);
        add_int16t(c, tmp);
    }
}

static void get_dir(char *name, char *word, command_t *c, int i)
{
    int16_t tmp_16t;
    int32_t tmp = getnbr_overflow(word + 1);
    int is_index = has_index(name, i);

    if (word[1] == LABEL_CHAR) {
        if (is_index) {
            add_int16t(c, 0);
            c->label_sizes[c->nb_label] = 2;
        } else {
            add_int32t(c, 0);
            c->label_sizes[c->nb_label] = 4;
        }
        c->labels[c->nb_label] = my_strdup(word + 2);
        c->label_pos[c->nb_label] = c->cmd_size - c->label_sizes[c->nb_label];
        c->nb_label++;
    } else {
        if (has_index(name, i)) {
            tmp_16t = tmp;
            convert_endian_short(&tmp_16t);
            add_int16t(c, tmp_16t);
        } else {
            convert_endian(&tmp);
            add_int32t(c, tmp);
        }
    }
}

static void get_args(command_t *c, char **words)
{
    char type;
    char *message = NULL;

    for (int i = 1; words[i]; i++) {
        type = type_of_arg(words[i], &message);
        if (type == T_REG)
            get_reg(words[i], c);
        if (type == T_DIR)
            get_dir(words[0], words[i], c, i);
        if (type == T_IND)
            get_ind(c, words[i]);
    }
}

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
