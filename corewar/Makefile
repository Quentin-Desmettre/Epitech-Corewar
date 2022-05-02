##
## EPITECH PROJECT, 2021
## B-CPE-201-LIL-2-1-corewar-noa.trachez
## File description:
## Makefile
##

SRC	=	main.c \
		arg_manage.c \
		check_args.c

OBJ	=	$(SRC:.c=.o)

NAME	=	corewar

FLAGS	=	-Wall -Wextra -g

LIB	=	-L ../lib/my -l my

INCLUDE	=	-I ../lib/my/include -I ../include

CFLAGS	=	-Wall -Wextra $(LIB) $(INCLUDE)

all: build_lib compile

build_lib:
	@make --no-print-directory -C ../lib/my/

compile: $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LIB) $(INCLUDE)

clean:
	@make clean --no-print-directory -C ../lib/my/
	rm -f $(OBJ)

fclean: clean
	@make fclean --no-print-directory -C ../lib/my/
	rm -f $(NAME)

re:	fclean all

valgrind:
	gcc -o $(NAME) $(FLAGS) $(SRC) $(LIB) $(INCLUDE) -g
