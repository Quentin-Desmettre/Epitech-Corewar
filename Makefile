##
## EPITECH PROJECT, 2021
## B-CPE-201-LIL-2-1-corewar-noa.trachez
## File description:
## Makefile
##

all	:
	make -C asm
	make -C corewar

clean	:
	make clean -C asm
	make clean -C corewar

fclean	:
	make fclean -C asm
	make fclean -C corewar
