/*
** EPITECH PROJECT, 2022
** COREWAR_C
** File description:
** corewar.c
*/

#include "corewar_include/op.h"

champ_t *last_to_live(champ_t *new)
{
    static champ_t *live = NULL;

    if (new)
        live = new;
    return live;
}

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
    if (!(*champ) || get_num_of_champ(champ) == 1) {
        need_dump ? dump_print(map) : 0;
        print("Le joueur %d (%s) a gagné.\n",
        last_to_live(NULL)->param.champ_nbr,
        last_to_live(NULL)->header.prog_name);
        exit(0);
    }
    all_champs(champ);
}

void get_instruction(char *map, champ_t *champ)
{
    champ->cycle++;
    if (champ->cycle_to_wait == -1)
        instruction_reader(map, champ);
    if (champ->cycle == champ->cycle_to_wait)
        exec_instructions(champ, map);
}

void main_loop(char *map, champ_t *champions, int dump_cycle)
{
    int nbr_cycle = CYCLE_TO_DIE;
    int current_cycle = 0;
    int need_dump = dump_cycle;
    champ_t *head = champions;

    all_champs(&champions);
    while (dump_cycle != 0) {
        while (head) {
            get_instruction(map, head);
            head = head->next;
        }
        nbr_cycle = *get_cycle_to_die();
        dump_cycle > 0 ? dump_cycle-- : dump_cycle;
        current_cycle++;
        if (current_cycle >= nbr_cycle) {
            check_alive_champ(&champions,
            (need_dump != -1 && dump_cycle == 0 ? 1 : 0), map);
            current_cycle = 0;
        }
        head = champions;
    }
    need_dump != -1 ? dump_print(map) : 0;
}

void setup_game(int ac, char **av)
{
    int dump_cycle = -1;
    champ_t *info_champ = NULL;
    char *map = NULL;

    check_argv(&ac, av, &dump_cycle, &info_champ);
    check_champ(ac, &info_champ);
    map = set_map(&info_champ, map);
    setup_all_champ_for_game(&info_champ);
    main_loop(map, info_champ, dump_cycle);
}
