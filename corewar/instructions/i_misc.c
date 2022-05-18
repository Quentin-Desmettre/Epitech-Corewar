/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "op.h"

champ_t **all_champs(champ_t **new)
{
    static champ_t **c = NULL;

    if (new)
        c = new;
    return c;
}

int i_live(int arg[3], champ_t *champ, __attribute__((unused))char *arena)
{
    static int nbr_lives_done = 0;
    int *cycle_to_die = 0;
    champ_t *save = *all_champs(NULL);

    while (save) {
        if (save->param.champ_nbr == arg[0]) {
            save->is_alive = 1;
            print("Le joueur %d (%s) est en vie.\n",
            save->param.champ_nbr, save->header.prog_name);
            last_to_live(save);
        }
        save = save->next;
    }
    nbr_lives_done++;
    while (nbr_lives_done >= NBR_LIVE) {
        cycle_to_die = get_cycle_to_die();
        *cycle_to_die -= CYCLE_DELTA;
        nbr_lives_done -= NBR_LIVE;
    }
    return (0);
}

int i_zjmp(int arg[3], champ_t *champ, __attribute__((unused))char *arena)
{
    if (champ->carry) {
        champ->pc += arg[0] % IDX_MOD;
        champ->pc -= champ->args.byte_offset;
        champ->pc %= MEM_SIZE;
    }
    return (0);
}

int i_fork(int arg[3], champ_t *champ, char *arena)
{
    print("Je fork a l'index %d\n", champ->pc + arg[0] % IDX_MOD);
    return (0);
}

int i_lfork(int arg[3], champ_t *champ, char *arena)
{
    print("Je lfork a l'index %d\n", (champ->pc + arg[0]));
    return (0);
}

int i_aff(int arg[3], champ_t *champ, __attribute__((unused))char *arena)
{
    my_putchar(champ->registers[arg[0]] % 256);
    return (0);
}
