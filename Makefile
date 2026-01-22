# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agouin <agouin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 16:18:45 by skuor             #+#    #+#              #
#    Updated: 2026/01/22 16:44:08 by agouin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc 
MAKE = make
CFLAGS = -Wall -Wextra -Werror -g3
SRC_DIR = ./srcs/
OBJ_DIR = ./objects/
INC_DIR = ./includes/
UTILS_DIR = $(SRC_DIR)utils/
PARSING_DIR = $(SRC_DIR)parsing/
PLAYER_DIR = $(SRC_DIR)player/
RAYCAST_DIR = $(SRC_DIR)raycast/
INIT_DIR = $(SRC_DIR)initialisation/

LIBFT_DIR = ./libft/

SRC_FILES = main.c 

UTILS_FILES = utils.c utils_parsing.c utils_map.c utils_player.c \
			  free.c error_msg.c 

PARSING_FILES = parsing_texture.c parsing_color.c parsing_map.c \
				parsing_file.c map_checks.c map_grid.c map_floodfill.c check_args.c 

PLAYER_FILES = player_pos.c player_movement.c handle_input.c

RAYCAST_FILES = raycast.c mini_map.c print_wall.c

INIT_FILES = init.c init2.c init3.c


OBJ = 	$(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o)) \
		$(addprefix $(OBJ_DIR), $(UTILS_FILES:.c=.o)) \
		$(addprefix $(OBJ_DIR), $(PARSING_FILES:.c=.o)) \
		$(addprefix $(OBJ_DIR), $(PLAYER_FILES:.c=.o)) \
		$(addprefix $(OBJ_DIR), $(RAYCAST_FILES:.c=.o)) \
		$(addprefix $(OBJ_DIR), $(INIT_FILES:.c=.o)) \

INC_H = -I $(INC_DIR) -I $(LIBFT_DIR)/includes/

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -L/usr/lib/X11 -lXext -lX11
MLX_OBJ_DIR = $(MLX_DIR)/obj/

DEFAULT = \033[0m
DEF_COLOR = \033[0;90m
WHITE = \033[1;37m
GREEN = \033[0;92m
YELLOW = \033[0;93m
CYAN = \033[0;96m
MAGENTA = \033[0;95m

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@echo "$(MAGENTA)libft compiled!$(DEFAULT)"
	@echo "$(GREEN)$(NAME) compiled!$(DEFAULT)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@$(MAKE) -C $(MLX_DIR) --no-print-directory
	@$(CC) $(CFLAGS) $(INC_H) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC_H) -c -o $@ $<

$(OBJ_DIR)%.o: $(UTILS_DIR)%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC_H) -c -o $@ $<

$(OBJ_DIR)%.o: $(PARSING_DIR)%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC_H) -c -o $@ $<

$(OBJ_DIR)%.o: $(PLAYER_DIR)%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC_H) -c -o $@ $<

$(OBJ_DIR)%.o: $(RAYCAST_DIR)%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC_H) -c -o $@ $<

$(OBJ_DIR)%.o: $(INIT_DIR)%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC_H) -c -o $@ $<

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(MLX_OBJ_DIR)
	@echo "$(GREEN)$(NAME) object directory cleaned!$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR) --no-print-directory
	@$(MAKE) clean -C $(MLX_DIR) --no-print-directory
	@echo "$(CYAN)$(NAME) executables and objects removed succesfully!$(DEFAULT)"
	@echo "$(MAGENTA)libft executables and objects removed succesfully!$(DEFAULT)"

re: fclean clean all

.PHONY: all clean fclean re