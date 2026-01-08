# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skuor <skuor@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 16:18:45 by skuor             #+#    #+#              #
#    Updated: 2026/01/08 16:14:46 by skuor            ###   ########.fr        #
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

LIBFT_DIR = ./libft/

SRC_FILES = init.c main.c

UTILS_FILES = utils.c free.c utils_parsing.c error_msg.c

PARSING_FILES = parsing_header.c parsing_color.c parsing_map.c \
				parsing_file.c


OBJ = 	$(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o)) \
		$(addprefix $(OBJ_DIR), $(UTILS_FILES:.c=.o)) \
		$(addprefix $(OBJ_DIR), $(PARSING_FILES:.c=.o)) \

INC_H = -I $(INC_DIR) -I $(LIBFT_DIR)/includes/

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

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)$(NAME) object directory cleaned!$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR) --no-print-directory
	@echo "$(CYAN)$(NAME) executables and objects removed succesfully!$(DEFAULT)"
	@echo "$(MAGENTA)libft executables and objects removed succesfully!$(DEFAULT)"

re: fclean clean all

.PHONY: all clean fclean re
	