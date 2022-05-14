/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** test_write_buffer.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <wait.h>
#include "asm.h"

Test (create_command, create_command)
{
    command_t special = {.is_special = 1};
    command_t not_special = {.is_special = 0};
    command_t *c = create_command((char *[]){"live", "%234", NULL}, NULL);

    cr_assert(c->is_special == 1);
    cr_assert(c->code == 1);

    c = create_command((char *[]){"ld", "%3", "r1", NULL}, &special);
    cr_assert(c->offset == 1);

    c = create_command((char *[]){"ld", "%3", "r1", NULL}, &not_special);
    cr_assert(c->offset == 2);
}

Test (create_label, create_label)
{
    label_t *l = create_label("yolo:", NULL);

    cr_assert_str_eq(l->name, "yolo");
    cr_assert(l->cmd == NULL);
}

Test (create_null_cmd, create_null_cmd)
{
    command_t *c = create_null_command(NULL);

    cr_assert(c->cmd_size == 0);
    cr_assert(c->offset == 0);
    c->is_special = 1;

    c = create_null_command(c);
    cr_assert(c->offset == 1);
    c->is_special = 0;

    c = create_null_command(c);
    cr_assert(c->offset == 3);
}

Test (write_command, write_command)
{
    command_t *c = malloc(sizeof(command_t));
    int param = 10;
    command_data2_t data = {};
    command_data2_t cmp;

    int pip[2];
    pipe(pip);

    c->code = 0;
    cr_assert(write_command(c, pip[1]) == 0);

    c->code = 1;
    data.code = 1;
    memcpy(c->params, &param, 4);
    memcpy(data.params, &param, 4);
    c->cmd_size = 4;

    cr_assert(write_command(c, pip[1]) == 5);
    read(pip[0], &cmp, sizeof(command_data2_t));

    cr_assert(memcmp(&data, &cmp, sizeof(command_data2_t)) == 0);;
}

Test (write_command2, write_command2)
{
    command_t *c = malloc(sizeof(command_t));
    int param = 10;
    command_data_t data = {};
    command_data_t cmp;

    int pip[2];
    pipe(pip);

    c->code = 0;
    cr_assert(write_command(c, pip[1]) == 0);

    c->code = 2;
    data.code = 2;
    c->coding_byte = 3;
    data.coding_byte = 3;
    memcpy(c->params, &param, 4);
    c->cmd_size = 4;
    memcpy(data.params, &param, 4);

    cr_assert(write_command(c, pip[1]) == 6);
    read(pip[0], &cmp, sizeof(command_data_t));

    cr_assert(memcmp(&data, &cmp, sizeof(command_data_t)) == 0);;
}

Test (write_buffer, write_buffer)
{
    file_buffer_t buf = {};
    command_t *c = create_null_command(NULL);

    cr_assert(write_buffer(&buf, NULL) == 0);
    buf.commands = NULL;
    cr_assert(write_buffer(&buf, "/tmp/test1") == 1);
    append_node(&buf.commands, c);
    cr_assert(write_buffer(&buf, "/tmp/test2") == 1);
}
