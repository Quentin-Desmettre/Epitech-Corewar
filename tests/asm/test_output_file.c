/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** test.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <wait.h>
#include "asm.h"

Test (output_file, output_file_test_output_file)
{
    char const *f = get_output_file("abel.s");
    cr_assert_str_eq(f, "abel.cor");

    f = get_output_file("abel.");
    cr_assert_str_eq(f, "abel..cor");

    f = get_output_file("abel.ss");
    cr_assert_str_eq(f, "abel.ss.cor");

    f = get_output_file(".s");
    cr_assert_str_eq(f, ".cor");

    f = get_output_file("s");
    cr_assert_str_eq(f, "s.cor");

    f = get_output_file("./test/abel.s");
    cr_assert_str_eq(f, "abel.cor");
}

Test (next_line, get_next_line)
{
    FILE *f = fopen("/tmp/tmp_file", "w");
    char const *strings[] = {
        "ligne1\n",
        "ligne2\n",
        "#putee\n",
        "ligne3\n",
        "ligne4\n",
        "\n",
        "ligne5\n",
    };
    char *tmp;
    int line = 0;

    for (int i = 0; i < 7; i++)
        fwrite(strings[i], 1, my_strlen(strings[i]), f);
    fclose(f);
    f = fopen("tmp_file", "r");
    for (int i = 0; i < 7; i++) {
        tmp = get_next_line(f, &line);
        if (i == 2 || i == 5)
            i++;
        cr_assert_eq(line, i + 1);
        cr_assert_str_eq(tmp, strings[i]);
    }
    cr_assert(get_next_line(f, NULL) == NULL);
    fclose(f);
}

Test (progsize_offset, progsize_offset)
{
    header_t s;
    size_t offset = (void *)&s.prog_size - (void *)&s;

    cr_assert(progsize_offset() == offset);
}

Test (code_of, code_of)
{
    cr_assert(code_of("live") == 1);
    cr_assert(code_of("sti") == 11);
    cr_assert(code_of("error") == -1);
}

Test (type_of_arg, type_of_arg)
{
    char *err_mess = "yolo";

    cr_assert(type_of_arg("r4", &err_mess) == T_REG);
    cr_assert(type_of_arg("%8", &err_mess) == T_DIR);
    cr_assert(type_of_arg(":label", &err_mess) == T_IND);
    cr_assert(type_of_arg("7", &err_mess) == T_IND);

    cr_assert(type_of_arg("aa", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid indirect");

    cr_assert(type_of_arg("r0", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid register");

    cr_assert(type_of_arg("r-1", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid register");

    cr_assert(type_of_arg("r16", &err_mess) == T_REG);
    cr_assert(type_of_arg("r17", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid register");

    cr_assert(type_of_arg("r", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid register");

    cr_assert(type_of_arg("%:hi", &err_mess) == T_DIR);
    cr_assert(type_of_arg("%::hi", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid direct");

    cr_assert(type_of_arg("%89:", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid direct");

    cr_assert(type_of_arg("%:èè", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid direct");

    cr_assert(type_of_arg("%-2", &err_mess) == T_DIR);
    cr_assert(type_of_arg("%:", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid direct");

    cr_assert(type_of_arg("%", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid direct");

    cr_assert(type_of_arg(":", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid indirect");

    cr_assert(type_of_arg(":hi", &err_mess) == T_IND);
    cr_assert(type_of_arg(":", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid indirect");
    cr_assert(type_of_arg(":hi", &err_mess) == T_IND);
    cr_assert(type_of_arg("-7878", &err_mess) == T_IND);
    cr_assert(type_of_arg("--67", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid indirect");
    cr_assert(type_of_arg("::", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid indirect");
    cr_assert(type_of_arg("%-", &err_mess) == T_DIR);
    cr_assert(type_of_arg("6767", &err_mess) == T_IND);
    cr_assert(type_of_arg("-", &err_mess) == T_IND);
    cr_assert(type_of_arg("", &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Invalid argument");
}

Test (coding_byte, coding_byte)
{
    char *words[] = {
        "truc", "r2", "23", "%34", NULL
    };
    cr_assert(coding_byte_for(words) == 0x78);

    char *words2[] = {
        "truc", "23", "45", "%34", NULL
    };
    cr_assert(coding_byte_for(words2) == 0xF8);

    char *words3[] = {
        "truc", "r1", "r3", "34", NULL
    };
    cr_assert(coding_byte_for(words3) == 0x5C);
}

Test (getnbr, getnbr)
{
    cr_assert(getnbr_overflow("35") == 35);
    cr_assert(getnbr_overflow("-35") == -35);
}

Test (check_command, check_command)
{
    char *args[] = {
        ".comment",
        NULL
    };
    char *err_mess;

    cr_assert(check_command(args, &err_mess) == 0);
    cr_assert_str_eq(err_mess, "Invalid op code");

    char *args2[] = {
        "live",
        "r3",
        "r4",
        NULL
    };
    cr_assert(check_command(args2, &err_mess) == 0);

    char *args3[] = {
        "live",
        "r2",
        NULL
    };
    cr_assert(check_command(args3, &err_mess) == 0);

    char *args4[] = {
        "live",
        "%234",
        NULL
    };
    cr_assert(check_command(args4, &err_mess) == 1);

    char *args5[] = {
        "live",
        "234",
        NULL
    };
    cr_assert(check_command(args5, &err_mess) == T_ERROR);
    cr_assert_str_eq(err_mess, "Incompatible argument type");

}

Test (get_name, get_name)
{
    cr_assert(get_name(".name \"some random name\"", 10) == NULL);
    cr_assert_str_eq(get_name(".name \"abel\"", 10), "abel");
}

void redirect_stdout()
{
    cr_redirect_stderr();
}

Test (error, error, .init = redirect_stdout)
{
    FILE *f = fopen("/dev/random", "r");
    cr_assert(error(f, "test", "file", 0) == 0);
    cr_assert_stderr_eq_str("file: Error on line 0. Reason: test.\n");
}

Test (is_label_valid, is_label_valid)
{
    cr_assert(is_label_valid("") == 0);
    cr_assert(is_label_valid("a") == 0);
    cr_assert(is_label_valid("::") == 0);
    cr_assert(is_label_valid("é:") == 0);
    cr_assert(is_label_valid("e:") == 1);
}

Test (replace_comment, replace_comment)
{
    char str[] = ";";

    replace_comment(str);
    cr_assert_str_eq(str, ";");
    char str2[] = ";#";
    replace_comment(str2);
    cr_assert_str_eq(str2, ";");
}

Test (split_next_line, split_next_line)
{
    FILE *f = fopen("./tests/empty.s", "r");
    char **words = 0;
    char *expected1[] = {".name", "\"42\""};
    char *expected2[] = {".comment", "\"Just", "a", "basic", "Winner", "Program\""};

    cr_assert(split_next_line(&words, f, NULL) == NULL);
    f = fopen("./tests/42.s", "r");

    words = split_next_line(&words, f, NULL);
    for (int i = 0; words[i]; i++)
        cr_assert_str_eq(words[i], expected1[i]);

    words = split_next_line(&words, f, NULL);
    for (int i = 0; words[i]; i++)
        cr_assert_str_eq(words[i], expected2[i]);
}

Test (add_int16t, add_int16t)
{
    command_t *c = calloc(1, sizeof(command_t));

    add_int16t(c, 1);
    cr_assert(c->cmd_size == 2);
    cr_assert(*((int16_t *)c->params) == 1);
}

Test (add_int32t, add_int32t)
{
    command_t *c = calloc(1, sizeof(command_t));

    add_int32t(c, 1);
    cr_assert(c->cmd_size == 4);
    cr_assert(*((int32_t *)c->params) == 1);
}

Test (is_special_case, is_special_case)
{
    cr_assert(is_special_case(0) == 0);
    cr_assert(is_special_case(1) == 1);
    cr_assert(is_special_case(9) == 1);
    cr_assert(is_special_case(12) == 1);
    cr_assert(is_special_case(15) == 1);
}

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

Test (has_index, has_index)
{
    cr_assert(has_index("zjmp", 0) == 1);
    cr_assert(has_index("yolo", 1) == 0);
    cr_assert(has_index("ldi", 2) == 1);
    cr_assert(has_index("lldi", 2) == 1);
    cr_assert(has_index("ldi", 3) == 0);
    cr_assert(has_index("lldi", 3) == 0);
    cr_assert(has_index("sti", 1) == 0);
    cr_assert(has_index("sti", 2) == 1);
    cr_assert(has_index("fork", 0) == 1);
    cr_assert(has_index("lfork", 0) == 1);
}

Test (get_args, get_args)
{
    command_t *c = calloc(1, sizeof(command_t));

    get_args(c, (char *[]){"sti", "r1", ":truc", "%89", NULL});

    cr_assert(c->cmd_size == 5);
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

Test (everything, everything, .init=cr_redirect_stderr)
{
    cr_assert(compile_file("yolo") == 0);
    cr_assert(has_error("yolo") == 1);
    system("find tests/ -name \"*.s\" > /tmp/files");
    FILE *f = fopen("/tmp/files", "r");
    char *line = NULL;
    int my_exit_code;
    int ref_exit;

    if (!f)
        return;
    while ((line = get_next_line(f, NULL))) {
        line = my_str_to_word_array(line, "\n")[0];
        errno = 0;
        my_exit_code = compile_file(line) ? 0 : 84;
        if (!my_exit_code)
            system("mv *.cor my_cor");
        ref_exit = WEXITSTATUS(system(str_concat(3,
        "../tests/asm/functional/ref/asm ", line,
        " > /dev/null 2> /dev/null")));
        if (!ref_exit)
            system("mv *.cor ref_cor");
        cr_assert(my_exit_code == ref_exit);
        if (!ref_exit) {
            cr_assert(WEXITSTATUS(system("diff my_cor ref_cor")) == 0);
            system("rm my_cor ref_cor");
        }
    }
}
