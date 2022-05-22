/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** test_check_champ.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "op.h"
#undef exit

Test (check_champ_error_func, check_champ_func, .exit_code = 84,
.init=cr_redirect_stderr)
{
    champ_t *champ = malloc(sizeof(champ_t));

    my_memset(champ, 0, sizeof(champ_t));
    champ->next = NULL;
    champ->name_champ = "../tests/corewar/cor_binary/pdd.cor";
    check_champ(&champ);
}

Test (check_champ_func, check_champ_func)
{
    champ_t *champ = malloc(sizeof(champ_t));
    champ_t *champ2 = malloc(sizeof(champ_t));

    my_memset(champ, 0, sizeof(champ_t));
    my_memset(champ2, 0, sizeof(champ_t));
    champ->next = champ2;
    champ2->next = NULL;
    champ->name_champ = "../tests/corewar/cor_binary/pdd.cor";
    champ2->name_champ = "../tests/corewar/cor_binary/pdd.cor";
    check_champ(&champ);
    cr_assert(champ->header.magic == COREWAR_EXEC_MAGIC);
}
