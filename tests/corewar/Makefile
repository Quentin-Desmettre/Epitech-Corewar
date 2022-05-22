##
## EPITECH PROJECT, 2021
## B-CPE-201-LIL-2-1-corewar-noa.trachez
## File description:
## Makefile
##

SRC = \
	test.c \
	test_champ_handling.c \
	test_champ.c \
	test_check_adress.c \
	test_check_args.c \
	test_check_champ.c \
	test_check_dump_args.c \
	test_check_num.c \
	test_header.c \
	test_instruction1.c \
	test_instruction2.c \
	test_instruction3.c \
	test_setmap.c \
	test_setup_champ.c \
	test_str_arena.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -I ../../include/ -I ../../lib/my/include \
	-I ../../include/corewar_include -I ../../include

all: $(OBJ)

clean:
	rm -f $(OBJ)

fclean:    clean
	rm -f $(NAME)

re:        fclean all
