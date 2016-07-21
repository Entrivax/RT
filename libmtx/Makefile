# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpilotto <lpilotto@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/24 13:02:11 by lpilotto          #+#    #+#              #
#    Updated: 2016/06/13 14:33:26 by lpilotto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libmtx.a
INPUT=mtx_init.c \
		mtx_trans.c \
		mtx_dotproduct.c \
		mtx_dot.c \
		mtx_add.c \
		mtx_sub.c \
		mtx_negate.c \
		mtx_mult.c \
		mtx_product.c \
		mtx_invert.c
OBJ=$(subst .c,.o,$(INPUT))
FLAGS=-Wall -Werror -Wextra -Iinclude -g

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) 
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	gcc -c $(FLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
