/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** test_str_arena.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "op.h"
#undef exit

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

Test (increase_counter_func, test_increase_counter)
{
    int test = *get_cycle_to_die();

    for (int i = 0; i < 50; i++) {
        increase_counter();
    }
    cr_assert(test - 5 == *get_cycle_to_die());
}
