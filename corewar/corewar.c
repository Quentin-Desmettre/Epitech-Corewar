/*
** EPITECH PROJECT, 2022
** COREWAR_C
** File description:
** corewar.c
*/

#include "corewar_include/op.h"

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

char *set_map(champ_t *champ, char *map)
{
    champ_t *save;
    int num_of_champ = 0;
    int pos = 0;

    map = malloc(sizeof(char) * (MEM_SIZE + 1));
    my_memset(map, 0, MEM_SIZE + 1);
    champ = sort_my_list(champ);
    save = champ;
    num_of_champ = get_num_of_champ(&champ);
    for (int i = 0; save; i++) {
        pos = i * (MEM_SIZE / num_of_champ);
        save->adress = (save->adress == -1) ? pos : save->adress;
        map = cor_strcpy(map, save->instruction,
        (int [2]){save->adress != -1 ? save->adress : pos, 1},
        save->header.prog_size);
        if (!map)
            exit(84);
        save = save->next;
    }
    return (map);
}

void main_loop(char *map, champ_t *champions)
{
    int nbr_cycle = CYCLE_TO_DIE;

    while (nbr_cycle >= 0) {
        for (int tmp = nbr_cycle; tmp >= 0; tmp--) {
            my_putstr("coucou\n");
        }
        nbr_cycle -= CYCLE_DELTA;
    }
}

void print_winner(champ_t *info_champ)
{
    my_putstr("A gagné\n");
}

void setup_game(int ac, char **av)
{
    int dump_cycle = 0;
    champ_t *info_champ = NULL;
    char *map = NULL;

    check_argv(&ac, av, &dump_cycle, &info_champ);
    check_champ(ac, &info_champ);
    map = set_map(info_champ, map);
    instruction_reader(info_champ);
//    main_loop(map, info_champ);
//    if (dump_cycle)
//        dump_print(map);
//    print_winner(info_champ);
}