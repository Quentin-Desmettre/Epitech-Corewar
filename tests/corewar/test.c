/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** test.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "op.h"
#undef exit

Test (glob_var, test_glob_var)
{
    int cmp = CYCLE_TO_DIE;
    champ_t *to_cmp = NULL;

    cr_assert(*get_cycle_to_die() == cmp);
    cr_assert(*get_champ_struct() == to_cmp);
}

Test (corewar_alive, test_corewar_alive, .exit_code = 0)
{
    champ_t *to_cmp = malloc(sizeof(champ_t));
    champ_t *ouais = malloc(sizeof(champ_t));
    champ_t *test = NULL;
    char *map = malloc(sizeof(char) * (MEM_SIZE + 1));
    my_memset(map, 0, MEM_SIZE);
    my_memset(to_cmp, 0, sizeof(champ_t));
    my_memset(ouais, 1, sizeof(champ_t));
    ouais->next = to_cmp;

    cr_assert(last_to_live(test) == test);
    cr_assert(last_to_live(to_cmp) == to_cmp);
    ouais->is_alive = 0;
    check_alive_champ(&ouais, -1, map);
}

Test (corewar_alive_champ, test_corewar_alive_champ, .exit_code = 0)
{
    champ_t *to_cmp = malloc(sizeof(champ_t));
    champ_t *ouais = malloc(sizeof(champ_t));
    champ_t *test = NULL;
    char *map = malloc(sizeof(char) * (MEM_SIZE + 1));
    my_memset(map, 0, MEM_SIZE);
    my_memset(to_cmp, 0, sizeof(champ_t));

    ouais->next = to_cmp;
    to_cmp->next = NULL;
    ouais->is_alive = 1;

    last_to_live(ouais);
    check_alive_champ(&ouais, 0, map);
}

Test (check_endian_convertor, test_check_endian_convertor)
{
    int test = 0x12345678;

    convert_endian(&test);
    cr_assert(test == 0x78563412);
    convert_endian(&test);
    cr_assert(test == 0x12345678);
}

Test (get_CodingByte, test_get_coding_byte)
{
    args_t *args = malloc(sizeof(args_t));

    my_memset(args, 0, sizeof(args_t));
    get_coding_byte(0x78, args);
    cr_assert(args->type[0] == T_REG);
    cr_assert(args->type[1] == T_IND);
    cr_assert(args->type[2] == T_DIR);
}

Test (num_of_args, test_num_of_args)
{
    args_t *args = malloc(sizeof(args_t));

    my_memset(args, 0, sizeof(args_t));
    get_coding_byte(0x78, args);
    cr_assert(number_of_args(args) == 3);
    my_memset(args, 0, sizeof(args_t));
    cr_assert(number_of_args(args) == 0);
}

Test (are_types_valid_func, test_are_types_valid)
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

Test (i_has_index_func, test_i_has_index)
{
    args_t *args = malloc(sizeof(args_t));
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

Test (instruction_reader_func, test_instruction_reader)
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

Test (setup_all_champ_for_game_func, test_setup_all_champ_for_game)
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

Test (corewar_alive_champ, test_corewar_alive_champ, .exit_code = 84)
{
    champ_t *coucou = malloc(sizeof(champ_t));
    my_memset(coucou, 0, sizeof(champ_t));
}
