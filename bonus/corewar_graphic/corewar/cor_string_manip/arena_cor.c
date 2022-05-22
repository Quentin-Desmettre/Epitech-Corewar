/*
** EPITECH PROJECT, 2022
** ARENA_COR_C
** File description:
** arena_cor.c
*/

#include "corewar_include/op.h"

void dump_print(__attribute__((unused))char *map)
{
    return;
    // int pos_index = 0;

    // for (pos_index = 0; pos_index < 6144; pos_index += 32) {
    //     print("%-5X: ", pos_index);
    //     for (int i = pos_index; i < pos_index + 32; i++)
    //         print("%02hhX ", map[i]);
    //     print("\n");
    // }
}

char *set_map(champ_t **champ, char *map)
{
    champ_t *save;
    int num_of_champ = get_num_of_champ(champ);
    int pos;
    corewar_grap_t *graph = get_graph_struct();

    graph->color = malloc(sizeof(char *) * 2);
    graph->color[0] = malloc(sizeof(char) * (MEM_SIZE + 1));
    graph->color[1] = NULL;
    my_memset(graph->color[0], 0, MEM_SIZE + 1);
    map = malloc(sizeof(char) * (MEM_SIZE + 1));
    my_memset(map, 0, MEM_SIZE + 1);
    *champ = sort_my_list(*champ);
    save = *champ;
    for (int i = 0; save; i++) {
        pos = i * (MEM_SIZE / num_of_champ);
        save->pc = (save->param.adress == -1) ? pos : save->param.adress;
        graph->writing = save->param.champ_nbr;
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
