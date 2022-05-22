/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

/// @file corewar.h
/// @brief Main corewar header

#ifndef COREWAR_H
    #define COREWAR_H
    #include "op.h"
    #define IS_SPECIAL_CASE(x) contain((char []){1, 9, 12, 15, 0}, (x))
    #define HAS_MOD_IDX(x) contain((char []){2, 3, 6, 7, 8, 10, 11, 0}, (x))

// ARGS
typedef struct {
    int code;
    int byte_offset;
    int tmp_ldi;
    int args[3];
    char type[3];
} args_t;

typedef struct param_champ_s {
    int champ_nbr;
    int nb_is_impose;
    int adress;
    int adress_impose;
} param_champ_t;

typedef struct champ_s{
    char *name_champ;
    char *instruction;
    int registers[REG_NUMBER];
    int cycle;
    int cycle_to_wait;
    int pc;
    int is_alive;
    int carry;
    header_t header;
    param_champ_t param;
    args_t args;
    struct champ_s *next;
} champ_t;

typedef struct {
    int adress_act;
    int adress_next;
    int num_champ;
    int index;
    int num_impose[5];
    int last_opt;
    int dump_cycle;
} param_argv_t;

/// @brief check the argument -dump option
/// @param param the number of cycle of the dump
/// @param arg the argument of the -dump
void check_dump(param_argv_t *param, char *arg);

/// @brief check the argument -num option
/// @param param the number_impose and the index
/// @param arg the argument of the -num
void check_num(param_argv_t *param, char *arg);

/// @brief check the argument -a option
/// @param param the next adress
/// @param arg the argument of the -a
void check_address(param_argv_t *param, char *arg);

/// @brief create a champion
/// @param path_file the path to the champ
/// @param param the structure with the parameters of the champion
/// @param info_champ the structure with the information of the champion
void create_champ(char *path_file, param_argv_t *param, champ_t **info_champ);

/// @brief delete a champion
/// @param info_champ the structure with the information of the champion
void delete_champ(champ_t **info_champ);

/// @brief get the number of alive champion
/// @param info_champ the structure with the information of the champion
int get_num_of_champ(champ_t **info_champ);

/// @brief setup all the champions
/// @param info_champ the structure with the information of the champion
void setup_all_champ_for_game(champ_t **info_champ);

/// @brief check all the
/// @param info_champ the structure with the information of the champion
void check_champ(champ_t **info_champ);

/// @brief get a valid number on the information of the champion
/// @param info_champ the structure with the information of the champion
/// @param valid_num a board of valid numbers for setup the champ
void setup_valid_num(champ_t **info_champ, int valid_num[][4]);

/// @brief setup the valid number get by setup_valid_num on the information of
/// the champion
/// @param info_champ the structure with the information of the champion
/// @param valid_num a board of valid numbers for setup the champ
void set_champ_real_num(champ_t **info_champ, int valid_num[][4]);

/// @brief check if the param number of the champion and the max are the same
/// @param param the parameters of the arguments of the champion
/// @return 0 on success, 1 on failure
int check_same_nbr(param_argv_t *param);

/// @brief check all the arguments
/// @param ac the number of arguments
/// @param av a board with al the arguments
/// @param dump_cycle the number of cycle
/// @param info_champ the structure with the information of the champion
void check_argv(int *ac, char **av, int *dump_cycle, champ_t **info_champ);

/// @brief check if the header of the champion's information is correct
/// @param info_champ the structure with the information of the champion
void fill_header_champ(champ_t **info_champ);

/// @brief convert in indian
/// @param nbr the number to convert
void convert_endian(int *nbr);

/// @brief convert in low indian
/// @param nbr the number to convert
void convert_endian_short(short *nbr);

/// @brief sort a linked list of champions
/// @param champ a structure with all the champions
/// @return the sorted list of champions
champ_t *sort_my_list(champ_t *champ);

/// @brief print the -dump
/// @param map is the map to print
void dump_print(char *map);

/// @brief set the map with the champions before the print
/// @param champ a structure with all the champions
/// @param map is the map to print
char *set_map(champ_t **champ, char *map);

/// @brief
/// @param ac the number of arguments
/// @param av a board with al the arguments
corewar_grap_t *setup_game(int ac, char **av);

// Instructions
int i_live(int arg[3], champ_t *champ, char *arena);
int i_zjmp(int arg[3], champ_t *champ, char *arena);
int i_fork(int arg[3], champ_t *champ, char *arena);
int i_lfork(int arg[3], champ_t *champ, char *arena);
int i_aff(int arg[3], champ_t *champ, char *arena);
int i_st(int arg[3], champ_t *champ, char *arena);
int i_sti(int arg[3], champ_t *champ, char *arena);
int i_ld(int arg[3], champ_t *champ, char *arena);
int i_ldi(int arg[3], champ_t *champ, char *arena);
int i_lld(int arg[3], champ_t *champ, char *arena);
int i_lldi(int arg[3], champ_t *champ, char *arena);
int i_add(int arg[3], champ_t *champ, char *arena);
int i_sub(int arg[3], champ_t *champ, char *arena);
int i_and(int arg[3], champ_t *champ, char *arena);
int i_or(int arg[3], champ_t *champ, char *arena);
int i_xor(int arg[3], champ_t *champ, char *arena);

/// @brief check the potential indexes error
/// @param mnemonic
/// @param nb_arg the number of arguments
int i_has_index(int mnemonic, int nb_arg);

/// @brief read the instruction
/// @param instructions is the instruction to read
/// @param champ a structure with all the champions
void instruction_reader(char *instructions, champ_t *champ);

/// @brief execute the instruction
/// @param champ a structure with all the champions
/// @param map where the instructions are execute
void exec_instructions(champ_t *champ, char *map);

/// @brief copy in the memory
/// @param dest the destination for the copy
/// @param source the things to copy
/// @param size the size of the copy
void my_memcpy(void *dest, void *source, size_t size);

/// @brief copy in the core ware memory
/// @param dest the things to copy
/// @param arena the destination for the copy
/// @param start the start position on the arena for the copy
/// @param size the size of the copy
void memcpy_cor(void *dest, char *arena, int start, int size);

/// @brief copy in the arena
/// @param src the things to copy
/// @param arena the destination for the copy
/// @param start the start position on the arena for the copy
/// @param size the size of the copy
void cpy_in_arena(char *arena, void *src, int start, int size);

/// @brief cpu a string in another one and count the overlap
/// @param str1 the str to copy
/// @param str2 the copy of the str
/// @param cc[0] the size of the arena
/// @param cc[1] a counter fo the overlap
/// @param size the size of the copy
/// @return the copy
char *cor_strcpy(char *str1, const char *str2, const int cc[2], size_t size);

/// @brief get the cycle
/// @return the cycle
int *get_cycle_to_die(void);

/// @brief get the champ
/// @return the champ
champ_t **get_champ_struct(void);

/// @brief get the instruction code in byte
/// @param coding_byte the code to get
/// @param args the arguments to parse to get the code
void get_coding_byte(char coding_byte, args_t *args);

/// @brief get the good number of arguments according to the instruction
/// @param args the number of arguments to parse according to the instruction
/// @return the number of arguments
int number_of_args(args_t *args);

/// @brief check if is the good type of arguments according to the instruction
/// @param args  arguments to parse
/// @param op_code the instruction code in byte
/// @param nb_arg the number of arguments
/// @return 0 on success, 1 on failure
int are_types_valid(args_t *args, int op_code, int nb_arg);

/// @brief get the size of the arguments
/// @param code the instruction code
/// @param nb the number of arguments
/// @param types the different possible types
/// @return teh size
int size_of_arg(int code, int nb, char types[3]);

/// @brief get the last champion alive
/// @param new the champion
/// @return the alive champion
champ_t *last_to_live(champ_t *new);

/// @brief get all the champion
/// @param new the champion
/// @return all the champion
champ_t **all_champs(champ_t **new);

/// @brief do the fork list
/// @return the list
champ_t **fork_list(void);

/// @brief check if the champion is alive
/// @param champ the struct with all the champions
/// @param need_dump if need a dump of not
/// @param map the map to print if is a dump
char *check_alive_champ(champ_t **champ, int need_dump, char *map);

/// @brief increase a counter
void increase_counter(void);

/// @brief replace the value
/// @param champ the struct with all the champions
/// @param arena the arena
void replace_indirects(champ_t *champ, char *arena);

/// @brief get the alive champion
/// @param champs all the champion
int get_alive_champs(champ_t *champs);

#endif /*COREWAR_H*/
