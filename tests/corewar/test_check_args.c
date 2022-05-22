/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** test_check_args.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "op.h"
#undef exit

Test (get_CodingByte, test_get_coding_byte, .init=cr_redirect_stdout)
{
    args_t *args = malloc(sizeof(args_t));

    my_memset(args, 0, sizeof(args_t));
    get_coding_byte(0x78, args);
    cr_assert(args->type[0] == T_REG);
    cr_assert(args->type[1] == T_IND);
    cr_assert(args->type[2] == T_DIR);
}

Test (num_of_args, test_num_of_args, .init=cr_redirect_stdout)
{
    args_t *args = malloc(sizeof(args_t));

    my_memset(args, 0, sizeof(args_t));
    get_coding_byte(0x78, args);
    cr_assert(number_of_args(args) == 3);
    my_memset(args, 0, sizeof(args_t));
    cr_assert(number_of_args(args) == 0);
}

Test (are_types_valid_func, test_are_types_valid, .init=cr_redirect_stdout)
{
    args_t *args = malloc(sizeof(args_t));
    int live = 1;
    int sti = 11;

    my_memset(args, 0, sizeof(args_t));
    args->type[0] = T_DIR;
    cr_assert(are_types_valid(args, live, 1) == 1);
    args->type[0] = T_REG;
    args->type[1] = T_REG;
    args->type[2] = T_IND;
    cr_assert(are_types_valid(args, sti, 3) == 0);
}

Test (i_has_index_func, test_i_has_index, .init=cr_redirect_stdout)
{
    int live = 1;
    int zjump = 9;
    int ldi = 10;
    int lldi = 14;
    int sti = 11;
    int fork = 12;
    int lfork = 15;

    cr_assert(i_has_index(zjump, 1) == 1);
    cr_assert(i_has_index(ldi, 2) == 1);
    cr_assert(i_has_index(lldi, 2) == 1);
    cr_assert(i_has_index(lldi, 3) == 0);
    cr_assert(i_has_index(sti, 2) == 1);
    cr_assert(i_has_index(fork, 2) == 1);
    cr_assert(i_has_index(lfork, 2) == 1);
    cr_assert(i_has_index(live, 2) == 0);
}

Test (size_of_arg_func, test_size_of_arg)
{
    int zjump = 9;
    char types[3] = {'2', T_REG, T_IND};
    int cr_return_value[4] = {IND_SIZE, 1, IND_SIZE, DIR_SIZE};

    for (int i = 0; i < 3; i++) {
        cr_assert(size_of_arg(zjump, i, types) == cr_return_value[i]);
    }
    cr_assert(size_of_arg(4, 0, types) == cr_return_value[3]);
}
