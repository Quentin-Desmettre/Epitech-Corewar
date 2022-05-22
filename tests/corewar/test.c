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
#include "my_crit.h"

Test (functionnal_test, check_functionnal_test, .init=cr_redirect_stdout)
{
    char *res[8] = {"../tests/corewar/cor_binary/42.cor",
    "../tests/corewar/cor_binary/add.cor",
    "../tests/corewar/cor_binary/aff.cor",
    "../tests/corewar/cor_binary/and.cor",
    "../tests/corewar/cor_binary/bigzork.cor",
    "../tests/corewar/cor_binary/live.cor",
    "../tests/corewar/cor_binary/lld.cor",
    "../tests/corewar/cor_binary/loose.cor"};

    for (int i = 0; i < 8; i++) {
        char *av[3] = {"./corewar", res[0], res[i]};

        setup_game(3, av);
    }
}

Test (fnc, fnc, .init=cr_redirect_stdout)
{
    char *res[8] = {"../tests/corewar/cor_binary/42.cor",
    "../tests/corewar/cor_binary/add.cor",
    "../tests/corewar/cor_binary/aff.cor",
    "../tests/corewar/cor_binary/and.cor",
    "../tests/corewar/cor_binary/bigzork.cor",
    "../tests/corewar/cor_binary/live.cor",
    "../tests/corewar/cor_binary/lld.cor",
    "../tests/corewar/cor_binary/loose.cor"};
    char *av[5] = {"./corewar", res[0], res[1], "-dump", "500"};
    char *av2[5] = {"./corewar", res[0], res[1], "-dump", "0"};

    setup_game(5, av2);
    setup_game(5, av);
}

Test (forced_fail, forced_fail, .exit_code=84, .init=cr_redirect_stderr)
{
    has_to_fail(1, 1);
    char *res[8] = {"../tests/corewar/cor_binary/42.cor",
    "../tests/corewar/cor_binary/add.cor",
    "../tests/corewar/cor_binary/aff.cor",
    "../tests/corewar/cor_binary/and.cor",
    "../tests/corewar/cor_binary/bigzork.cor",
    "../tests/corewar/cor_binary/live.cor",
    "../tests/corewar/cor_binary/lld.cor",
    "../tests/corewar/cor_binary/loose.cor"};
    char *av[5] = {"./corewar", res[0], res[1], "-dump", "500"};
    setup_game(5, av);
}

Test (functionnal_test_double_prog_number, check_functionnal_test,
.init=cr_redirect_stderr, .exit_code = 84)
{
    for (int i = 0; i < 8; i++) {
        char *av[5] = {"./corewar", "-n", "2", "-n", "2"};
        setup_game(5, av);
    }
}

Test (functionnal_test_above_limit, check_functionnal_test,
.init=cr_redirect_stderr, .exit_code = 84)
{
    char *res[8] = {"../tests/corewar/cor_binary/42.cor",
    "../tests/corewar/cor_binary/add.cor",
    "../tests/corewar/cor_binary/aff.cor",
    "../tests/corewar/cor_binary/and.cor",
    "../tests/corewar/cor_binary/bigzork.cor",
    "../tests/corewar/cor_binary/live.cor",
    "../tests/corewar/cor_binary/lld.cor",
    "../tests/corewar/cor_binary/loose.cor"};
    for (int i = 0; i < 8; i++) {
        char *av[6] = {"./corewar", res[0], res[1], res[2], res[3], res[4]};
        setup_game(6, av);
    }
}

Test (functionnal_test_bad_option, check_functionnal_test,
.init=cr_redirect_stderr, .exit_code = 84)
{
    char *res[8] = {"../tests/corewar/cor_binary/42.cor",
    "../tests/corewar/cor_binary/add.cor",
    "../tests/corewar/cor_binary/aff.cor",
    "../tests/corewar/cor_binary/and.cor",
    "../tests/corewar/cor_binary/bigzork.cor",
    "../tests/corewar/cor_binary/live.cor",
    "../tests/corewar/cor_binary/lld.cor",
    "../tests/corewar/cor_binary/loose.cor"};

    for (int i = 0; i < 8; i++) {
        char *av[4] = {"./corewar", res[1], "-n", 0};
        setup_game(3, av);
    }
}

Test (functionnal_test_bad_option_address, check_functionnal_test,
.init=cr_redirect_stderr, .exit_code = 84)
{
    char *res[8] = {"../tests/corewar/cor_binary/42.cor",
    "../tests/corewar/cor_binary/add.cor",
    "../tests/corewar/cor_binary/aff.cor",
    "../tests/corewar/cor_binary/and.cor",
    "../tests/corewar/cor_binary/bigzork.cor",
    "../tests/corewar/cor_binary/live.cor",
    "../tests/corewar/cor_binary/lld.cor",
    "../tests/corewar/cor_binary/loose.cor"};

    for (int i = 0; i < 8; i++) {
        char *av[6] = {"./corewar", res[1], "-a", "5", "-a", "5"};
        setup_game(6, av);
    }
}

Test (functionnal_test_bad_prog_number, check_functionnal_test,
.init=cr_redirect_stderr, .exit_code = 84)
{
    char *res[8] = {"../tests/corewar/cor_binary/42.cor",
    "../tests/corewar/cor_binary/add.cor",
    "../tests/corewar/cor_binary/aff.cor",
    "../tests/corewar/cor_binary/and.cor",
    "../tests/corewar/cor_binary/bigzork.cor",
    "../tests/corewar/cor_binary/live.cor",
    "../tests/corewar/cor_binary/lld.cor",
    "../tests/corewar/cor_binary/loose.cor"};

    for (int i = 0; i < 8; i++) {
        char *av[7] = {"./corewar", "-n", "2", res[1], "-n", "2", res[0]};
        setup_game(7, av);
    }
}

Test (functionnal_test_bad_work, check_functionnal_test,
.init=cr_redirect_stderr, .exit_code = 84)
{
    char *res[8] = {"../tests/corewar/cor_binary/42.cor",
    "../tests/corewar/cor_binary/add.cor",
    "../tests/corewar/cor_binary/aff.cor",
    "../tests/corewar/cor_binary/and.cor",
    "../tests/corewar/cor_binary/bigzork.cor",
    "../tests/corewar/cor_binary/live.cor",
    "../tests/corewar/cor_binary/lld.cor",
    "../tests/corewar/cor_binary/loose.cor"};

    for (int i = 0; i < 8; i++) {
        char *av[9] = {"./corewar", "-n", "2", res[1], "-n", "0",
        res[0], "-n", "4"};
        setup_game(9, av);
    }
}
