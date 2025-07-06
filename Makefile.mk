# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/06 10:31:36 by odudniak          #+#    #+#              #
#    Updated: 2025/07/06 10:31:39 by odudniak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC	=%%%%

UNAME = $(shell uname)
CC	= gcc
ifeq ($(UNAME),FreeBSD)
	CC = clang
endif

NAME		= libmlx.a
NAME_UNAME	= libmlx_$(UNAME).a

SRC = ./mlx_clear_window.c \
	./mlx_destroy_display.c \
	./mlx_destroy_image.c \
	./mlx_destroy_window.c \
	./mlx_expose_hook.c \
	./mlx_ext_randr.c \
	./mlx_flush_event.c \
	./mlx_get_color_value.c \
	./mlx_get_data_addr.c \
	./mlx_hook.c \
	./mlx_int_do_nothing.c \
	./mlx_int_get_visual.c \
	./mlx_int_param_event.c \
	./mlx_int_set_win_event_mask.c \
	./mlx_int_str_to_wordtab.c \
	./mlx_int_wait_first_expose.c \
	./mlx_key_hook.c \
	./mlx_loop.c \
	./mlx_loop_hook.c \
	./mlx_mouse.c \
	./mlx_mouse_hook.c \
	./mlx_new_image.c \
	./mlx_pixel_put.c \
	./mlx_put_image_to_window.c \
	./mlx_rgb.c \
	./mlx_screen_size.c \
	./mlx_set_font.c \
	./mlx_string_put.c \
	./mlx_xpm.c \
	./src/init/_mlx_rgb_convert.c \
	./src/init/mlx_init.c \
	./src/new_window/mlx_new_window.c


OBJ_DIR = obj
OBJ	= $(SRC:%.c=$(OBJ_DIR)/%.o)
CFLAGS	= -O3 -I$(INC) -I.

all	: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME)	: $(OBJ)
	ar -r $(NAME) $(OBJ)
	ranlib $(NAME)
	cp $(NAME) $(NAME_UNAME)

check: all
	@test/run_tests.sh

show:
	@printf "NAME  		: $(NAME)\n"
	@printf "NAME_UNAME	: $(NAME_UNAME)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "SRC		:\n	$(SRC)\n"
	@printf "OBJ		:\n	$(OBJ)\n"

clean	:
	rm -rf $(OBJ_DIR)/ $(NAME) $(NAME_UNAME) *~ core *.core

.PHONY: all check show clean
