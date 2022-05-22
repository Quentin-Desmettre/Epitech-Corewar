/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#include "op.h"

int i_live(int arg[3], __attribute__((unused)) champ_t *champ,
__attribute__((unused)) char *arena)
{
    champ_t *save = *all_champs(NULL);

    while (save) {
        if (save->param.champ_nbr == arg[0]) {
            save->is_alive = 1;
            last_to_live(save);
        }
        save = save->next;
    }
    increase_counter();
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

int i_fork(int arg[3], champ_t *champ, __attribute__((unused))char *arena)
{
    champ_t *new = malloc(sizeof(champ_t));

    my_memcpy(new, champ, sizeof(champ_t));
    new->pc = champ->pc + arg[0] % IDX_MOD;
    new->cycle = 0;
    new->is_alive = 0;
    new->cycle_to_wait = -1;
    new->next = *fork_list();
    *fork_list() = new;

    return (0);
}

int i_lfork(int arg[3], champ_t *champ, __attribute__((unused))char *arena)
{
    champ_t *new = malloc(sizeof(champ_t));

    my_memcpy(new, champ, sizeof(champ_t));
    new->pc = champ->pc + arg[0];
    new->cycle = 0;
    new->is_alive = 0;
    new->cycle_to_wait = -1;
    new->next = *fork_list();
    *fork_list() = new;

    return (0);
}

int i_aff(int arg[3], champ_t *champ, __attribute__((unused))char *arena)
{
    my_putchar(champ->registers[arg[0]] % 256);
    return (0);
}
