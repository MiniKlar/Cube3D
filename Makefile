# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/31 19:15:37 by lomont            #+#    #+#              #
#    Updated: 2025/11/07 03:58:55 by lomont           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= cube3D

CC 				= cc
RM				= rm -f
CLONE 			= git clone --depth=1

CFLAGS 			= -Wall -Wextra -Werror -DSHOW_FPS=1
## On macOS with Homebrew GLFW, the library lives in the Homebrew lib dir
## Detect Homebrew prefix (works when brew is installed) and add it to the
## linker search path so -lglfw can be resolved.
BREW_PREFIX		= $(shell brew --prefix 2>/dev/null || echo /opt/homebrew)
CLINKS			= -L$(BREW_PREFIX)/lib -ldl -lglfw -pthread -lm

MLX_GIT_URL		= git@github.com:MiniKlar/MLX42.git
MLX				= MLX42
LIBMLX 			= $(MLX)/libmlx42.a

LIB_C_GIT_URL 	= git@github.com:MiniKlar/LIB_C.git
LIB_C			= LIB_C

SRC 			= ./src/main.c \
					./src/fps.c \
					./src/handle_image.c \
					./src/init.c \
					./src/raycasting.c \

OBJ 			= $(SRC:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(MLX) $(LIBMLX) $(LIB_C) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) ./LIB_C/LIB_C.a -o $(NAME)  $(LIBMLX) $(CLINKS)

$(LIBMLX): $(MLX)
	$(MAKE) -C $(MLX)

$(MLX):
	git clone $(MLX_GIT_URL) $(MLX);
	cmake $(MLX) -B $(MLX)

$(LIB_C):
	git clone $(LIB_C_GIT_URL) $(LIB_C)
	$(MAKE) -C $(LIB_C)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(LIB_C)
	$(RM) -r $(MLX)
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

clear: fclean
	$(RM) -rf $(MLX)

re: fclean all

test:
	g++ test.cpp quickcg.cpp `sdl-config --cflags --libs` -o test

.PHONY:	all bonus clear clean fclean re
