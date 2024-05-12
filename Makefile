NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a
LIBFT_DIR = libft

MLX_DIR = ./MLX42
MLX_FLAGS = -L$(MLX_DIR) MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm
MLX_LIB = $(MLX_DIR)/build/libmlx42.a

INCLUDES = -I./inc -I./libft/inc -I$(MLX_DIR)

SRC_DIR = src
OBJ_DIR = obj

SRC_FILES = main \
	utils/list utils/color utils/free \
	checker/data checker/map checker/map_utils checker/rgb_data checker/fields checker/spaces \
	 init_and_draw/game  init_and_draw/draw_map init_and_draw/init_map \
	hook/directions hook/map hook/mlx_hook hook/moves hook/rotate hook/shoot_animation hook/shoot_break_wall\
	raycast/raycast raycast/raycast_utils raycast/texture raycast/wall raycast/wall_utils\
	parsing/data parsing/map parsing/player parsing/texture_color \

SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

RED = \033[0;31m
GREEN = \033[0;32m
NO_COLOR = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB) inc/cub3D.h
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)Compiling $(NAME)...$(NO_COLOR)"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBFT) $(MLX_FLAGS) -g
	@echo "$(GREEN)$(NAME) compiled$(NO_COLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c inc/cub3D.h
	@echo "$(GREEN)Generating $(NAME) objects...$(NO_COLOR)"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)$(NAME) objects generated$(NO_COLOR)"


clean:
	@make clean -C $(LIBFT_DIR)
	@echo "$(RED)Cleaning $(NAME) objects...$(NO_COLOR)"
	@rm -rf $(OBJ_DIR)

fclean:
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)Cleaning $(NAME) objects...$(NO_COLOR)"
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Deleting executable $(NAME)...$(NO_COLOR)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
