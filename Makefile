NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I./inc -I./libft/inc

LIBFT = libft/libft.a
LIBFT_DIR = libft

SRC_DIR = src
OBJ_DIR = obj

SRC_FILES = main \
	utils/list_utils \
	parsing/checker parsing/parse \
	parsing/map_checker parsing/fields_checker \

SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

RED = \033[0;31m
GREEN = \033[0;32m
NO_COLOR = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)Compiling $(NAME)...$(NO_COLOR)"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "$(GREEN)$(NAME) compiled$(NO_COLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
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