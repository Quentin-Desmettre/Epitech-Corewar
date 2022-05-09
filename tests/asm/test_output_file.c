/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** test.c
*/

#include <criterion/criterion.h>
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
}

Test (next_line, get_next_line)
{
    FILE *f = fopen("tmp_file", "w");
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

    for (int i = 0; i < 7; i++)
        fwrite(strings[i], 1, my_strlen(strings[i]), f);
    fclose(f);
    f = fopen("tmp_file", "r");
    for (int i = 0; i < 7; i++) {
        tmp = get_next_line(f);
        if (i == 2 || i == 5)
            i++;
        cr_assert_str_eq(tmp, strings[i]);
    }
    cr_assert(get_next_line(f) == NULL);
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
    cr_assert(type_of_arg("r4") == T_REG);
    cr_assert(type_of_arg("%8") == T_DIR);
    cr_assert(type_of_arg(":label") == T_IND);
    cr_assert(type_of_arg("7") == T_IND);
    cr_assert(type_of_arg("aa") == T_ERROR);
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
