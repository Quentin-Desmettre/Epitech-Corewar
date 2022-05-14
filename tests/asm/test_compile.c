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

    if (!f)
        return;
    for (int i = 0; i < 7; i++)
        fwrite(strings[i], 1, my_strlen(strings[i]), f);
    fclose(f);
    f = fopen("/tmp/tmp_file", "r");
    if (!f)
        return;
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

Test (replace_comment, replace_comment)
{
    char str[] = ";";

    replace_comment(str);
    cr_assert_str_eq(str, ";");
    char str2[] = ";#";
    replace_comment(str2);
    cr_assert_str_eq(str2, ";");
}
