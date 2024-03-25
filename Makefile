NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a
LIBFT_DIR = libft

MLX_DIR = ./MLX42
MLX_BUILD_DIR = $(MLX_DIR)/build
MLX_FLAGS = -L$(MLX_BUILD_DIR) -lmlx42 -Iinclude -ldl -lglfw -pthread -lm
MLX_LIB = $(MLX_BUILD_DIR)/libmlx42.a

INCLUDES = -I./inc -I./libft/inc -I$(MLX_DIR)

SRC_DIR = src
BONUS_SRC_DIR = src_bonus
OBJ_DIR = obj
BONUS_OBJ_DIR = obj_bonus

SRC_FILES = main \
	utils/list utils/color utils/free \
	checker/data checker/map checker/map_utils checker/rgb_data checker/fields checker/spaces \
	init_and_draw/game init_and_draw/init_map \
	hook/directions hook/mlx_hook hook/moves hook/rotate \
	raycast/raycast raycast/raycast_utils raycast/texture raycast/wall raycast/wall_utils \
	parsing/data parsing/map parsing/player parsing/texture_color \

BONUS_SRC_FILES = main_bonus \
	utils_bonus/list_bonus utils_bonus/color_bonus utils_bonus/free_bonus \
	checker_bonus/data_bonus checker_bonus/map_bonus checker_bonus/map_utils_bonus \
	checker_bonus/rgb_data_bonus checker_bonus/fields_bonus checker_bonus/spaces_bonus \
	init_and_draw_bonus/game_bonus init_and_draw_bonus/draw_map_bonus init_and_draw_bonus/init_map_bonus \
	hook_bonus/directions_bonus hook_bonus/map_bonus hook_bonus/mlx_hook_bonus hook_bonus/moves_bonus \
	hook_bonus/rotate_bonus hook_bonus/shoot_animation_bonus hook_bonus/shoot_break_wall_bonus \
	raycast_bonus/raycast_bonus raycast_bonus/raycast_utils_bonus raycast_bonus/texture_bonus \
	raycast_bonus/wall_bonus raycast_bonus/wall_utils_bonus \
	parsing_bonus/data_bonus parsing_bonus/map_bonus parsing_bonus/player_bonus parsing_bonus/texture_color_bonus \

SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

BONUS_SRC = $(addprefix $(BONUS_SRC_DIR)/, $(addsuffix .c, $(BONUS_SRC_FILES)))
BONUS_OBJ = $(addprefix $(BONUS_OBJ_DIR)/, $(addsuffix .o, $(BONUS_SRC_FILES)))

RED = \033[0;31m
GREEN = \033[0;32m
NO_COLOR = \033[0m

all: mlx42 $(NAME)

mlx42:
	@echo "$(GREEN)Compiling MLX42...$(NO_COLOR)"
	@mkdir -p $(MLX_BUILD_DIR)
	@cmake -B $(MLX_BUILD_DIR) -S $(MLX_DIR) && cmake --build $(MLX_BUILD_DIR) -j4
	@if [ ! -f $(MLX_LIB) ]; then \
		echo "$(RED)Error: MLX42 library not found!$(NO_COLOR)"; \
		exit 1; \
	fi
	@echo "$(GREEN)MLX42 compiled$(NO_COLOR)"

$(NAME): $(OBJ) $(MLX_LIB) inc/cub3D.h
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)Compiling $(NAME)...$(NO_COLOR)"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBFT) $(MLX_FLAGS)
	@echo "$(GREEN)$(NAME) compiled$(NO_COLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c inc/cub3D.h
	@echo "$(GREEN)Generating $(NAME) objects...$(NO_COLOR)"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)$(NAME) objects generated$(NO_COLOR)"

$(NAME)_bonus: $(BONUS_OBJ) $(MLX_LIB) inc/cub3D.h
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)Compiling $(NAME) bonus...$(NO_COLOR)"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME)_bonus $(BONUS_OBJ) $(LIBFT) $(MLX_FLAGS)
	@echo "$(GREEN)$(NAME) bonus compiled$(NO_COLOR)"

bonus: mlx42 $(NAME)_bonus

$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c inc/cub3D.h
	@echo "$(GREEN)Generating $(NAME) bonus objects...$(NO_COLOR)"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
clean:
	@make clean -C $(LIBFT_DIR)
	@echo "$(RED)Cleaning $(NAME) objects...$(NO_COLOR)"
	@rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@rm -rf $(MLX_BUILD_DIR) 

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)Deleting executable $(NAME)...$(NO_COLOR)"
	@rm -f $(NAME) $(NAME)_bonus
	@rm -f $(MLX_LIB)

re: fclean all

.PHONY: all clean fclean re bonus mlx42
