# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sganon <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/23 12:32:31 by sganon            #+#    #+#              #
#    Updated: 2016/04/20 15:20:36 by sganon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	wolf3d

SRC =	main.c \
		parsing.c \
		key_events.c \
		init.c \
		ray_cast.c \
		wall_bitmap.c \
		floor_n_ceil_cast.c \
		minimap.c \
		check.c \

SRC_LIST =	$(addprefix srcs/, $(SRC))

O_FILES = $(SRC:.c=.o)

O_LIST = $(addprefix objs/, $(O_FILES))

CC = gcc

CC_FLAGS = -Wall -Werror -Wextra -Ofast

LIBFT_FLAG = -L./libft -lft

MLX_FLAG = -L./mlx -lmlx -framework AppKit -framework OpenGL 

INC_FLAG = -I./includes

all : $(NAME)

$(NAME): 
		@make -C libft/ fclean
		@make -C mlx/ clean
		@make -C libft/
		@make -C mlx/ libmlx.a
		@echo "Libft and mlx compiled."
		@$(CC) $(CC_FLAGS) -c $(SRC_LIST) $(INC_FLAG)
		@echo "Objects compiled."
		@rm -rf objs/
		@mkdir objs/
		@mv $(O_FILES) ./objs/
		@$(CC) $(CC_FLAGS) -o $(NAME) $(O_LIST) $(LIBFT_FLAG) $(MLX_FLAG) -lm $(INC_FLAG)
		@echo "Wolf3d compiled."

clean:
		@rm -rf objs/
		@make -C libft/ fclean
		@make -C mlx/ clean
		@echo "Objects and libraries cleaned."

fclean : clean
		@rm -f $(NAME)
		@echo "Wolf3d cleaned."

re : fclean all

.PHONY : all clean fclean re
