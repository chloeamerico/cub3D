NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I.

# dossiers
LIBFT_DIR 	=	libft/
SRCS_DIR	=	srcs/
OBJ_DIR		=	obj/
MLX_DIR		=	minilibx-linux/

SRCS =  main.c \
	parsing/check_args_and_init.c \
	parsing/check_maps_file.c \
	parsing/create_map.c \
	parsing/parse_texture.c \
	free.c \


HEADER = cub3D.h

SRCS_CUB3D 	=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJS_CUB3D 	= 	$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

# ajout de la libft
LIBFT = $(LIBFT_DIR)/libft.a

# ajout de MLX
MLX 	= 	$(MLX_DIR)/libmlx.a
MLXFLAGS = 	-L$(MLX_DIR) -lmlx -lXext -lX11

# compilation
all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

$(NAME): $(LIBFT) $(MLX) $(OBJ_DIR) $(OBJS_CUB3D)
	$(CC) $(CFLAGS) $(OBJS_CUB3D) $(MLXFLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re