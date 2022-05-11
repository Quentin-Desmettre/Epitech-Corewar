/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_COREWAR_NOA_TRACHEZ_OP_H
** File description:
** op.h
*/
#ifndef _OP_H_
    #define _OP_H_
    #define MEM_SIZE (6*1024)
    #define IDX_MOD 512   /* modulo of the index < */
    #define MAX_ARGS_NUMBER 4
    #define COMMENT_CHAR '#'
    #define LABEL_CHAR ':'
    #define DIRECT_CHAR '%'
    #define SEPARATOR_CHAR ','
    #define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"
    #define NAME_CMD_STRING ".name"
    #define COMMENT_CMD_STRING ".comment"
    #define REG_NUMBER 16
    #include <unistd.h>
    #include <fcntl.h>
    #include "libmy.h"

typedef char args_type_t;

    #define T_REG 1
    #define T_DIR 2
    #define T_IND 4
    #define T_LAB 8
    #define T_ERROR 0

typedef struct op_s {
    char *mnemonique;
    char nbr_args;
    args_type_t type[MAX_ARGS_NUMBER];
    char code;
    int nbr_cycles;
    char *comment;
} op_t;

    #define IND_SIZE 2
    #define DIR_SIZE 4
    #define REG_SIZE DIR_SIZE

    #define PROG_NAME_LENGTH 128
    #define COMMENT_LENGTH 2048
    #define COREWAR_EXEC_MAGIC 0xea83f3

typedef struct header_s {
    int magic;
    char prog_name[PROG_NAME_LENGTH + 1];
    int prog_size;
    char comment[COMMENT_LENGTH + 1];
} header_t;

    #define CYCLE_TO_DIE 1536
    #define CYCLE_DELTA 5
    #define NBR_LIVE 40

static const op_t op_tab[] = {
    {"live", 1, {T_DIR}, 1, 10, "alive"},
    {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load"},
    {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store"},
    {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition"},
    {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction"},
    {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
    "et (and  r1, r2, r3   r1&r2 -> r3"},
    {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
    "ou  (or   r1, r2, r3   r1 | r2 -> r3"},
    {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
    "ou (xor  r1, r2, r3   r1^r2 -> r3"},
    {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero"},
    {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
    "load index"},
    {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
    "store index"},
    {"fork", 1, {T_DIR}, 12, 800, "fork"},
    {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load"},
    {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
    "long load index"},
    {"lfork", 1, {T_DIR}, 15, 1000, "long fork"},
    {"aff", 1, {T_REG}, 16, 2, "aff"},
    {0, 0, {0}, 0, 0, 0}
};

typedef struct champ_s{
    int champ_nbr;
    char *name_champ;
    int nb_is_impose;
    int adress;
    int adress_impose;
    char *instruction;
    header_t header;
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
} param_champ_t;

//main.c
int help_message(char *name_binarie);
void print_info_champ(champ_t *info_champ);

//check args
void check_dump(param_champ_t *param, char *arg);
void check_num(param_champ_t *param, char *arg);
void check_address(param_champ_t *param, char *arg);

//create champ
champ_t *init_node(param_champ_t *param, char *path_file);
void append_champ(char *path_file, param_champ_t *param, champ_t **info_champ);
void create_champ(char *path_file, param_champ_t *param, champ_t **info_champ);

//check champ
void delete_champ(champ_t **info_champ);
int get_num_of_champ(champ_t **info_champ);
void check_champ(int nb_to_change, champ_t **info_champ);

//num champ
void find_little_number(int valid_num[][4], int *nbr);
void setup_valid_num(champ_t **info_champ, int valid_num[][4]);
void set_champ_real_num(champ_t **info_champ, int valid_num[][4]);
void change_all_nb_champ(champ_t **info_champ, int nb);
int check_same_nbr(param_champ_t *param);

//arg manage
param_champ_t *init_value(void);
int check_if_opt(param_champ_t *param, char *str, char *str_next, int *index);
void check_argv(int *ac, char **av, int *dump_cycle, champ_t **info_champ);

//endian
void convert_endian(int *nbr);

//header_champ
void check_header(champ_t **info_champ, size_t size);
void read_header(champ_t **info_champ, size_t size);
void fill_header_champ(champ_t **info_champ);

#endif
