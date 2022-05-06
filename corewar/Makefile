##
## EPITECH PROJECT, 2021
## B-CPE-201-LIL-2-1-corewar-noa.trachez
## File description:
## Makefile
##

SRC	=	main.c \
		convert_endian.c

ARGS	=	args/arg_manage.c \
			args/check_args.c \
			args/check_champ.c \
			args/num_champ.c

CHAMP	=	champ/create_champ.c \
			champ/read_check_header.c

OBJ	=	$(SRC:.c=.o) $(ARGS:.c=.o) $(CHAMP:.c=.o)

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
	gcc -o $(NAME) $(FLAGS) $(SRC) $(ARGS) $(CHAMP) $(LIB) $(INCLUDE) -g
