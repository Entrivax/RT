# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpilotto <lpilotto@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/25 12:44:37 by lpilotto          #+#    #+#              #
#    Updated: 2016/09/13 15:41:08 by lpilotto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#OUT=LINUX
OUT=MAC
NAME=rt
SRCFOLDER=src/
SRCFILES=aabb.c \
		add_to_queue.c \
		compute_color.c \
		compute_light.c \
		cone.c \
		cylinder.c \
		destruct_env.c \
		dot_vect.c \
		find_closest.c \
		get_material.c \
		get_normal.c \
		init_camera.c \
		init_env.c \
		init_img.c \
		init_win.c \
		invert_ray.c \
		main.c \
		mouse_hook.c \
		mtx_createrotmtx.c \
		mtx_createscalemtx.c \
		norm_vect.c \
		parse_args.c \
		parse_camera.c \
		parse_cone.c \
		parse_cylinder.c \
		parse_file.c \
		parse_helper.c \
		parse_helper_2.c \
		parse_light.c \
		parse_material.c \
		parse_plane.c \
		parse_scene.c \
		parse_sphere.c \
		phong.c \
		plane.c \
		print_memory.c \
		print_usage.c \
		program.c \
		render_scene.c \
		return_print.c \
		rgb_add.c \
		rgb_clamp.c \
		rgb_div.c \
		rgb_mult.c \
		rgb_new.c \
		save_to_bmp.c \
		sdl_loop.c \
		set_img_pixel.c \
		set_objenv.c \
		set_vector.c \
		solve_quadratic.c \
		sphere.c \
		transform_object.c \
		update_title.c \
		vect_reflect.c
INCFOLDER=./include/
INCFILES=keycodes.h \
		 quadric_shortcuts.h \
		 rt.h
INC=$(addprefix $(INCFOLDER),$(INCFILES))
OBJFOLDER=obj/
OBJ=$(addprefix $(OBJFOLDER),$(subst .c,.o,$(SRCFILES)))
SRC=$(addprefix $(SRCFOLDER),$(SRCFILES))
LIBFTFOLDER=./libft
LIBFT=$(LIBFTFOLDER)/libft.a
LIBBMPFOLDER=./libbmp
LIBBMP=$(LIBBMPFOLDER)/libbmp.a
LIBMTXFOLDER=./libmtx
LIBMTX=$(LIBMTXFOLDER)/libmtx.a
LIBSDLFOLDER=./SDL2-2.0.4
EFLAGS=-Wall -Werror -Wextra -g
IFLAGS=-I$(LIBFTFOLDER) -I$(LIBMTXFOLDER)/include -I$(LIBBMPFOLDER)/include -I$(INCFOLDER)
ifeq ($(OUT),MAC)
  IFLAGS+= -I./SDL2.framework/Headers
  LFLAGS=-L$(LIBFTFOLDER) -lft -L$(LIBMTXFOLDER) -lmtx -L$(LIBBMPFOLDER) -lbmp -lpthread -L./SDL2.framework/Versions/Current -F. -framework SDL2 -framework Cocoa
  EDITLIB=install_name_tool -change @executable_path/../Frameworks/SDL2.framework/SDL2 @executable_path/SDL2.framework/SDL2 $(NAME) && install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 @executable_path/SDL2.framework/SDL2 $(NAME)
else
  PATHSOSDL=-Wl,-R`pwd`/$(LIBSDLFOLDER)/build/.libs
  IFLAGS+= -I$(LIBSDLFOLDER)/include
  LFLAGS=-L$(LIBFTFOLDER) -lft -L$(LIBMTXFOLDER) -lmtx -L$(LIBBMPFOLDER) -lbmp -lm -lpthread $(PATHSOSDL) -L`pwd`/$(LIBSDLFOLDER)/build/.libs -lSDL2
  DYNSDL=libSDL2-2.0.so.0
endif
CFLAGS=-D $(OUT)

.PHONY: all clean fclean re

$(NAME): $(LIBFT) $(LIBMTX) $(LIBBMP) $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LFLAGS)
	$(EDITLIB)

all: $(NAME)

$(OBJFOLDER)%.o: $(SRCFOLDER)%.c $(INC)
	@if ! [ -d "$(OBJFOLDER)" ]; then mkdir $(OBJFOLDER); fi
	gcc $(CFLAGS) -c $< $(EFLAGS) $(IFLAGS) -o $@

$(LIBFT):
	make -C $(LIBFTFOLDER) all

$(LIBMTX):
	make -C $(LIBMTXFOLDER) all

$(LIBBMP):
	make -C $(LIBBMPFOLDER) all

clean:
	rm -rf $(OBJFOLDER)
	make -C $(LIBFTFOLDER) clean
	make -C $(LIBMTXFOLDER) clean
	make -C $(LIBBMPFOLDER) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTFOLDER) fclean
	make -C $(LIBMTXFOLDER) fclean
	make -C $(LIBBMPFOLDER) fclean

re: fclean all
