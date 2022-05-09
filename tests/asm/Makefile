##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

SRC = \
	test.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -I ../../include/ -I ../../lib/my/include \
	-I ../../include/corewar_include -I ../../include

all: $(OBJ)

clean:
	rm -f $(OBJ)

fclean:    clean
	rm -f $(NAME)

re:        fclean all
