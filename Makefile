# NAME = cub3d
# CC = cc
# CFLAGS = -Wall -Wextra -Werror -MMD -MP
# INCS = -I.
# MLX_DIR = minilibx-linux
# MLX_INC = -I$(MLX_DIR)
# MLX_LIB = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# SRC_DIR = srcs
# OBJ_DIR = obj

# SRCS = \
# main.c \
# srcs/raycasting/mlx_wrap.c \
# srcs/raycasting/render.c \
# srcs/raycasting/player.c \
# srcs/raycasting/textures.c \
# srcs/raycasting/raycast.c \
# srcs/raycasting/draw.c \
# srcs/parsing/check_args_and_init.c \
# srcs/parsing/check_maps_file.c \
# srcs/parsing/create_map.c \
# srcs/parsing/flood_fill.c \
# srcs/parsing/parse_color.c \
# srcs/parsing/parse_map.c \
# srcs/parsing/parse_texture.c \
# srcs/parsing/free.c

# OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
# DEPS = $(OBJS:.o=.d)

# all: $(NAME)

# $(NAME): $(OBJS)
# 	$(MAKE) -C $(MLX_DIR)
# 	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) -o $@

# $(OBJ_DIR)/%.o: %.c
# 	mkdir -p $(dir $@)
# 	$(CC) $(CFLAGS) $(INCS) $(MLX_INC) -c $< -o $@

# clean:
# 	rm -rf $(OBJ_DIR)
# 	$(MAKE) -C $(MLX_DIR) clean || true

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# .PHONY: all clean fclean re
# -include $(DEPS)

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I.

# Dossiers
LIBFT_DIR = libft
SRC_DIR = srcs
OBJ_DIR = obj
MLX_DIR = minilibx-linux

# Sources
SRCS = \
main.c \
parsing/check_args_and_init.c \
parsing/check_maps_file.c \
parsing/create_map.c \
parsing/flood_fill.c \
parsing/parse_color.c \
parsing/parse_map.c \
parsing/parse_texture.c \
raycasting/draw.c \
raycasting/mlx_wrap.c \
raycasting/player.c \
raycasting/raycast.c \
raycasting/render.c \
raycasting/minimap.c \
raycasting/textures.c \
parsing/free.c \

# Paths complets
SRCS_FULL = $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Librairies
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

# Flags liens MLX
MLXFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

# Compilation librairies
$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

# Linkage final
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -L$(LIBFT_DIR) -lft -o $@

# Construction des fichiers obj dans obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -c $< -o $@

# Pour main.c à la racine
$(OBJ_DIR)/main.o: main.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -c $< -o $@

# Dossier obj
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
