/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** test_compile2.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <wait.h>
#include "asm.h"

Test (getnbr, getnbr)
{
    cr_assert(getnbr_overflow("35") == 35);
    cr_assert(getnbr_overflow("-35") == -35);
}

Test (split_next_line, split_next_line)
{
    FILE *f = fopen("./tests/empty.s", "r");
    char **words = 0;
    char *expected1[] = {".name", "\"42\""};
    char *expected2[] = {".comment", "\"Just", "a",
    "basic", "Winner", "Program\""};

    if (!f)
        return;
    cr_assert(split_next_line(&words, f, NULL) == NULL);
    f = fopen("./tests/42.s", "r");
    if (!f)
        return;
    words = split_next_line(&words, f, NULL);
    for (int i = 0; words[i]; i++)
        cr_assert_str_eq(words[i], expected1[i]);

    words = split_next_line(&words, f, NULL);
    for (int i = 0; words[i]; i++)
        cr_assert_str_eq(words[i], expected2[i]);
}

Test (everything, everything, .init=cr_redirect_stderr)
{
    cr_assert(compile_file("yolo") == 0);
    cr_assert(has_error("yolo") == 1);
    system("find ../tests/asm/functional/tests -name \"*.s\" > /tmp/files");
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
            cr_expect(WEXITSTATUS(system("diff my_cor ref_cor")) == 0);
            system("rm my_cor ref_cor");
        }
    }
}
