/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** test_header.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "op.h"
#undef exit

Test (fill_header_champ_func_bad_size, test_fill_header_champ, .exit_code = 84,
.init=cr_redirect_stderr)
{
    champ_t *champ = malloc(sizeof(champ_t));
    champ_t *champ2 = malloc(sizeof(champ_t));

    my_memset(champ, 0, sizeof(champ_t));
    my_memset(champ2, 0, sizeof(champ_t));
    champ->next = champ2;
    champ2->next = NULL;
    champ->name_champ = "../tests/corewar/cor_binary/corrupted_size.cor";
    champ2->name_champ = "../tests/corewar/cor_binary/pdd.cor";
    fill_header_champ(&champ);
}

Test (fill_header_champ_func_bad_file, test_fill_header_champ, .exit_code = 84,
.init=cr_redirect_stderr)
{
    champ_t *champ = malloc(sizeof(champ_t));

    my_memset(champ, 0, sizeof(champ_t));
    champ->next = NULL;
    champ->name_champ = "test";
    fill_header_champ(&champ);
}

Test (fill_header_champ_func_bad_magic, test_fill_header_champ, .exit_code = 84,
.init=cr_redirect_stderr)
{
    champ_t *champ = malloc(sizeof(champ_t));

    my_memset(champ, 0, sizeof(champ_t));
    champ->next = NULL;
    champ->name_champ = "../tests/corewar/cor_binary/corrupted_magic.cor";
    fill_header_champ(&champ);
}

Test (fill_header_champ_func_bad_head, test_fill_header_champ, .exit_code = 84,
.init=cr_redirect_stderr)
{
    champ_t *champ = malloc(sizeof(champ_t));

    my_memset(champ, 0, sizeof(champ_t));
    champ->next = NULL;
    champ->name_champ = "../tests/corewar/cor_binary/corrupted_header.cor";
    fill_header_champ(&champ);
}

Test (fill_header_champ_func, test_fill_header_champ)
{
    champ_t *champ = malloc(sizeof(champ_t));
    champ_t *champ2 = malloc(sizeof(champ_t));

    my_memset(champ, 0, sizeof(champ_t));
    my_memset(champ2, 0, sizeof(champ_t));
    champ->next = champ2;
    champ2->next = NULL;
    champ->name_champ = "../tests/corewar/cor_binary/pdd.cor";
    champ2->name_champ = "../tests/corewar/cor_binary/pdd.cor";
    fill_header_champ(&champ);
    cr_assert(champ->header.magic == COREWAR_EXEC_MAGIC);
}
