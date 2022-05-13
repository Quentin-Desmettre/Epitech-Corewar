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

SRC_TEST = \
		$(COMPILE) \
		$(ERROR)

SRC = $(SRC_TEST) \
	main.c

OBJ	=	$(SRC_TEST:.c=.o)

OBJ2 = $(SRC:.c=.o)

NAME	=	asm

FLAGS	=	-Wall -Wextra -g

LIB	=	-L ../lib/my -l my

INCLUDE	=	-I ../lib/my/include -I ../include/corewar_include -I ../include

CFLAGS	=	-Wall -Wextra $(LIB) $(INCLUDE)

all: build_lib compile

build_lib:
	@make --no-print-directory -C ../lib/my/

compile: $(OBJ2)
	gcc -o $(NAME) $(OBJ2) $(LIB) $(INCLUDE) $(CFLAGS)

debug: CFLAGS += -g
debug: all

clean:
	@make clean --no-print-directory -C ../lib/my/
	rm -f $(OBJ2)
	find . -name "*.gcda" -delete
	find . -name "*.gcno" -delete
	find . -name "*.html" -delete
	find . -name "*.css" -delete
	find . -name "*.gcov.txt" -delete

fclean: clean
	@make fclean --no-print-directory -C ../lib/my/
	rm -f $(NAME)
	rm -f test_bin

re:	fclean all

valgrind:
	gcc -o $(NAME) $(FLAGS) $(SRC_TEST) $(LIB) $(INCLUDE) -g

tests: CFLAGS += --coverage
tests: $(OBJ)
	make -s -C ../lib/my/
	make -s --no-print-directory -C ../tests/asm/
	gcc $(CFLAGS) -o test_bin -g $(OBJ) ../tests/asm/*.o -lcriterion -lmy
	./test_bin ; echo -ne

functional_tests: all
	cp ./asm ../tests/asm/functional/my/
	cd ../tests/asm/functional/ ; python tester.py ; cd -