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
        save->param.adress = (save->param.adress == -1) ? pos : save->param.adress;
        map = cor_strcpy(map, save->instruction,
        (int [2]){save->param.adress != -1 ? save->param.adress : pos, 1},
        save->header.prog_size);
        if (!map) {
            write(2, "Overlap.\n", 9);
            exit(84);
        }
        save = save->next;
    }
    return (map);
}

void check_alive_champ(champ_t **champ)
{
    champ_t *head = *champ;

    if (!head->is_alive)
        (*champ) = head->next;
    while (head) {
        if (!head->next->is_alive && head->next)
            head->next = head->next->next;
        else
            head->next = NULL;
        head = head->next;
    }
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

    while (dump_cycle != 0) {
        while (head) {
            get_instruction(map, head);
            head = head->next;
        }
        dump_cycle > 0 ? dump_cycle-- : dump_cycle;
        current_cycle++;
        if (current_cycle == nbr_cycle) {
            check_alive_champ(&champions);
            current_cycle = 0;
        }
        head = champions;
    }
    if (need_dump != -1)
        dump_print(map);
}

void print_winner(champ_t *info_champ)
{
    my_putstr("A gagné\n");
}

void setup_game(int ac, char **av)
{
    int dump_cycle = -1;
    champ_t *info_champ = NULL;
    char *map = NULL;

    check_argv(&ac, av, &dump_cycle, &info_champ);
    check_champ(ac, &info_champ);
    map = set_map(info_champ, map);
    main_loop(map, info_champ, dump_cycle);
//    print_winner(info_champ);
}
