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

CHAMP	=	champ/create_champ.c \
			champ/read_check_header.c \
			champ/sort_champ.c \

VMCORE	=	instructions/instructions_manager.c \
			instructions/exec_instructions.c \
			instructions/i_conditions.c \
			instructions/i_load.c \
			instructions/i_misc.c \
			instructions/i_operations.c \
			instructions/i_store.c \
			instructions/check_instruction.c \
			instructions/replace_indirects.c \
			cor_string_manip/cor_str.c \
			cor_string_manip/arena_cor.c \

SRC_TESTS = convert_endian.c \
	corewar.c \
	glob.c \
	globals.c \
	$(ARGS) \
	$(CHAMP) \
	$(VMCORE) \

SRC = $(SRC_TESTS) \
	main.c

OBJ	=	$(SRC_TESTS:.c=.o)

OBJ2 = $(SRC:.c=.o)

NAME	=	corewar

FLAGS	=	-Wall -Wextra -g

LIB	=	-L ../lib/my -l my

INCLUDE	=	-I ../lib/my/include -I ../include -I ../include/corewar_include

CFLAGS	=	-Wall -Wextra $(LIB) $(INCLUDE)

all: build_lib compile

build_lib:
	@make --no-print-directory -C ../lib/my/

compile: $(OBJ2)
	gcc -o $(NAME) $(OBJ2) $(LIB) $(INCLUDE)

clean:
	@make clean --no-print-directory -C ../lib/my/
	rm -f $(OBJ2)

fclean: clean
	@make fclean --no-print-directory -C ../lib/my/
	rm -f $(NAME)

re:	fclean all

valgrind:	CFLAGS += -g
valgrind:	clean $(OBJ2)
	gcc -o $(NAME) $(OBJ2) $(LIB) $(INCLUDE)

tests: CFLAGS += --coverage -DCRITERION
tests: $(OBJ)
	make -s -C ../lib/my/
	make -s --no-print-directory -C ../tests/corewar/
	gcc $(CFLAGS) -o test_bin -g $(OBJ) ../tests/corewar/*.o -lcriterion \
	-lmy --coverage
	./test_bin ; echo -ne
