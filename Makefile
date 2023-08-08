# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diegofranciscolunalopez <diegofrancisco    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 13:29:11 by dluna-lo          #+#    #+#              #
#    Updated: 2023/08/08 12:55:48 by diegofranci      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program
NAME = cub3D
S_DIR	=	src
S_OBJ	=	bin

SUBDIRS		= game \
						parsing \
						raycasting \
						utils

SRCS = src/main.c src/parsing/ft_check_file.c src/parsing/save_data.c \
				src/utils/Error.c src/utils/str_1.c src/utils/str_2.c src/game/game.c \
				src/raycasting/raycasting.c src/game/control.c src/game/ft_creat_frams.c \
				src/game/color.c src/game/utils.c src/parsing/img_color.c src/parsing/check_file_color.c \
				src/parsing/save.c src/parsing/save_2.c src/parsing/get_map_heigth.c \
				src/parsing/utils.c src/raycasting/utils.c

OBJS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(S_OBJ)/, $(dir)))

OBJS		= $(subst $(S_DIR), $(S_OBJ), $(SRCS:.c=.o))


CC = gcc
CFLAGS =  -g -Wall -Wextra -Werror
# CFLAGS =  -g
RM = rm -fr
LIBFT = ./libs/libft/libft.a
#  LIB_MLX  = -framework Cocoa -framework OpenGL -framework IOKit libs/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
LIB_MLX  = -framework Cocoa -framework OpenGL -framework IOKit libs/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/opt/glfw/lib/"

$(S_OBJ)/%.o:$(S_DIR)/%.c
	@mkdir -p $(S_OBJ) $(OBJS_DIRS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(MAKE) all -C ./libs/libft
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LIB_MLX)
# @$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

$(S_OBJ):
	@mkdir -p $(S_OBJ)

all: $(NAME)

clean:
	@$(RM) $(OFIX) $(S_OBJ)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C ./libs/libft

re: fclean all

.PHONY: all clean fclean re
