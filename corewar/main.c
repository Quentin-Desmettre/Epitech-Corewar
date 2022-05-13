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

void set_map(champ_t *champ, char *map)
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
    dump_print(map);
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
