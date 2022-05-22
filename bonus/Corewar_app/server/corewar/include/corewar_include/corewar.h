/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#ifndef COREWAR_H
    #define COREWAR_H
    #include "op.h"
    #define IS_SPECIAL_CASE(x) contain((char []){1, 9, 12, 15, 0}, x)

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

//check args
void check_dump(param_argv_t *param, char *arg);
void check_num(param_argv_t *param, char *arg);
void check_address(param_argv_t *param, char *arg);

//create champ
void create_champ(char *path_file, param_argv_t *param, champ_t **info_champ);

//check champ
void delete_champ(champ_t **info_champ);
int get_num_of_champ(champ_t **info_champ);
void setup_all_champ_for_game(champ_t **info_champ);
void check_champ(champ_t **info_champ);

//num champ
void setup_valid_num(champ_t **info_champ, int valid_num[][4]);
void set_champ_real_num(champ_t **info_champ, int valid_num[][4]);
int check_same_nbr(param_argv_t *param);

//arg manage
void check_argv(int *ac, char **av, int *dump_cycle, champ_t **info_champ);
void fill_header_champ(champ_t **info_champ);

//endian
void convert_endian(int *nbr);
void convert_endian_short(short *nbr);

//sort_champ
champ_t *sort_my_list(champ_t *champ);

//corewar
void dump_print(char *map);
char *set_map(champ_t **champ, char *map);
void setup_game(int ac, char **av);

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

// instructions
int i_has_index(int mnemonic, int nb_arg);
void instruction_reader(char *instructions, champ_t *champ);
void exec_instructions(champ_t *champ, char *map);

// lib
void my_memcpy(void *dest, void *source, size_t size);
void memcpy_cor(void *dest, char *arena, int start, int size);
void cpy_in_arena(char *arena, void *src, int start, int size);
char *cor_strcpy(char *str1, const char *str2, const int cc[2], size_t size);

//glob
int *get_cycle_to_die(void);
champ_t **get_champ_struct(void);

//check_instruction
void get_coding_byte(char coding_byte, args_t *args);
int number_of_args(args_t *args);
int are_types_valid(args_t *args, int op_code, int nb_arg);
int size_of_arg(int code, int nb, char types[3]);
champ_t *last_to_live(champ_t *new);
champ_t **all_champs(champ_t **new);
champ_t **fork_list(void);
void check_alive_champ(champ_t **champ, int need_dump, char *map);
void increase_counter(void);
void replace_indirects(champ_t *champ, char *arena);
int get_alive_champs(champ_t *champs);

#endif /*COREWAR_H*/
