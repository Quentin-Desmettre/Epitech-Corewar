/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "op.h"

int *nbr_live_done(void)
{
    static int nbr_lives_done = 0;

    return (&nbr_lives_done);
}

int i_live(int arg[3], champ_t *champ, char *arena)
{
    int *tmp = 0;
    champ_t *save = champ;

    while (save) {
        if (save->param.champ_nbr == arg[0]) {
            save->is_alive += 1;
            print("Le joueur %d (%s) est en vie.\n",
            save->param.champ_nbr, save->header.prog_name);
        }
        save = save->next;
    }
    tmp = nbr_live_done();
    (*tmp)++;
    return (0);
}

int i_zjmp(int arg[3], champ_t *champ, char *arena)
{
    print("zjmp %d\n", arg[0]);
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
    print("aff %d\n", arg[0]);
    return (0);
}
