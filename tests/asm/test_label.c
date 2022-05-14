/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** test_label.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <wait.h>
#include "asm.h"

Test (has_double, has_double, .init=cr_redirect_stderr)
{
    list_t *list = NULL;

    append_node(&list, create_label("test11", NULL));
    append_node(&list, create_label("test22", NULL));
    cr_assert(has_double(list) == 0);

    append_node(&list, create_label("test11", NULL));
    cr_assert(has_double(list) == 1);

    cr_assert(has_double(NULL) == 0);
}

Test (get_label_pos, get_label_pos)
{
    command_t *c = create_null_command(NULL);
    list_t *labels = NULL;
    c->offset = 69;
    int error;

    cr_assert(get_label_pos(NULL, "yolo", &error) == 0);
    cr_assert(error == 1);

    append_node(&labels, create_label("test11", c));
    append_node(&labels, create_label("test22", create_null_command(c)));
    cr_assert(get_label_pos(labels, "test1", &error) == 69);
    cr_assert(error == 0);

    cr_assert(get_label_pos(labels, "test", &error) == 0);
    cr_assert(error == 1);
}

Test (resolve_labels, resolve_labels)
{
    file_buffer_t buf = {};
    command_t c = {};

    c.nb_label = 2;
    c.labels[0] = my_strdup("yolo");
    c.labels[1] = strdup("bobby");
    c.label_sizes[0] = 2;
    c.label_sizes[1] = 2;
    c.offset = 0;
    c.label_pos[0] = 0;
    c.label_pos[1] = 2;
    c.params[0] = 13;
    c.params[1] = 0;
    c.params[2] = 15;
    c.params[3] = 0;

    append_node(&buf.labels, create_label("yolo:", &c));
    append_node(&buf.labels, create_label("bobby:", &c));
    append_node(&buf.commands, &c);
    resolve_labels(&buf);

}
