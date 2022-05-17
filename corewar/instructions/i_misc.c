/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "op.h"

int i_live(int arg[3], champ_t *champ, __attribute__((unused))char *arena)
{
    static int nbr_lives_done = 0;
    int *cycle_to_die = 0;
    champ_t *save = champ;

    while (save) {
        if (save->param.champ_nbr == arg[0]) {
            save->is_alive = 1;
            print("Le joueur %d (%s) est en vie.\n",
            save->param.champ_nbr, save->header.prog_name);
        }
        save = save->next;
    }
    nbr_lives_done++;
    if (nbr_lives_done >= 40) {
        cycle_to_die = get_cycle_to_die();
        (*cycle_to_die)--;
        nbr_lives_done = 0;
    }
    return (0);
}

int i_zjmp(int arg[3], champ_t *champ, __attribute__((unused))char *arena)
{
    if (champ->carry) {
        champ->pc += arg[0] % IDX_MOD;
        champ->pc -= champ->args.byte_offset;
    }
    return (0);
}

int i_fork(int arg[3], champ_t *champ, char *arena)
{
    print("fork %d\n", arg[0]);
    return (0);
}

int i_lfork(int arg[3], champ_t *champ, char *arena)
{
    print("lfork %d\n", arg[0]);
    return (0);
}

int i_aff(int arg[3], champ_t *champ, char *arena)
{
    print("%c\n", champ->registers[arg[0]] % 256);
    return (0);
}
