/*
** EPITECH PROJECT, 2022
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** my_crit
*/


#ifndef CRIT_H
    #define CRIT_H
    #include <stdlib.h>
    #include <unistd.h>

int has_to_fail(int change, int new);

static inline int my_read(int fd, void *buf, size_t size)
{
    static int nb_call = 0;

    if (nb_call == 1 && has_to_fail(0, 0))
        return -1;
    nb_call++;
    return read(fd, buf, size);
}
    #ifdef CRITERION
        #define read my_read
    #endif
#endif
