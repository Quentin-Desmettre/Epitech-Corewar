/*
** EPITECH PROJECT, 2021
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** check_commands.c
*/

#include "asm.h"

void replace_comment(char *line);
int getnbr_overflow(char *str);

int is_in_bounds(int nb, int low, int up)
{
    return (nb > low && nb < up);
}

int check_command(char **args)
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
        type = type_of_arg(args[i]);
        if (type == T_ERROR || !(op_tab[code].type[i - 1] & type))
            return 0;
    }
    return 1;
}

int is_label_valid(char const *arg)
{
    return arg[my_strlen(arg) - 1] == LABEL_CHAR &&
    count_occurences(LABEL_CHAR, arg) == 1 &&
    contain_only(arg, LABEL_CHARS ":") && my_strlen(arg) >= 2;
}

int check_label(char **args)
{
    if (!args[1])
        return 0;
    return check_command(args + 1);
}

int get_error_for(FILE *f, char const *file)
{
    char *line;
    char **words;
    int is_lab;

    while ((line = get_next_line(f))) {
        replace_comment(line);
        words = my_str_to_word_array(line, " \t,\n");
        if (!words[0]) {
            free_str_array(words);
            free(line);
            continue;
        }
        is_lab = is_label_valid(words[0]);
        if ((is_lab && !check_label(words)) ||
        (!is_lab && !check_command(words)))
            return !error(f, file);
    }
    if (errno)
        return !error(f, file);
    return 0;
}
