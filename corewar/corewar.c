/*
** EPITECH PROJECT, 2022
** COREWAR_C
** File description:
** corewar.c
*/

#include "corewar_include/op.h"

void check_alive_champ(champ_t **champ, int need_dump, char *map)
{
    champ_t *head = *champ;

    while (head && !head->is_alive) {
        (*champ) = head->next;
        head = *champ;
    }
    while (head) {
        if (head->next && !head->next->is_alive)
            head->next = head->next->next;
        head->is_alive = 0;
        head = head->next;
    }
    if (!(*champ) || get_alive_champs(*champ) == 1) {
        need_dump ? dump_print(map) : 0;
        head = last_to_live(NULL);
        if (last_to_live(NULL))
            print(MSG_WIN, head->param.champ_nbr, head->header.prog_name);
        exit(0);
    }
    all_champs(champ);
}

static void add_forks(void)
{
    champ_t **all = all_champs(NULL);
    champ_t *forks = *fork_list();
    champ_t *next;

    while (forks) {
        next = forks->next;
        forks->next = *all;
        *all = forks;
        forks = next;
    }
    *fork_list() = NULL;
}

static void exec_champions(char *map, champ_t *champions)
{
    champ_t *champ = champions;

    while (champ) {
        champ->cycle++;
        while (champ->pc < 0)
            champ->pc += MEM_SIZE;
        champ->pc %= MEM_SIZE;
        if (champ->cycle_to_wait == -1)
            instruction_reader(map, champ);
        if (champ->cycle == champ->cycle_to_wait)
            exec_instructions(champ, map);
        champ = champ->next;
    }
}

static void main_loop(char *map, champ_t *champions, int dump_cycle)
{
    int nbr_cycle = CYCLE_TO_DIE;
    int current_cycle = 0;
    int need_dump = dump_cycle;

    all_champs(&champions);
    while (dump_cycle != 0) {
        exec_champions(map, champions);
        nbr_cycle = *get_cycle_to_die();
        dump_cycle > 0 ? dump_cycle-- : dump_cycle;
        current_cycle++;
        if (current_cycle >= nbr_cycle) {
            check_alive_champ(&champions,
            (need_dump != -1 && dump_cycle == 0 ? 1 : 0), map);
            current_cycle = 0;
        }
        add_forks();
    }
    dump_print(map);
}

void setup_game(int ac, char **av)
{
    int dump_cycle = -1;
    champ_t *info_champ = NULL;
    char *map = NULL;

    check_argv(&ac, av, &dump_cycle, &info_champ);
    check_champ(&info_champ);
    map = set_map(&info_champ, map);
    setup_all_champ_for_game(&info_champ);
    main_loop(map, info_champ, dump_cycle);
}
