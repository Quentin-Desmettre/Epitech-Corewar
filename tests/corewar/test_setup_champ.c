/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** test_setup_champ.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "op.h"
#undef exit

Test (instruction_reader_func, test_instruction_reader,
.init=cr_redirect_stdout)
{
    champ_t *champ = malloc(sizeof(champ_t));
    char *map = malloc(sizeof(char) * (MEM_SIZE + 1));
    int live = 1;
    int add = 4;
    champ->param.champ_nbr = 2;

    my_memset(map, 0, MEM_SIZE);
    my_memset(champ, 0, sizeof(champ_t));
    map[0] = live;
    map[1] = champ->param.champ_nbr;
    instruction_reader(map, champ);
    cr_assert(champ->args.code == live);
    my_memset(map, 0, MEM_SIZE);
    my_memset(champ, 0, sizeof(champ_t));
    instruction_reader(map, champ);
    cr_assert(champ->pc == 1);
    champ->pc = 0;
    map[0] = 17;
    instruction_reader(map, champ);
    cr_assert(champ->pc == 1);
    champ->pc = 0;
    map[0] = add;
    map[1] = 0b01010100;
    map[2] = 1;
    map[3] = 3;
    map[4] = 6;
    instruction_reader(map, champ);
    cr_assert(champ->args.code == add);
}

Test (setup_all_champ_for_game_func, test_setup_all_champ_for_game,
.init=cr_redirect_stdout)
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
    setup_all_champ_for_game(&coucou);
    cr_assert(coucou == *get_champ_struct());
}

Test (setup_valid_num_func, test_setup_valid_num, .init=cr_redirect_stdout)
{
    champ_t *coucou = malloc(sizeof(champ_t));
    champ_t *suite = malloc(sizeof(champ_t));
    champ_t *follow = malloc(sizeof(champ_t));
    int valid_num[4] = {1, 2, 3, 4};
    int cmp[4] = {1, 0, 3, 4};

    my_memset(coucou, 0, sizeof(champ_t));
    my_memset(suite, 0, sizeof(champ_t));
    my_memset(follow, 0, sizeof(champ_t));
    coucou->next = suite;
    suite->next = follow;
    follow->next = NULL;
    coucou->param.champ_nbr = 1;
    suite->param.champ_nbr = 2;
    suite->param.nb_is_impose = 1;
    follow->param.champ_nbr = 4;
    setup_valid_num(&coucou, &valid_num);
    for (int i = 0; i < 4; i++)
        cr_assert(valid_num[i] == cmp[i]);
}

Test (set_champ_real_num_func, test_set_champ_real_num,
.init=cr_redirect_stderr)
{
    champ_t *coucou = malloc(sizeof(champ_t));
    champ_t *suite = malloc(sizeof(champ_t));
    champ_t *follow = malloc(sizeof(champ_t));
    int valid_num[4] = {1, 2, 3, 4};

    my_memset(coucou, 0, sizeof(champ_t));
    my_memset(suite, 0, sizeof(champ_t));
    my_memset(follow, 0, sizeof(champ_t));
    coucou->next = suite;
    suite->next = follow;
    follow->next = NULL;
    coucou->param.champ_nbr = 8;
    suite->param.champ_nbr = 2;
    suite->param.nb_is_impose = 1;
    follow->param.champ_nbr = 4;
    setup_valid_num(&coucou, &valid_num);
    set_champ_real_num(&coucou, &valid_num);
    cr_assert(coucou->param.champ_nbr == 1);
    cr_assert(suite->param.champ_nbr == 2);
    cr_assert(follow->param.champ_nbr == 3);
}

Test (check_same_nbr_func, test_check_same_nbr, .init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    for (int i = 0; i < 5; i++)
        param->num_impose[i] = 0;
    cr_assert(check_same_nbr(param) == 0);
    param->num_impose[1] = 4;
    param->num_impose[3] = 4;
    cr_assert(check_same_nbr(param) == 1);
}
