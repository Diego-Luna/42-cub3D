# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 13:29:11 by dluna-lo          #+#    #+#              #
#    Updated: 2023/07/20 19:04:38 by dluna-lo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Program
NAME = cub3D

CC		=	gcc
CFLAGS	=	-g -Wall -Werror -Wextra -I. -I./$(INCDIR)
RM		=	rm -f
RM_F		=	rm -rf

# Includes are all .h files
INCDIR	=	libs/
INC		=	libs/cub.h
MLX		= ${HOME}/.brew/lib/
LIB_MLX  = -framework Cocoa -framework OpenGL -framework IOKit libs/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
#-framework Cocoa -framework OpenGL -framework IOKit

# Sources are all .c files
SRCDIR	=	src/
SRCS =	src/main.c \
				src/utils/Error.c \
				src/utils/str_1.c \
				src/parsing/ft_check_file.c src/parsing/save_data.c

# Objects are all .o files
OBJDIR	=	bin/
OBJS	=	$(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))

# libf
LIBFT = libft.a
D_LIBFT = libs/libft/

# ////////////////// TARGETS

# all: $(NAME)
all: do_libft $(NAME)

# Generates output file
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(D_LIBFT)$(LIBFT)
# $(CC) $(CFLAGS) -o $@ $(OBJS) ${LIB_MLX} $(D_LIBFT)$(LIBFT)

# Compiles sources into objects
$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c $(INC) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Creates directory for binaries
$(OBJDIR):
	mkdir -p $@

# Removes objects
clean:
	@$(RM_F) $(OBJDIR)
	@$(MAKE) --no-print-directory -C $(D_LIBFT) clean

# Removes objects and executables
fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) --no-print-directory -C $(D_LIBFT) fclean

# Removes objects and executables and remakes
re: fclean all

# libf
do_libft:
	@$(MAKE) -C $(D_LIBFT)
# libf
.PHONY:		all clean fclean re header
