/*
** EPITECH PROJECT, 2022
** COREWAR_C
** File description:
** corewar.c
*/

#include "corewar_include/op.h"

int *get_cycle_to_die(void)
{
    static int cycle_to_die = CYCLE_TO_DIE;

    return (&cycle_to_die);
}

void dump_print(char *map)
{
    int pos_index = 0;

    for (pos_index = 0; pos_index < 6144; pos_index += 32) {
        print("%-5X: ", pos_index);
        for (int i = pos_index; i < pos_index + 32; i++)
            print("%02hhX ", map[i]);
        print("\n");
    }
}

char *set_map(champ_t **champ, char *map)
{
    champ_t *save;
    int num_of_champ = get_num_of_champ(champ);
    int pos;

    map = malloc(sizeof(char) * (MEM_SIZE + 1));
    my_memset(map, 0, MEM_SIZE + 1);
    *champ = sort_my_list(*champ);
    save = *champ;
    for (int i = 0; save; i++) {
        pos = i * (MEM_SIZE / num_of_champ);
        save->pc = (save->param.adress == -1) ? pos : save->param.adress;
        map = cor_strcpy(map, save->instruction, (int [2]){save->pc, 1},
        save->header.prog_size);
        if (!map) {
            write(2, "Overlap.\n", 9);
            exit(84);
        }
        save = save->next;
    }
    return (map);
}

void main_loop(char *map, champ_t *champions, int dump_cycle)
{
    int nbr_cycle = CYCLE_TO_DIE;
    int need_dump = dump_cycle;

    while (dump_cycle != 0) {
        dump_cycle > 0 ? dump_cycle-- : dump_cycle;
    }
    if (need_dump != -1)
        dump_print(map);
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
//    instruction_reader(info_champ);
    main_loop(map, info_champ, dump_cycle);
//    print_winner(info_champ);
}
