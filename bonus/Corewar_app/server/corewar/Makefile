##
## EPITECH PROJECT, 2021
## B-CPE-201-LIL-2-1-corewar-noa.trachez
## File description:
## Makefile
##

all	:
	make -C asm
	make -C corewar

re	:
	make re -C asm
	make re -C corewar

clean	:
	make clean -C asm
	make clean -C corewar
	find . -name "*.gcda" -delete
	find . -name "*.gcno" -delete
	find . -name "*.o" -delete
	find . -name "vgcore.*" -delete

fclean	:
	make fclean -C asm
	make fclean -C corewar
