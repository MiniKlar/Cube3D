NAME				= cube3D

CC					= cc
RM					= rm -f
CLONE				= git clone --depth=1

SRC_DIR				= src
OBJ_DIR				= objet

MLX_INCLUDES		= -I $(MLX) -I $(LIB_C)
CFLAGS				= -Wall -Wextra -Werror $(MLX_INCLUDES)
CLINKS				= -ldl -lglfw -pthread -lm

MLX_GIT_URL			= git@github.com:MiniKlar/MLX42.git
MLX					= MLX42
LIBMLX				= $(MLX)/libmlx42.a

LIB_C_GIT_URL		= git@github.com:MiniKlar/LIB_C.git
LIB_C				= LIB_C
LIB_C_A				= $(LIB_C)/LIB_C.a

SRC_FILES			= main.c \
						parsing.c \

SRC					= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_FILES			= $(notdir $(SRC_FILES:.c=.o))
OBJ					= $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

all: $(NAME)

bonus: $(NAME)

$(NAME): $(MLX) $(LIBMLX) $(LIB_C) $(LIB_C_A) $(OBJ_DIR) $(OBJ)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJ) $(LIB_C_A) -o $(NAME) $(LIBMLX) $(CLINKS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBMLX): $(MLX)
	$(MAKE) -C $(MLX)

$(MLX):
	git clone $(MLX_GIT_URL) $(MLX);
	cmake $(MLX) -B $(MLX)

$(LIB_C):
	git clone $(LIB_C_GIT_URL) $(LIB_C)

$(LIB_C_A): $(LIB_C)
	@echo "Compiling $(LIB_C)..."
	$(MAKE) -C $(LIB_C)

clean:
	$(MAKE) -C $(LIB_C) clean || true
	$(MAKE) -C $(MLX) clean || true
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
