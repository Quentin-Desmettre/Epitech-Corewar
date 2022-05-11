/*
** EPITECH PROJECT, 2022
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** asm
*/

#ifndef ASM_H_
    #define ASM_H_
    #include <unistd.h>
    #include <stdio.h>
    #include <errno.h>
    #include <stdint.h>
    #include "libmy.h"
    #include "op.h"

typedef struct {
    char code;
    uint8_t coding_byte;
    uint8_t params[MAX_ARGS_NUMBER * DIR_SIZE];
    int32_t offset;
    int cmd_size;
    char *labels[3];
    char label_pos[3];
    char label_sizes[3];
    int nb_label;
    int is_special;
} command_t;

typedef struct {
    command_t *cmd;
    char *name;
} label_t;

typedef struct {
    header_t header;
    list_t *commands;
    list_t *labels;
    FILE *f;
} file_buffer_t;

/**
 * @brief Check if the given file has error
 * @param file The file to check
 * @return 1 if the file is invalid, 0 if it is valid
 */
int has_error(char const *file);

/**
 * @brief Compile and write the file to the correct output file
 * @param f The openned FILE stream representing the input file
 * @param file The output file
 * @return 1 on success, 0 on failure
 */
int write_file(FILE *f, char const *file);

/**
 * @brief Get the appropriate output file name for a given input file
 * @param file The input file
 * @return The newly allocated string, containing the appropriate
 * output file name
 */
char const *get_output_file(char const *file);

/**
 * @brief Get the next line of the file stream f
 * @param f The file stream
 * @return A newly allocated string, containing the next line, Or NULL if
 * getline failed. In case of an error, errno is set to indicate the cause.
 * You should always free the given string.
 */
char *get_next_line(FILE *f, int *line);

/**
 * @brief Get the offset of the progsize, inside the header_t structure
 * @return size_t representing the offset in the header_t structure
 */
size_t progsize_offset(void);

/**
 * @brief Get the instruction code of the given command
 * @param name The command you want to check
 * @return The instruction code of the command, or -1 if not found
 */
char code_of(char const *name);

/**
 * @brief Get the type of given argument.
 * @param arg The argument you want to get the type of
 * @return T_REG if the argument is a register, T_DIR if the argument is direct,
 * T_IND if it is indirect, and T_ERROR if it is none of that.
 */
char type_of_arg(char const *arg, char **err_mess);

/**
 * @brief Get the coding byte for the given arguments.
 * @param words the arguments; words[0] must be the name of the command.
 * @return uint8_t representing the coding byte.
 */
uint8_t coding_byte_for(char **words);

/**
 * @brief Resolve all logged labels
 * @param buf The buffer containing all commands and labels
 * @return 0 if it failed, 1 if it succeeded
 */
int resolve_labels(file_buffer_t *buf);

command_t *create_command(char **words, command_t *prev);
int get_error_for(FILE *f, char const *file, int *line);
int check_label(char **args, char **err_mess, FILE *f, int *line);
int check_command(char **args, char **err_mess);
int error(FILE *f, char const *mess, char const *file, int line);
char *get_name(char const *line, int max);
int check_comment(FILE *f, char const *file, int *line);
int check_name(FILE *f, char const *file, int *line);
void convert_endian(int *nbr);
void convert_endian_short(short *nbr);
int write_buffer(file_buffer_t *buf, char const *output);
int is_in_bounds(int nb, int low, int up);
size_t progsize_offset(void);
char code_of(char const *name);
uint8_t coding_byte_for(char **words);
int has_index(char *name, int nb_arg);
int compile_file(char const *file);

static inline void add_int16t(command_t *c, int16_t i)
{
    my_memcpy(c->params + c->cmd_size, &i, 2);
    c->cmd_size += 2;
}

static inline void add_int32t(command_t *c, int32_t i)
{
    my_memcpy(c->params + c->cmd_size, &i, 4);
    c->cmd_size += 4;
}

static inline int is_special_case(int x)
{
    return (x == 1) || (x == 9) || (x == 12) || (x == 15);
}

#endif /* !ASM_H_ */
