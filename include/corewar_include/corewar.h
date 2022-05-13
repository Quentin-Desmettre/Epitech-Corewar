/*
** EPITECH PROJECT, 2022
** B_CPE_201_LIL_2_1_corewar_noa_trachez
** File description:
** TODO: description
*/

#ifndef COREWAR_H
    #define COREWAR_H

// ARGS
typedef struct {
    int args[3];
    char type[3];
} args_t;

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

// lib
void my_memcpy(void *dest, void *source, size_t size);

#endif /*COREWAR_H*/
