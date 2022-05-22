/*
** EPITECH PROJECT, 2022
** READ_CHECK_HEADER_C
** File description:
** read_check_header.c
*/

#include "corewar_include/op.h"

long long int my_stat(char *file, int nbline_or_nbchar)
{
    FILE *fd = fopen(file, "r");
    size_t bufsize = 0;
    char *buf = NULL;
    int len = 0;
    long long int nb_char = 0;
    long long int return_getline = 1;

    if (!fd)
        return (-1);
    while (return_getline > 0) {
        return_getline = getline(&buf, &bufsize, fd);
        free(buf);
        buf = NULL;
        nb_char += return_getline;
        len++;
    }
    fclose(fd);
    return (nbline_or_nbchar == 0 ? len - 1 : nb_char + 1);
}

static void check_header(champ_t **info_champ, size_t size)
{
    convert_endian(&(*info_champ)->header.magic);
    convert_endian(&(*info_champ)->header.prog_size);
    if ((*info_champ)->header.magic != COREWAR_EXEC_MAGIC) {
        dprint(2, "Wrong executable magic number.\n");
        exit(84);
    }
    if ((*info_champ)->header.prog_size + sizeof(header_t) != size) {
        dprint(2,
        "%s : Wrong program size in the header\n", (*info_champ)->name_champ);
        exit(84);
    }
}

static void read_header(champ_t **info_champ, size_t size)
{
    int fd = open((*info_champ)->name_champ, O_RDONLY);
    size_t size_header = sizeof(header_t);

    if (fd < 0) {
        dprint(2, "Error in function open: No such file or directory.\n");
        exit(84);
    }
    if (read(fd, &(*info_champ)->header, size_header) != (ssize_t)size_header) {
        dprint(2, "Corrupted header\n");
        exit(84);
    }
    (*info_champ)->instruction = malloc(sizeof(char) * (size - size_header));
    if (read(fd, (*info_champ)->instruction, (size - size_header)) !=
    (long int)(size - size_header)) {
        dprint(2, "Error on read\n");
        exit(84);
    }
    close(fd);
}

void fill_header_champ(champ_t **info_champ)
{
    champ_t *save = *info_champ;
    size_t size = 0;

    while (*info_champ) {
        size = my_stat((*info_champ)->name_champ, 1);
        read_header(info_champ, size);
        check_header(info_champ, size);
        (*info_champ) = (*info_champ)->next;
    }
    (*info_champ) = save;
}
