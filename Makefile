# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpilotto <lpilotto@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/25 12:44:37 by lpilotto          #+#    #+#              #
#    Updated: 2016/06/01 16:21:36 by lpilotto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OUT=LINUX
#OUT=MAC
NAME=rtv1
SRCFOLDER=src/
SRCFILES=expose_hook.c \
		find_dist.c \
		init_env.c \
		init_img.c \
		loop_hook.c \
		main.c \
		norm_vect.c \
		parse_camera.c \
		parse_cone.c \
		parse_cylinder.c \
		parse_file.c \
		parse_helper.c \
		parse_light.c \
		parse_plane.c \
		parse_scene.c \
		parse_sphere.c \
		program.c \
		render_scene.c \
		return_print.c \
		set_img_pixel.c \
		set_mlx_hooks.c \
		solve_quadratic.c
OBJFOLDER=obj/
OBJ=$(addprefix $(OBJFOLDER),$(subst .c,.o,$(SRCFILES)))
SRC=$(addprefix $(SRCFOLDER),$(SRCFILES))
ifeq ($(OUT),MAC)
  LIBXFOLDER=./minilibx_macos
  LIBX=$(LIBXFOLDER)/libmlx.a
else
  LIBXFOLDER=./minilibx
  LIBX=$(LIBXFOLDER)/libmlx_Linux.a
endif
LIBFTFOLDER=./libft
LIBFT=$(LIBFTFOLDER)/libft.a
LIBMTXFOLDER=./libmtx
LIBMTX=$(LIBMTXFOLDER)/libmtx.a
EFLAGS=-Wall -Werror -Wextra -g
IFLAGS=-I$(LIBFTFOLDER) -I$(LIBMTXFOLDER)/include -I./include -I$(LIBXFOLDER)
ifeq ($(OUT),MAC)
  LFLAGS=-L$(LIBXFOLDER) -lmlx -framework OpenGL -framework AppKit -L$(LIBFTFOLDER) -lft -lmtx
else
  LFLAGS=-L$(LIBXFOLDER) -lmlx_Linux -lXext -lX11 -L$(LIBFTFOLDER) -lft -lmtx -lm
endif
CFLAGS=-D $(OUT)

.PHONY: all clean fclean re

$(NAME): $(LIBFT) $(LIBMTX) $(LIBX) $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LFLAGS)

all: $(NAME)

$(OBJFOLDER)%.o: $(SRCFOLDER)%.c
	if ! [ -d "$(OBJFOLDER)" ]; then mkdir $(OBJFOLDER); fi
	gcc $(CFLAGS) -c $< $(EFLAGS) $(IFLAGS) -o $@

$(LIBX):
	make -C $(LIBXFOLDER) all

$(LIBFT):
	make -C $(LIBFTFOLDER) all

$(LIBMTX):
	make -C $(LIBMTXFOLDER) all

clean:
	rm -rf $(OBJFOLDER)
	make -C $(LIBFTFOLDER) clean
	make -C $(LIBMTXFOLDER) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTFOLDER) fclean
	make -C $(LIBMTXFOLDER) fclean
	make -C $(LIBXFOLDER) clean

re: fclean all
