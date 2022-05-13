##
## EPITECH PROJECT, 2021
## B-CPE-201-LIL-2-1-corewar-noa.trachez
## File description:
## Makefile
##

ARGS	=	args/arg_manage.c \
			args/check_args.c \
			args/check_champ.c \
			args/num_champ.c \
			main.c\
			convert_endian.c \

CHAMP	=	champ/create_champ.c \
			champ/read_check_header.c \

VMCORE	=	instructions/instructions_manager.c \
			instructions/i_conditions.c \
			instructions/i_load.c \
			instructions/i_misc.c \
			instructions/i_operations.c \
			instructions/i_store.c \

SRC	=	$(ARGS) $(CHAMP) $(VMCORE)

OBJ	=	$(SRC:.c=.o)

NAME	=	corewar

FLAGS	=	-Wall -Wextra -g

LIB	=	-L ../lib/my -l my

INCLUDE	=	-I ../lib/my/include -I ../include -I ../include/corewar_include

CFLAGS	=	-Wall -Wextra $(LIB) $(INCLUDE)

all: build_lib compile

build_lib:
	@make --no-print-directory -C ../lib/my/

compile: $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LIB) $(INCLUDE)

clean:
	@make clean --no-print-directory -C ../lib/my/
	rm -f $(OBJ)
	find . -name "*.gcda" -delete
	find . -name "*.gcno" -delete
	find . -name "*.html" -delete
	find . -name "*.css" -delete
	find . -name "*.gcov.txt" -delete

fclean: clean
	@make fclean --no-print-directory -C ../lib/my/
	rm -f $(NAME)

re:	fclean all

valgrind:
	gcc -o $(NAME) $(FLAGS) $(SRC) $(LIB) $(INCLUDE) -g

tests: CFLAGS += --coverage
tests: $(OBJ)
	make -s -C ../lib/my/
	make -s --no-print-directory -C ../tests/corewar/
	gcc $(CFLAGS) -o test_bin -g $(OBJ) ../tests/corewar/*.o -lcriterion -lmy --coverage
	./test_bin ; echo -ne
	@make clean
