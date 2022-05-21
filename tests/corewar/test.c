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

Test (glob_var, test_glob_var, .init=cr_redirect_stdout)
{
    int cmp = CYCLE_TO_DIE;
    champ_t *to_cmp = NULL;

    cr_assert(*get_cycle_to_die() == cmp);
    cr_assert(*get_champ_struct() == to_cmp);
}

Test (corewar_alive, test_corewar_alive, .exit_code = 0,
.init=cr_redirect_stdout)
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

Test (corewar_alive_champ, test_corewar_alive_champ, .exit_code = 0,
.init=cr_redirect_stdout)
{
    champ_t *to_cmp = malloc(sizeof(champ_t));
    champ_t *ouais = malloc(sizeof(champ_t));
    char *map = malloc(sizeof(char) * (MEM_SIZE + 1));
    my_memset(map, 0, MEM_SIZE);
    my_memset(to_cmp, 0, sizeof(champ_t));

    ouais->next = to_cmp;
    to_cmp->next = NULL;
    ouais->is_alive = 1;

    last_to_live(ouais);
    check_alive_champ(&ouais, 0, map);
}

Test (check_endian_convertor, test_check_endian_convertor,
.init=cr_redirect_stdout)
{
    int test = 0x12345678;

    convert_endian(&test);
    cr_assert(test == 0x78563412);
    convert_endian(&test);
    cr_assert(test == 0x12345678);
}

Test (check_short_endian_convertor, test_check_short_endian_convertor,
.init=cr_redirect_stdout)
{
    short test = 0x1234;

    convert_endian_short(&test);
    cr_assert(test == 0x3412);
    convert_endian_short(&test);
    cr_assert(test == 0x1234);
}


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

Test (check_dump_no_arg, test_check_dump_no_arg, .exit_code = 84,
.init=cr_redirect_stderr)
{
    check_dump(NULL, NULL);
}

Test (check_dump_already_dump, test_check_dump_already_dump, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    check_dump(param, "test");
}

Test (check_bad_dump, test_check_bad_dump, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    param->dump_cycle = -1;
    check_dump(param, "test");
}

Test (check_inf_dump, test_check_inf_dump, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    param->dump_cycle = -1;
    check_dump(param, "13527828763632867867126736");
}

Test (check_nice_dump, test_check_nice_dump, .init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    param->dump_cycle = -1;
    check_dump(param, "50");
    cr_assert(param->dump_cycle == 50);
}

Test (check_no_arg_num, test_check_no_arg_num, .exit_code = 84,
.init=cr_redirect_stderr)
{
    check_num(NULL, NULL);
}

Test (check_num_specifie, test_check_num_specifie, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    param->num_impose[0] = 10;
    check_num(param, "50");
}

Test (check_bad_num_impose, test_check_bad_num_impose, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    check_num(param, "-50");
}

Test (check_bad_alpha_impose, test_check_bad_alpha_impose, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    check_num(param, "78163761978635967153967153");
}

Test (check_nice_num, test_check_nice_num, .init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    check_num(param, "3");
    cr_assert(param->num_impose[0] == 3);
}

Test (check_no_arg_adress, test_check_no_arg_adress, .exit_code = 84,
.init=cr_redirect_stderr)
{
    check_address(NULL, NULL);
}

Test (check_adress_specifie, test_check_adress_specifie, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    param->adress_next = 10;
    check_address(param, "50");
}

Test (check_bad_adress_impose, test_check_bad_adress_impose, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    param->adress_next = -1;
    check_address(param, "-50");
}

Test (check_alpha_adress_impose, test_check_alpha_adress_impo, .exit_code = 84,
.init=cr_redirect_stderr)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    param->adress_next = -1;
    check_address(param, "78163761978635967153967153");
}

Test (check_nice_adress, test_check_nice_adress, .init=cr_redirect_stdout)
{
    param_argv_t *param = malloc(sizeof(param_argv_t));

    my_memset(param, 0, sizeof(param_argv_t));
    param->adress_next = -1;
    check_address(param, "3");
    cr_assert(param->adress_next == 3);
}

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

Test (check_set_map_func, test_set_map_, .init=cr_redirect_stdout)
{
    champ_t *champ = malloc(sizeof(champ_t));
    char *map = NULL;

    my_memset(champ, 0, sizeof(champ_t));
    champ->instruction = malloc(sizeof(char) * 20);
    my_memset(champ->instruction, 0, sizeof(char) * 20);
    champ->param.champ_nbr = 2;
    champ->header.prog_size = 4;
    champ->next = NULL;
    champ->instruction[0] = 4;
    champ->instruction[1] = 0b01010100;
    champ->instruction[2] = 1;
    champ->instruction[3] = 3;
    champ->instruction[4] = 6;
    map = set_map(&champ, map);
    cr_assert(map[0] = 4);
    cr_assert(map[1] = 0b01010100);
    cr_assert(map[2] = 1);
    cr_assert(map[3] = 3);
    cr_assert(map[4] = 6);
}

Test (check_set_map_func_err, test_set_map_err, .init=cr_redirect_stderr,
.exit_code = 84)
{
    champ_t *champ = malloc(sizeof(champ_t));
    champ_t *champ2 = malloc(sizeof(champ_t));
    char *map = NULL;

    my_memset(champ, 0, sizeof(champ_t));
    my_memset(champ2, 0, sizeof(champ_t));
    champ->instruction = malloc(sizeof(char) * 20);
    champ2->instruction = malloc(sizeof(char) * 20);
    my_memset(champ->instruction, 0, sizeof(char) * 20);
    my_memset(champ2->instruction, 0, sizeof(char) * 20);
    champ->header.prog_size = 4;
    champ2->header.prog_size = 4;
    champ->param.champ_nbr = 2;
    champ2->param.champ_nbr = 1;
    champ->next = champ2;
    champ2->next = NULL;
    champ->instruction[0] = 4;
    champ->instruction[1] = 0b01010100;
    champ->instruction[2] = 1;
    champ->instruction[3] = 3;
    champ->instruction[4] = 6;
    champ2->instruction[0] = 4;
    champ2->instruction[1] = 0b01010100;
    champ2->instruction[2] = 1;
    champ2->instruction[3] = 3;
    champ2->instruction[4] = 6;
    champ2->param.adress = 0;
    champ2->param.adress_impose = 1;
    champ->param.adress = 0;
    champ->param.adress_impose = 1;
    map = set_map(&champ, map);
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


Test (increase_counter_func, test_increase_counter)
{
    int test = *get_cycle_to_die();

    for (int i = 0; i < 50; i++) {
        increase_counter();
    }
    cr_assert(test - 5 == *get_cycle_to_die());
}

Test (cpy_in_arena_func, test_cpy_in_arena)
{
    char *arena = malloc(sizeof(char) * (MEM_SIZE + 1));
    char *instruction = malloc(sizeof(char) * 20);

    my_memset(arena, 0, sizeof(char) * (MEM_SIZE));
    my_memset(instruction, 0, sizeof(char) * 20);
    instruction[0] = 4;
    instruction[1] = 0b01010100;
    instruction[2] = 1;
    instruction[3] = 3;
    instruction[4] = 6;
    cpy_in_arena(arena, instruction, -MEM_SIZE, 20);
    cr_assert(arena[0] == instruction[0]);
}

Test (memcpy_cor_func, test_memcpy_cor)
{
    char *arena = malloc(sizeof(char) * (MEM_SIZE + 1));
    char *instruction = malloc(sizeof(char) * 20);

    my_memset(arena, 0, sizeof(char) * (MEM_SIZE));
    my_memset(instruction, 0, sizeof(char) * 20);
    instruction[0] = 4;
    instruction[1] = 0b01010100;
    instruction[2] = 1;
    instruction[3] = 3;
    instruction[4] = 6;
    memcpy_cor(instruction, arena, -MEM_SIZE, 20);
    cr_assert(arena[0] == instruction[0]);
}

Test (cor_strcpy_func, test_cor_strcpy)
{
    char *arena = malloc(sizeof(char) * (MEM_SIZE + 1));
    char *instruction = malloc(sizeof(char) * 20);

    my_memset(arena, 0, sizeof(char) * (MEM_SIZE));
    my_memset(instruction, 0, sizeof(char) * 20);
    instruction[0] = 4;
    instruction[1] = 0b01010100;
    instruction[2] = 1;
    instruction[3] = 3;
    instruction[4] = 6;
    cor_strcpy(arena, instruction, (int [2]){MEM_SIZE, 0}, 20);
    cr_assert(arena[0] == instruction[0]);
}

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
