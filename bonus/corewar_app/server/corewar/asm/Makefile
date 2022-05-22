##
## EPITECH PROJECT, 2021
## B-CPE-201-LIL-2-1-corewar-noa.trachez
## File description:
## Makefile
##

COMPILE = \
		compile.c                      \
		compile/compile.c              \
		compile/get_args.c             \
		compile/get_header.c           \
		compile/labels.c               \
		compile/write_buffer.c

ERROR = \
		error/has_error.c              \
		error/check_commands.c         \
		endian.c

SRC = \
		main.c\
		$(COMPILE) \
		$(ERROR)

OBJ = $(SRC:.c=.o)

NAME	=	asm

LIB	=	-L ../lib/my -l my

INCLUDE	=	-I ../lib/my/include -I ../include/corewar_include -I ../include

CFLAGS	=	-Wall -Wextra $(LIB) $(INCLUDE)

all: build_lib compile

build_lib:
	@make --no-print-directory -C ../lib/my/

compile: $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LIB) $(INCLUDE) $(CFLAGS)

clean:
	@make clean --no-print-directory -C ../lib/my/
	rm -f $(OBJ)

fclean: clean
	@make fclean --no-print-directory -C ../lib/my/
	rm -f $(NAME)

re:	fclean all
