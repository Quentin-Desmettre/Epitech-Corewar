/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** main.c
*/

#include "unistd.h"
#include "corewar_include/op.h"
#include "libmy.h"

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

void print_info_champ(champ_t *info_champ)
{
    while (info_champ) {
        my_putstr("Champ name : ");
        my_putstr(info_champ->name_champ);
        my_putstr("\nChamp nbr : ");
        my_put_nbr(info_champ->champ_nbr);
        my_putstr("\nChamp adress : ");
        my_put_nbr(info_champ->adress);
        my_putchar('\n');
        info_champ = info_champ->next;
    }
}

int main(int ac, char **av)
{
    int dump_cycle = 0;
    champ_t *info_champ = NULL;

    if (ac == 2)
        if (my_strcmp(av[1], "-h") == 0)
            return (help_message(av[0]));
    if (ac < 3) {
        write(2, "Need at least 2 champ\n", 22);
        return 84;
    }
    check_argv(&ac, av, &dump_cycle, &info_champ);
    check_champ(ac, &info_champ);
    print_info_champ(info_champ);
    return (0);
}
