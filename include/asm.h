/*
** EPITECH PROJECT, 2022
** B-CPE-201-LIL-2-1-corewar-noa.trachez
** File description:
** asm
*/

/// @file asm.h
/// @brief Main header for the ASM compiler.

#ifndef ASM_H_
    #define ASM_H_
    #include <unistd.h>
    #include <stdio.h>
    #include <errno.h>
    #include <stdint.h>
    #include "libmy.h"
    #include "op.h"

    #pragma pack(push, 1)

/// @struct command_data_t
/// @brief Structure for unit tests purposes.
typedef struct command_data {
    char code;
    char coding_byte;
    uint8_t params[4];
} command_data_t;

/// @struct command_data2_t
/// @brief Structure for unit tests purposes.
typedef struct command_data2 {
    char code;
    uint8_t params[4];
} command_data2_t;

    #pragma pack(pop)

/// @struct command_t
/// @brief Structure to represent a command.
typedef struct {
    char code; /**< The command code. */
    uint8_t coding_byte; /**< The coding byte. */
    uint8_t params[MAX_ARGS_NUMBER * DIR_SIZE]; /**< The parameters. */
    int32_t offset; /**< The command offset in the file. */
    int cmd_size; /**< The command size. */
    char *labels[3]; /**< The labels. */
    char label_pos[3]; /**< The label positions. */
    char label_sizes[3]; /**< The label sizes. */
    int nb_label; /**< The number of labels. */
    int is_special; /**< Is the command a special case? */
} command_t;

/// @struct label_t
/// @brief A structure representing a label.
typedef struct {
    command_t *cmd; /**< The command it's linked to. */
    char *name; /**< The name of the label. */
} label_t;

/// @struct file_buffer_t
/// @brief A structure representing the file contents.
typedef struct {
    header_t header; /**< The header of the file. */
    list_t *commands; /**< The list of commands. */
    list_t *labels; /**< The list of labels. */
    FILE *f; /**< The file to read from. */
} file_buffer_t;

/// @brief Check if the given file has error
/// @param file The file to check
/// @return 1 if the file is invalid, 0 if it is valid
int has_error(char const *file);

/// @brief Compile and write the file to the correct output file
/// @param f The openned FILE stream representing the input file
/// @param file The output file
/// @return 1 on success, 0 on failure
int write_file(FILE *f, char const *file);

/// @brief Get the appropriate output file name for a given input file
/// @param file The input file
/// @return The newly allocated string, containing the appropriate
/// output file name
char const *get_output_file(char const *file);

/// @brief Get the next line of the file stream f
/// @param f The file stream
/// @param line A pointer to the integer to increment, or
/// NULL if you don't want to count the number of lines
/// @return A newly allocated string, containing the next line, Or NULL if
/// getline failed. In case of an error, errno is set to indicate the cause.
/// You should always free the given string.
char *get_next_line(FILE *f, int *line);

/// @brief Get the instruction code of the given command
/// @param name The command you want to check
/// @return The instruction code of the command, or -1 if not found
char code_of(char const *name);

/// @brief Get the type of given argument.
/// @param arg The argument you want to get the type of
/// @return T_REG if the argument is a register, T_DIR if the argument is direct
/// ,T_IND if it is indirect, and T_ERROR if it is none of that.
char type_of_arg(char const *arg, char **err_mess);

/// @brief Get the coding byte for the given arguments.
/// @param words the arguments; words[0] must be the name of the command.
/// @return uint8_t representing the coding byte.
uint8_t coding_byte_for(char **words);

/// @brief Resolve all logged labels
/// @param buf The buffer containing all commands and labels
/// @return 0 if it failed, 1 if it succeeded
int resolve_labels(file_buffer_t *buf);

/// @brief Display an error message and close the openned FILE*.
/// @param f The base FILE*
/// @param mess The custom error message
/// @param file The file name where the error occured
/// @param line The line on which an error occured
/// @return 0 in any case.
int error(FILE *f, char const *mess, char const *file, int line);

/// @brief Convert the endianness of a 4-byte integer.
/// @param nbr A pointer to the integer you want to convert
void convert_endian(int *nbr);

/// @brief Convert the endiannes of a 2-byte integer.
/// @param nbr A pointer to the integer you want to convert
void convert_endian_short(short *nbr);

/// @brief Write the file buffer to the output file
/// @param buf The file buffer, containing the commands to write
/// @param output The output file
/// @return 0 if it failed, 1 if it succeeded.
int write_buffer(file_buffer_t *buf, char const *output);

/// @brief Check if the given number follows the rule low < nb < up.
/// @param nb The number to check
/// @param low The lower bound (excluded)
/// @param up The upper bound (excluded)
/// @return 0 if the number is not in the bounds, else 1.
int is_in_bounds(int nb, int low, int up);

/// @brief Check if the given command must take an index as parameter
/// @param name The name of the command
/// @param nb_arg The index of the argument we have to check
/// @return 1 if it must have and index, else 0.
int has_index(char *name, int nb_arg);

/// @brief Compile a .s file.
/// @param file The file to compile
/// @return 0 if it failed, else 1.
int compile_file(char const *file);

/// @brief Shortens the line, to omit comments.
/// @param line The line to shorten.
void replace_comment(char *line);

/// @brief Convert a string to an integer, without performing any error
/// handling or overflow check.
/// @param str The string to convert
/// @return The value of the string
int getnbr_overflow(char *str);

/// @brief Get all the labels contained in base_words, with the next labels.
/// @param base_words The current command's arguments.
/// @param f The FILE* we are currently reading.
/// @param line A pointer to an integer,
/// representing the line we're currently on.
/// @return char** A string array containg all the labels.
/// If the labels are not linked to any command, (*base_words) is set to NULL.
/// Else, (*base_words) is set to be the command's arguments.
char **get_labels(char ***base_words, FILE *f, int *line);

/// @brief Check if the given argument represents a label definition.
/// @param arg The argument we have to check
/// @return 1 if the argument is a valid label, else 0.
int is_label_valid(char const *arg);

/// @brief Create a command object, built with the given arguments.
/// @param words The command's arguments
/// @param prev The previous command
/// @return command_t* representing the built command.
command_t *create_command(char **words, command_t *prev);

/// @brief Check if the given file has any error.
/// This function is executed after the name and comment check.
/// @param f The FILE* we have to read.
/// @param file The file name.
/// @param line A pointer to an integer,
/// representing the line we're currently on.
/// @return 1 if there is an error, else 0.
int get_error_for(FILE *f, char const *file, int *line);

/// @brief Check if the given arguments,
/// representing a label, contains any error.
/// @param args The command's arguments.
/// @param err_mess A pointer to a string, representing the error message.
/// @param f The FILE* we have to read.
/// @param line A pointer to an integer,
/// representing the line we're currently on.
/// @return 1 if there is no error, else 0.
int check_label(char **args, char **err_mess, FILE *f, int *line);

/// @brief Check if the given arguments,
/// representing a command, contains any error.
/// @param args The command's arguments.
/// @param err_mess A pointer to a string, representing the error message.
/// @return 1 if there is no error, else 0.
int check_command(char **args, char **err_mess);

/// @brief Get the header value for 'name'.
/// @param line The current line, containing the header value for 'name'.
/// @param max The maximum length for 'name'.
/// @return NULL if there is an error, else the header value for 'name'.
char *get_name(char const *line, int max);

/// @brief Check if the given comment is valid.
/// @param f The FILE* we're reading.
/// @param file The file name we're reading.
/// @param line A pointer to an integer,
/// representing the line we're currently on.
/// @return 0 if there is an error, else 1.
int check_comment(FILE *f, char const *file, int *line);

/// @brief Check if the given name is valid.
/// @param f The FILE* we're reading.
/// @param file The file name we're reading.
/// @param line A pointer to an integer,
/// representing the line we're currently on.
/// @return 0 if there is an error, else 1.
int check_name(FILE *f, char const *file, int *line);

/// @brief Get the arguments for a command.
/// @param c The command we want to get the arguments of.
/// @param words The command's arguments.
void get_args(command_t *c, char **words);

/// @brief Create a label object.
/// @param name The name of the label.
/// @param cmd The command it is linked to.
/// @return A new label_t representing the label.
label_t *create_label(char const *name, command_t *cmd);

/// @brief Split the next line from a file.
/// @param base_words The base word array
/// @param f The file.
/// @param nb_line A pointer to the number of lines read so far.
/// @return A str array containing the new line, splitted.
char **split_next_line(char ***base_words, FILE *f, int *nb_line);

/// @brief Create a null command object.
/// @param prev The previous command.
/// @return A new command_t containing a null command.
command_t *create_null_command(command_t *prev);

/// @brief Get all the data from a line.
/// @param words The current words.
/// @param buf The file buffer.
/// @param line The current line.
void get_data(char **words, file_buffer_t *buf, char *line);

/// @brief Check if the argument given to the direct label is valid.
/// @param arg The argument.
/// @param err_mess A pointer to a string, to contain an error message.
/// @return T_DIR if the label is valid, else T_ERROR.
char check_direct_validity(char const *arg, char **err_mess);

/// @brief Check if the given label has a copy.
/// @param labels The label list.
/// @param lab The label to check.
/// @param except The label to except from check.
/// @return 1 if it has a copy, else 0.
int has_copy(list_t *labels, label_t *lab, list_t *except);

/// @brief Check if there is 2 times the same label.
/// @param labels The labels
/// @return 1 if there is doubles, else 0.
int has_double(list_t *labels);

/// @brief Get the position of the label 'name'.
/// @param labels The list of labels
/// @param name The name of the label to find
/// @param not_found A pointer to an integer,
/// telling if we have found the command or not.
/// @return The label pos. If it has not been found,
/// returns 0 and set not_found to 1.
int32_t get_label_pos(list_t *labels, char const *name, int *not_found);

/// @brief Search and replace the labels of the given command.
/// @param current The comma d in which the labels have to be changed.
/// @param index_of_label The index of the label in the command's arguments
/// @param labels The list of labels
/// @return 0 if it failed, 1 if it succeeded.
int search_for_label(command_t *current, int index_of_label, list_t *labels);

/// @brief Write a single command to fd.
/// @param cmd The command to write
/// @param fd The file descriptor in wich to write
/// @return The number of byte effectively written.
int write_command(command_t *cmd, int fd);

/// @brief Add a 2-byte integer to the command's parameters
/// @param c The command
/// @param i The value to add
static inline void add_int16t(command_t *c, int16_t i)
{
    my_memcpy(c->params + c->cmd_size, &i, 2);
    c->cmd_size += 2;
}

/// @brief Add a 2-byte integer to the command's parameters
/// @param c The command
/// @param i The value to add
static inline void add_int32t(command_t *c, int32_t i)
{
    my_memcpy(c->params + c->cmd_size, &i, 4);
    c->cmd_size += 4;
}

/// @brief Check if the given command must have a coding byte or not.
/// @param x The code of the command
/// @return 1 if the command must not have a coding byte, else 0.
static inline int is_special_case(int x)
{
    return (x == 1) || (x == 9) || (x == 12) || (x == 15);
}

/// @brief Get the offset of the progsize, inside the header_t structure
/// @return size_t representing the offset in the header_t structure
static inline size_t progsize_offset(void)
{
    return (size_t)(&((header_t *)NULL)->prog_size);
}

#endif /* !ASM_H_ */
