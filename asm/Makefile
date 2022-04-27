##
## EPITECH PROJECT, 2021
## B-CPE-201-LIL-2-1-corewar-noa.trachez
## File description:
## Makefile
##

SRC	=	main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	asm

FLAGS	=	-Wall -Wextra -g

LIB	=	-L lib/ -l my

INCLUDE	=	-I ../include/

CFLAGS	=	-Wall -Wextra $(LIB) $(INCLUDE)

all: build_lib compile

build_lib:
	@make --no-print-directory -C lib/my
	@echo -e "\033[44m#####= LIB COMPILED =#####\e[0m"

compile: $(OBJ)
	@echo -e "\033[1;34m#####= Compiling Project... =#####\e[0m"
	gcc -o $(NAME) $(OBJ) $(LIB) $(INCLUDE)
	@echo -e "\033[42m#####= COMPILATION FINISHED =#####\e[0m"

clean:
	@echo -e "\033[1;31m#####= Removing .o files... =#####\e[0m"
	@make clean --no-print-directory -C lib/my
	rm -f $(OBJ)

fclean: clean
	@make fclean --no-print-directory -C lib/my
	@echo -e "\033[1;31m#####= Removing binary file... =#####\e[0m"
	rm -f $(NAME)
	@echo -e "\033[41m#####= CLEANING DONE =#####\e[0m"

re:	fclean all

valgrind:
	gcc -o $(NAME) $(FLAGS) $(SRC) $(LIB) $(INCLUDE) -g
