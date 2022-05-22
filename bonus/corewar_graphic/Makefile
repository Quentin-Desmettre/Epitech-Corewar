##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

SRC = \
	src/button/build_button.c                          \
	src/button/button.c                                \
	src/button/change_button.c                         \
	src/button/get_button_ev.c                         \
	src/button/setters.c                               \
	src/button/setters_next.c                          \
	src/clock/clock_list.c                             \
	src/clock/my_clock.c                               \
	src/clock/time.c                                   \
	src/free.c                                         \
	src/global_win/init_window.c                       \
	src/global_win/rescale_all.c                       \
	src/global_win/transition.c                        \
	src/globals/fonts.c                                \
	src/globals/pnj.c                                  \
	src/globals/sounds.c                               \
	src/globals/texture.c                              \
	src/globals/window.c                               \
	src/line_edit/create.c                             \
	src/line_edit/events.c                             \
	src/main.c                                         \
	src/rand/srand.c                                   \
	src/settings/apply.c                               \
	src/settings/checkbox.c                            \
	src/settings/destroy.c                             \
	src/settings/load.c                                \
	src/settings/move_settings.c                       \
	src/settings/rendering_evt.c                       \
	src/settings/save.c                                \
	src/settings/scale_settings.c                      \
	src/settings/set_evt.c                             \
	src/settings/set_evt_manager.c                     \
	src/settings/settings.c                            \
	src/settings/sound_evt.c                           \
	src/settings/visu_updates.c                        \
	src/sound_builder/build_music.c                    \
	src/sound_builder/build_sfx.c                      \
	src/sprite/init_sprite.c                           \
	src/sprite/rotate_vector.c                         \
	src/sprite/sprite_modif.c                          \
	src/main_menuu/create.c                            \
	src/create_game/create.c                           \
	corewar/args/arg_manage.c                          \
	corewar/args/check_args.c                          \
	corewar/args/check_champ.c                         \
	corewar/args/num_champ.c                           \
	corewar/champ/read_check_header.c                  \
	corewar/champ/sort_champ.c                         \
	corewar/champ/create_champ.c                       \
	corewar/convert_endian.c                           \
	corewar/instructions/check_instruction.c           \
	corewar/instructions/instructions_manager.c        \
	corewar/instructions/i_misc.c                      \
	corewar/instructions/i_conditions.c                \
	corewar/instructions/i_load.c                      \
	corewar/instructions/i_operations.c                \
	corewar/instructions/exec_instructions.c           \
	corewar/instructions/replace_indirects.c           \
	corewar/instructions/i_store.c                     \
	corewar/glob.c                                     \
	corewar/cor_string_manip/arena_cor.c               \
	corewar/cor_string_manip/cor_str.c                 \
	corewar/globals.c                                  \
	corewar/corewar.c                                  \
	src/main_game/noa.c                                \
	src/main_game/quentin.c

OBJ = $(SRC:.c=.o)

NAME = gcore

CFLAGS = -Wall -Wextra -I ./include/ -I lib/my/include/ -I include/corewar_include -g

LDFLAGS += -L lib/my/ -lmy -lcsfml-graphics -lcsfml-window \
	-lcsfml-system -lcsfml-audio -lm

all: $(NAME)

$(NAME):   $(OBJ)
	make -s -C lib/my/
	gcc -o $(NAME) $(FLAGS) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)
	make -s -C lib/my clean

fclean:    clean
	rm -f $(NAME)
	make -s -C lib/my fclean

re:        fclean all
