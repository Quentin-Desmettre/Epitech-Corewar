##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

SRC = \
	test_asm_h.c         \
	test_check_command.c \
	test_compile.c       \
	test_compile2.c      \
	test_get_args.c      \
	test_get_header.c    \
	test_has_error.c     \
	test_label.c         \
	test_write_buffer.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -I ../../include/ -I ../../lib/my/include \
	-I ../../include/corewar_include

all: $(OBJ)

clean:
	rm -f $(OBJ)

fclean:    clean
	rm -f $(NAME)

re:        fclean all
