# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/31 19:15:37 by lomont            #+#    #+#              #
#    Updated: 2025/11/12 23:44:25 by lomont           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= cube3D

CC					= cc
RM					= rm -f
CLONE				= git clone --depth=1

SRC_DIR				= src
OBJ_DIR				= objet
TEST_OBJ_DIR		= $(OBJ_DIR)/tests

TEST_NAME	= cube3D_tests
TEST_SRC_DIR		= tests
TEST_SRC_FILES	= test_utils.c \
				test_stubs.c
TEST_SRC		= $(addprefix $(TEST_SRC_DIR)/, $(TEST_SRC_FILES))
UNIT_TEST_SRC_FILES	= utils/check_line.c \
					utils/rgba.c \
					map_validity/helpers_player_char.c \
					map_validity/helpers_grid.c \
					map_validity/helpers_store_map.c \
					config_validity/helpers_validate_config.c
UNIT_TEST_SRC	= $(addprefix $(SRC_DIR)/, $(UNIT_TEST_SRC_FILES))
TEST_SRCS		= $(TEST_SRC) $(UNIT_TEST_SRC)
TEST_LDFLAGS	= -lm
MEMCHECK_SCRIPT	= $(TEST_SRC_DIR)/run_memcheck.sh

BREW_PREFIX			= $(shell brew --prefix 2>/dev/null || echo /opt/homebrew)
CLINKS				= -L$(BREW_PREFIX)/lib -ldl -lglfw -pthread -lm

MLX_INCLUDES		= -I $(MLX) -I $(LIB_C)
CFLAGS				= -Wall -g -Wextra -Werror $(MLX_INCLUDES) -I ./includes -g
# CLINKS				= -ldl -lglfw -pthread -lm

MLX_GIT_URL			= git@github.com:MiniKlar/MLX42.git
MLX					= MLX42
LIBMLX				= $(MLX)/libmlx42.a

LIB_C_GIT_URL		= git@github.com:MiniKlar/LIB_C.git
LIB_C				= LIB_C
LIB_C_A				= $(LIB_C)/LIB_C.a

SRC_FILES			= main.c \
						utils/check_line.c \
						utils/error.c \
						utils/init_free.c \
						utils/rgba.c \
						config_validity/helpers_correct_file.c \
						config_validity/helpers_validate_config.c \
						config_validity/parse_config.c \
						map_validity/helpers_fullfill.c \
						map_validity/helpers_grid.c \
						map_validity/helpers_player_char.c \
						map_validity/helpers_store_map.c \
						map_validity/parse_map.c \
						handle_image.c \
						init.c \
						raycasting.c \
						raycasting_calcul.c \
						draw.c \
						key.c \
						fps.c \

SRC					= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ					= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

bonus: $(NAME)

test: $(TEST_NAME)
	@./$(TEST_NAME)

memcheck: $(NAME) $(TEST_NAME)
	@bash $(MEMCHECK_SCRIPT)

$(NAME): $(MLX) $(LIBMLX) $(LIB_C) $(LIB_C_A) $(OBJ)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ) $(LIB_C_A) -o $(NAME) $(LIBMLX) $(CLINKS)

$(TEST_NAME): $(LIB_C_A) $(TEST_SRCS)
	@echo "Building $(TEST_NAME)..."
	@$(CC) $(CFLAGS) -DUNIT_TESTS $(TEST_SRCS) -o $@ $(LIB_C_A) $(TEST_LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "--> Compiled $< with success."

$(LIBMLX): $(MLX)
	@echo "Compiling $(MLX)..."
	@$(MAKE) -C $(MLX)

$(MLX):
	@echo "Cloning $(MLX)..."
	@git clone $(MLX_GIT_URL) $(MLX);
	@cmake $(MLX) -B $(MLX)

$(LIB_C):
	@echo "Cloning $(LIB_C)..."
	@git clone $(LIB_C_GIT_URL) $(LIB_C)

$(LIB_C_A): $(LIB_C)
	@echo "Compiling $(LIB_C)..."
	@$(MAKE) -C $(LIB_C)

clean:
	@echo "Cleaning up $(LIB_C)..."
	@$(MAKE) -C $(LIB_C) clean || true
	@echo "Cleaning up $(MLX)..."
	@$(MAKE) -C $(MLX) clean || true
	$(RM) -r $(OBJ_DIR)
	$(RM) -r $(TEST_OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST_NAME)
	$(RM) $(LIB_C_A)
	$(RM) $(LIBMLX)

clear: fclean
	$(RM) -rf $(MLX)
	$(RM) -rf $(LIB_C)

re: fclean all

.PHONY: all bonus clear clean fclean re test memcheck
