/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** main.c
*/

#include "corewar_include/op.h"

int help_message(char *name_binarie)
{
    write(1, "USAGE\n    ", 10);
    my_putstr(name_binarie);
    write(1, "[-dump nbr_cycle] [[-n prog_number] [-a load_address] prog_name] "
    "...\nDESCRIPTION\n    -dump nbr_cycle dumps the memory after the nbr_cycle"
    " execution (if the round isn’t already over) with the following format: 32"
    " bytes/line in hexadecimal (A0BCDEFE1DD3...)\n    -n prog_number sets the "
    "next program’s number. By default, the first free number in the parameter "
    "order\n    -a load_address sets the next program’s loading address. When "
    "no address is specified, optimize the addresses so that the processes are "
    "as far away from each other as possible. The addresses are MEM_SIZE "
    "modulo.\n", 586);
    return 0;
}

int find_little_but_higher(champ_t *champ, int int_compare)
{
    int little_int = 8;
    champ_t *save = champ;

    while (champ) {
        if (champ->champ_nbr > int_compare && champ->champ_nbr < little_int)
            little_int = champ->champ_nbr;
        champ = champ->next;
    }
    champ = save;
    return little_int;
}

champ_t *sort_my_list(champ_t *champ)
{
    int num_of_champ = get_num_of_champ(&champ);
    champ_t *sorted = NULL;
    int little = 0;

    for (int i = 0; i < num_of_champ; i++) {
        little = find_little_but_higher(champ, little);
        printf("%d\n", little);
    }
}

void set_map(champ_t *champ, char *map)
{
    map = malloc(sizeof(char) * MEM_SIZE);
    my_memset(map, 0, MEM_SIZE);
    sort_my_list(champ);
    champ = champ;
}

int main(int ac, char **av)
{
    int dump_cycle = 0;
    champ_t *info_champ = NULL;
    char *map = NULL;

    if (ac == 2)
        if (my_strcmp(av[1], "-h") == 0)
            return (help_message(av[0]));
    if (ac < 3) {
        write(2, "Need at least 2 champ\n", 22);
        return 84;
    }
    check_argv(&ac, av, &dump_cycle, &info_champ);
    check_champ(ac, &info_champ);
    set_map(info_champ, map);
    return (0);
}
