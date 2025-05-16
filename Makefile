# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 21:23:07 by chrrodri          #+#    #+#              #
#    Updated: 2024/12/22 15:55:44 by chrrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project
NAME = pipex
NAME_BONUS = pipex_bonus

# Directories
MANDATORY_DIR = src
BONUS_DIR = bonus_src
LIBFT_DIR = libft
INCLUDES = -Iinclude -I$(LIBFT_DIR)/include

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Sources
MANDATORY_SRCS = \
	$(MANDATORY_DIR)/core/pipex.c \
	$(MANDATORY_DIR)/cmd/exec_cmd.c \
	$(MANDATORY_DIR)/cmd/get_cmd_path.c \
	$(MANDATORY_DIR)/cmd/get_path.c \
	$(MANDATORY_DIR)/cmd/handle_fork.c \
	$(MANDATORY_DIR)/file/create_pipe.c \
	$(MANDATORY_DIR)/file/open_files.c \
	$(MANDATORY_DIR)/utils/init_pipex.c \
	$(MANDATORY_DIR)/utils/free_pipex.c \
	$(MANDATORY_DIR)/utils/free_2d_array.c \
	$(MANDATORY_DIR)/error/free_on_error.c

BONUS_SRCS = \
	$(BONUS_DIR)/core/pipex_bonus.c \
	$(BONUS_DIR)/cmd/exec_cmd_bonus.c \
	$(BONUS_DIR)/cmd/get_cmd_path.c \
	$(BONUS_DIR)/cmd/get_path.c \
	$(BONUS_DIR)/cmd/handle_fork_bonus.c \
	$(BONUS_DIR)/file/create_pipe_bonus.c \
	$(BONUS_DIR)/file/open_files_bonus.c \
	$(BONUS_DIR)/utils/init_pipex_bonus.c \
	$(BONUS_DIR)/utils/free_pipex.c \
	$(BONUS_DIR)/utils/free_2d_array.c \
	$(BONUS_DIR)/error/free_on_error.c

# Objects
MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# Rules
all: $(NAME)

$(NAME): $(MANDATORY_OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) $(LIBFT) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(BONUS_OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME_BONUS)

clean:
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
