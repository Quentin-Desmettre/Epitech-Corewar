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
    #include "libmy.h"
    #include "op.h"


/// \brief Check if the given file has error
/// \param file The file to check
/// \return 1 if the file is invalid, 0 if it is valid
int has_error(char const *file);

/// \brief Compile and write the file to the correct output file
/// \param f The openned FILE stream representing the input file
/// \param file The output file
/// \return 1 on success, 0 on failure
int write_file(FILE *f, char const *file);

/// \brief Get the appropriate output file name for a given input file
/// \param file The input file
/// \return The newly allocated string, containing the appropriate
/// output file name
char const *get_output_file(char const *file);

/// \brief Get the next line of the file stream f
/// \param f The file stream
/// \return A newly allocated string, containing the next line, Or NULL if
/// getline failed. In case of an error, errno is set to indicate the cause.
/// You should always free the given string.
char *get_next_line(FILE *f);

#endif /* !ASM_H_ */
