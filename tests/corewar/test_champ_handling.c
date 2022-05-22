/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** test_champ_handling.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "op.h"
#undef exit

Test (get_num_of_champ_func, test_get_num_of_champ)
{
    champ_t *coucou = malloc(sizeof(champ_t));
    champ_t *suite = malloc(sizeof(champ_t));
    champ_t *follow = malloc(sizeof(champ_t));

    my_memset(coucou, 0, sizeof(champ_t));
    my_memset(suite, 0, sizeof(champ_t));
    my_memset(follow, 0, sizeof(champ_t));
    coucou->next = suite;
    suite->next = follow;
    follow->next = NULL;
    cr_assert(get_num_of_champ(&coucou) == 3);
}

Test (create_champ_func, test_create_champ_func, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    create_champ("test", param, NULL);
}

Test (create_champ_func_work, test_create_champ_func_work)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));
    champ_t *info_champ = NULL;

    my_memset(param, 0, sizeof(param_argv_t));
    create_champ("../tests/corewar/cor_binary/pdd.cor", param, &info_champ);
    param->num_impose[0] = 8;
    param->index = 0;
    create_champ("../tests/corewar/cor_binary/pdd.cor", param, &info_champ);
    param->num_impose[0] = 0;
    create_champ("../tests/corewar/cor_binary/pdd.cor", param, &info_champ);
    for (int i = 0; i < 3; i++) {
        cr_assert(my_strcmp("../tests/corewar/cor_binary/pdd.cor",
        info_champ->name_champ) == 0);
        info_champ = info_champ->next;
    }
}

Test (sort_champ_func, test_sort_champ_func)
{
    champ_t *coucou = malloc(sizeof(champ_t));
    champ_t *suite = malloc(sizeof(champ_t));
    champ_t *follow = malloc(sizeof(champ_t));
    champ_t *tmp = NULL;

    my_memset(coucou, 0, sizeof(champ_t));
    my_memset(suite, 0, sizeof(champ_t));
    my_memset(follow, 0, sizeof(champ_t));
    coucou->next = suite;
    suite->next = follow;
    follow->next = NULL;
    coucou->param.champ_nbr = 3;
    suite->param.champ_nbr = 2;
    follow->param.champ_nbr = 1;
    tmp = sort_my_list(coucou);
    for (int i = 0; i < 3; i++) {
        cr_assert(tmp->param.champ_nbr == i + 1);
        tmp = tmp->next;
    }
}

Test (exec_instruction_func, check_exec_instruction)
{
    champ_t *champ = malloc(sizeof(champ_t));
    char *map = malloc(sizeof(char) * (MEM_SIZE + 1));

    my_memset(champ, 0, sizeof(champ_t));
    my_memset(map, 0, sizeof(char) * (MEM_SIZE));
    champ->instruction = malloc(sizeof(char) * 20);
    my_memset(champ->instruction, 0, sizeof(char) * 20);
    champ->instruction[0] = 4;
    champ->instruction[1] = 0b01010100;
    champ->instruction[2] = 1;
    champ->instruction[3] = 3;
    champ->instruction[4] = 6;
    champ->args.code = 4;
    exec_instructions(champ, map);
    cr_assert(champ->cycle_to_wait == -1);
    cr_assert(champ->cycle == 0);
}
