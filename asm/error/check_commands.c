/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** check_commands.c
*/

#include "asm.h"

void replace_comment(char *line);
int getnbr_overflow(char *str);
char **get_labels(char ***base_words, FILE *f, int *line);

int is_in_bounds(int nb, int low, int up)
{
    return (nb > low && nb < up);
}

int check_command(char **args, char **err_mess)
{
    int nb_args = my_str_array_len(args) - 1;
    int type;
    int code = code_of(args[0]);

    code--;
    if (code < 0)
        return 0;
    if (nb_args != op_tab[code].nbr_args)
        return 0;
    for (int i = 1; i < nb_args + 1; i++) {
        type = type_of_arg(args[i], err_mess);
        if (type == T_ERROR || !(op_tab[code].type[i - 1] & type)) {
            *err_mess = (type == T_ERROR) ? *err_mess :
            "Incompatible argument type";
            return 0;
        }
    }
    return 1;
}

int is_label_valid(char const *arg)
{
    return arg[my_strlen(arg) - 1] == LABEL_CHAR &&
    count_occurences(LABEL_CHAR, arg) == 1 &&
    contain_only(arg, LABEL_CHARS ":") && my_strlen(arg) >= 2;
}

int check_label(char **args, char **err_mess, FILE *f, int *line)
{
    char **labels = get_labels(&args, f, line);

    if (!args)
        return 1;
    return check_command(args, err_mess);
}

int get_error_for(FILE *f, char const *file, int *nb_line)
{
    char *line;
    char **words;
    char *err_mess = "yolo";

    while ((line = get_next_line(f, nb_line))) {
        replace_comment(line);
        words = my_str_to_word_array(line, " \t,\n");
        if (!words[0]) {
            free_str_array(words);
            free(line);
            continue;
        }
        if (!check_label(words, &err_mess, f, nb_line))
            return !error(f, err_mess, file, *nb_line);
    }
    if (errno)
        return !error(f, "error while reading file", file, *nb_line);
    return 0;
}
