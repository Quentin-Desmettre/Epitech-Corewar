/*
** EPITECH PROJECT, 2022
** COREWAR_C
** File description:
** corewar.c
*/

#include "corewar_include/op.h"
#define strndup noa_strndup

char *noa_strndup(char *src, size_t size)
{
    char *ans = malloc(sizeof(char) * size);

    memcpy(ans, src, size);
    return (ans);
}

corewar_grap_t *get_graph_struct(void)
{
    static corewar_grap_t *graph = NULL;

    if (!graph) {
        graph = malloc(sizeof(corewar_grap_t));
        memset(graph, 0, sizeof(corewar_grap_t));
    }
    return (graph);
}

char *check_alive_champ(champ_t **champ, int need_dump, char *map)
{
    champ_t *head = *champ;
    static char *result_string = "Le joueur ";

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
        if (last_to_live(NULL)) {
            append(&result_string, nbr_to_str(head->param.champ_nbr), 0);
            append(&result_string, " (", 1);
            append(&result_string, head->header.prog_name, 1);
            append(&result_string, ") a gagne.", 1);
            return (result_string);
        }
        return my_strdup("Egalite");
    }
    all_champs(champ);
    return NULL;
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

static void add_champ_pc(champ_t *champions, char *str)
{
    champ_t *save = champions;

    while (save) {
        str[save->pc] = 10;
        str[save->pc] += save->param.champ_nbr;
        save = save->next;
    }
}

void set_is_dead(int *to_change)
{
    for (int i = 0; i < 4; i++)
        to_change[i] = 1;
    for (champ_t *champs = *all_champs(NULL); champs; champs = champs->next) {
        to_change[champs->param.champ_nbr - 1] = 0;
    }
}

static char **main_loop(char *map, champ_t *champions, int dump_cycle)
{
    int nbr_cycle = CYCLE_TO_DIE;
    int current_cycle = 0;
    int need_dump = dump_cycle;
    char *tmp = NULL;
    corewar_grap_t *graph = get_graph_struct();
    graph->nbr_cycle_max = 0;
    graph->bytes = malloc(sizeof(char *) * ((graph->nbr_cycle_max) + 2));
    graph->is_dead = malloc(sizeof(int*));
    graph->is_dead[0] = malloc(sizeof(int) * 4);
    memset(graph->is_dead[0], 0, sizeof(int) * 4);
    graph->cycle_to_die = malloc(sizeof(int));
    graph->cycle_to_die[0] = CYCLE_TO_DIE;

    graph->bytes[graph->nbr_cycle_max] = strndup(map, MEM_SIZE);
    graph->bytes[graph->nbr_cycle_max + 1] = NULL;
    graph->nbr_cycle_max++;
    all_champs(&champions);
    while (dump_cycle != 0) {
        graph->color = realloc(graph->color, sizeof(char *) * (graph->nbr_cycle_max + 3));
        graph->color[graph->nbr_cycle_max] = strndup(graph->color[graph->nbr_cycle_max - 1], MEM_SIZE);
        add_champ_pc(champions, graph->color[graph->nbr_cycle_max - 1]);
        graph->color[graph->nbr_cycle_max + 1] = NULL;
        exec_champions(map, champions);
        nbr_cycle = *get_cycle_to_die();
        dump_cycle > 0 ? dump_cycle-- : dump_cycle;
        current_cycle++;
        if (current_cycle >= nbr_cycle) {
            tmp = check_alive_champ(&champions,
            (need_dump != -1 && dump_cycle == 0 ? 1 : 0), map);
            if (tmp) {
                current_cycle = 0;
                graph->bytes = realloc(graph->bytes, sizeof(char *) * (graph->nbr_cycle_max + 2));
                graph->bytes[graph->nbr_cycle_max] = strndup(map, MEM_SIZE);
                graph->bytes[graph->nbr_cycle_max + 1] = NULL;
                graph->is_dead[graph->nbr_cycle_max] = malloc(sizeof(int) * 4);
                set_is_dead(graph->is_dead[graph->nbr_cycle_max]);
                graph->cycle_to_die[graph->nbr_cycle_max] = nbr_cycle;
                if (last_to_live(NULL))
                    graph->is_dead[graph->nbr_cycle_max][last_to_live(NULL)->param.champ_nbr - 1] = 0;
                graph->winner_str = tmp;
                return (graph->bytes);
            }
        }
        add_forks();
        graph->bytes = realloc(graph->bytes, sizeof(char *) * (graph->nbr_cycle_max + 2));
        graph->bytes[graph->nbr_cycle_max] = strndup(map, MEM_SIZE);
        graph->bytes[graph->nbr_cycle_max + 1] = NULL;
        graph->is_dead = realloc(graph->is_dead, sizeof(int *) * (graph->nbr_cycle_max + 2));
        graph->is_dead[graph->nbr_cycle_max] = malloc(sizeof(int) * 4);
        set_is_dead(graph->is_dead[graph->nbr_cycle_max]);
        graph->cycle_to_die = realloc(graph->cycle_to_die, sizeof(int) * (graph->nbr_cycle_max + 2));
        graph->cycle_to_die[graph->nbr_cycle_max] = nbr_cycle;
        graph->nbr_cycle_max++;
    }
    need_dump != -1 ? dump_print(map) : 0;
    return (graph->bytes);
}

corewar_grap_t *setup_game(int ac, char **av)
{
    int dump_cycle = -1;
    champ_t *info_champ = NULL;
    char *map = NULL;

    check_argv(&ac, av, &dump_cycle, &info_champ);
    check_champ(&info_champ);
    map = set_map(&info_champ, map);
    setup_all_champ_for_game(&info_champ);
    main_loop(map, info_champ, dump_cycle);
    return (get_graph_struct());
}
