##
## EPITECH PROJECT, 2021
## B-CPE-201-LIL-2-1-corewar-noa.trachez
## File description:
## Makefile
##

COMPILE = \
		compile.c \
		compile/compile.c

ERROR = \
		error/has_error.c

SRC	=	$(COMPILE) \
		$(ERROR)

OBJ	=	$(SRC:.c=.o)

NAME	=	asm

FLAGS	=	-Wall -Wextra -g

LIB	=	-L ../lib/my -l my

INCLUDE	=	-I ../lib/my/include -I ../include/corewar_include -I ../include

CFLAGS	=	-Wall -Wextra $(LIB) $(INCLUDE)

all: build_lib compile

build_lib:
	@make --no-print-directory -C ../lib/my/

compile: SRC += main.c
compile: $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LIB) $(INCLUDE)

clean:
	@make clean --no-print-directory -C ../lib/my/
	rm -f $(OBJ)

fclean: clean
	@make fclean --no-print-directory -C ../lib/my/
	rm -f $(NAME)
	rm -f test_bin

re:	fclean all

valgrind:
	gcc -o $(NAME) $(FLAGS) $(SRC) $(LIB) $(INCLUDE) -g

tests: CFLAGS += --coverage
tests: $(OBJ)
	make -s -C ../lib/my/
	make -s --no-print-directory -C ../tests/asm/
	gcc $(CFLAGS) -o test_bin -g $(OBJ) ../tests/asm/*.o -lcriterion -lmy  --coverage
	./test_bin ; echo -ne
