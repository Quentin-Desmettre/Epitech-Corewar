/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** test_get_args.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <wait.h>
#include "asm.h"

Test (get_reg_ind_dir, get_reg_ind_dir1)
{
    command_t *c = calloc(1, sizeof(command_t));

    get_reg("r1", c);
    cr_assert(c->params[0] == 1);
    cr_assert(c->cmd_size == 1);
    get_ind(c, ":label");
    cr_assert(c->nb_label == 1);
    cr_assert(c->cmd_size == 3);
    get_ind(c, "13");
    cr_assert(c->nb_label == 1);
    cr_assert(c->cmd_size == 5);
}

Test (get_reg_ind_dir, get_label)
{
    command_t *c = calloc(1, sizeof(command_t));

    get_label(0, c, "%:label");
    cr_assert(c->nb_label == 1);
    cr_assert(c->label_sizes[0] == 4);
    cr_assert_str_eq(c->labels[0], "label");

    get_label(1, c, "%:label");
    cr_assert(c->nb_label == 2);
    cr_assert(c->label_sizes[1] == 2);
    cr_assert_str_eq(c->labels[0], "label");
}

Test (get_reg_ind_dir, get_dir)
{
    command_t *c = calloc(1, sizeof(command_t));

    get_dir("sti", "%:label", c, 0);
    cr_assert(c->nb_label == 1);
    cr_assert_str_eq(c->labels[0], "label");

    int size = c->cmd_size;
    get_dir("sti", "%3", c, 2);
    cr_assert(c->nb_label == 1);
    cr_assert(c->cmd_size == size + 2);

    size = c->cmd_size;
    get_dir("sti", "%3", c, 0);
    cr_assert(c->nb_label == 1);
    cr_assert(c->cmd_size == size + 4);
}

Test (get_args, get_args)
{
    command_t *c = calloc(1, sizeof(command_t));

    get_args(c, (char *[]){"sti", "r1", ":truc", "%89", NULL});

    cr_assert(c->cmd_size == 5);
}
