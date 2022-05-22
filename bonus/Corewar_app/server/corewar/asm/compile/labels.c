/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** labels.c
*/

#include "asm.h"

int has_copy(list_t *labels, label_t *lab, list_t *except)
{
    list_t *l = labels;
    label_t *cur;

    do {
        cur = l->data;
        if (l != except && !my_strcmp(lab->name, cur->name))
            return 1;
        l = l->next;
    } while (l != labels);
    return 0;
}

int has_double(list_t *labels)
{
    list_t *lab = labels;
    label_t *l;

    if (!lab)
        return 0;
    do {
        l = lab->data;
        if (has_copy(labels, l, lab))
            return dprint(2, "Error: Label '%s' defined multiple times.\n",
            l->name) ? 1 : 1;
        lab = lab->next;
    } while (lab != labels);
    return 0;
}

int32_t get_label_pos(list_t *labels, char const *name, int *not_found)
{
    list_t *begin = labels;
    label_t *lab;

    *not_found = 1;
    if (!begin)
        return 0;
    do {
        lab = labels->data;
        if (!my_strcmp(lab->name, name)) {
            *not_found = 0;
            return lab->cmd->offset;
        }
        labels = labels->next;
    } while (begin != labels);
    return 0;
}

int search_for_label(command_t *current, int index_of_label, list_t *labels)
{
    int error = 0;
    int32_t lab_pos = get_label_pos(labels,
    current->labels[index_of_label], &error);
    int32_t offset_32 = lab_pos - current->offset;
    int16_t offset = offset_32;

    if (error) {
        dprint(2, "Error: Label '%s' not found.\n",
        current->labels[index_of_label]);
        return 0;
    }
    convert_endian_short(&offset);
    convert_endian(&offset_32);
    if (current->label_sizes[index_of_label] == 2)
        my_memcpy(current->params + current->label_pos[index_of_label],
        &offset, 2);
    else
        my_memcpy(current->params + current->label_pos[index_of_label],
        &offset_32, 4);
    return 1;
}

int resolve_labels(file_buffer_t *buf)
{
    list_t *command = buf->commands;
    command_t *cmd;
    int cont = 1;
    int rcont = 1;

    if (!command || has_double(buf->labels))
        return !command ? 1 : 0;
    do {
        cmd = command->data;
        for (int i = 0; i < cmd->nb_label && cont; i++) {
            cont = search_for_label(cmd, i, buf->labels);
            rcont = cont;
            cont = (i + 1 < cmd->nb_label) ? 0 : cont;
        }
        if (!rcont)
            return 0;
        command = command->next;
    } while (command != buf->commands);
    return 1;
}
