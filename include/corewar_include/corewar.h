/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#ifndef COREWAR_H
    #define COREWAR_H
    #include "op.h"

enum I_TYPE {EMPTY, REGISTER, DIRECT, INDIRECT};

// ARGS
typedef struct {
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
    char registers[REG_NUMBER];
    int cycle;
    int cycle_to_wait;
    int pc;
    int is_alive;
    header_t header;
    param_champ_t param;
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

//main.c
int help_message(char *name_binarie);
void print_info_champ(champ_t *info_champ);

//check args
void check_dump(param_argv_t *param, char *arg);
void check_num(param_argv_t *param, char *arg);
void check_address(param_argv_t *param, char *arg);

//create champ
champ_t *init_node(param_argv_t *param, char *path_file);
void append_champ(char *path_file, param_argv_t *param, champ_t **info_champ);
void create_champ(char *path_file, param_argv_t *param, champ_t **info_champ);

//check champ
void delete_champ(champ_t **info_champ);
int get_num_of_champ(champ_t **info_champ);
void setup_all_champ_for_game(champ_t **info_champ);
void check_champ(int nb_to_change, champ_t **info_champ);

//num champ
void find_little_number(int valid_num[][4], int *nbr);
void setup_valid_num(champ_t **info_champ, int valid_num[][4]);
void set_champ_real_num(champ_t **info_champ, int valid_num[][4]);
void change_all_nb_champ(champ_t **info_champ, int nb);
int check_same_nbr(param_argv_t *param);

//arg manage
param_argv_t *init_value(void);
int check_if_opt(param_argv_t *param, char *str, char *str_next, int *index);
void check_argv(int *ac, char **av, int *dump_cycle, champ_t **info_champ);

//endian
void convert_endian(int *nbr);

//header_champ
void check_header(champ_t **info_champ, size_t size);
void read_header(champ_t **info_champ, size_t size);
void fill_header_champ(champ_t **info_champ);

//sort_champ
int find_little_but_higher(champ_t *champ, int int_compare);
champ_t *create_nodes(champ_t *info, int champ);
champ_t *append_champ_with_value(champ_t *sorted, int little, champ_t *all);
champ_t *sort_my_list(champ_t *champ);

//my_exit
char *cor_strcpy(char *str1, const char *str2, const int cc[2], size_t size);

//corewar
void dump_print(char *map);
char *set_map(champ_t *champ, char *map);
void main_loop(char *map, champ_t *champions, int dump_cycle);
void print_winner(champ_t *info_champ);
void setup_game(int ac, char **av);

// Instructions
int i_live(int arga);
int i_zjmp(int arga);
int i_fork(int arga);
int i_lfork(int arga);
int i_aff(int arga);
int i_st(int arga, int argb);
int i_sti(int arga, int argb, int argc);
int i_ld(int arga, int argb);
int i_ldi(int arga, int argb, int argc);
int i_lld(int arga, int argb);
int i_lldi(int arga, int argb);
int i_add(int arga, int argb, int argc);
int i_sub(int arga, int argb, int argc);
int i_and(int arga, int argb, int argc);
int i_or(int arga, int argb, int argc);
int i_xor(int arga, int argb, int argc);

int i_has_index(int mnemonic, int nb_arg);
int get_instruction_args(int mnemonic, char *instructions, args_t *args);

#endif /*COREWAR_H*/
