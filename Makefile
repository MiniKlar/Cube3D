NAME				= cube3D

CC					= cc
RM					= rm -f
CLONE				= git clone --depth=1

SRC_DIR				= src
OBJ_DIR				= objet

MLX_INCLUDES		= -I $(MLX) -I $(LIB_C)
CFLAGS				= -Wall -g -Wextra -Werror $(MLX_INCLUDES)
CLINKS				= -ldl -lglfw -pthread -lm

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
						config_validity/correct_file.c \
						config_validity/parse_config.c \
						config_validity/validate_config.c \
						map_validity/helpers_fullfill.c \
						map_validity/helpers_grid.c \
						map_validity/helpers_player_char.c \
						map_validity/helpers_store_map.c \
						map_validity/parse_map.c \

SRC					= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ					= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

bonus: $(NAME)

$(NAME): $(MLX) $(LIBMLX) $(LIB_C) $(LIB_C_A) $(OBJ)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ) $(LIB_C_A) -o $(NAME) $(LIBMLX) $(CLINKS)

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

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIB_C_A)
	$(RM) $(LIBMLX)

clear: fclean
	$(RM) -rf $(MLX)
	$(RM) -rf $(LIB_C)

re: fclean all

.PHONY: all bonus clear clean fclean re