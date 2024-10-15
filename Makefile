# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/06 15:41:57 by chrrodri          #+#    #+#              #
#    Updated: 2024/10/06 15:42:11 by chrrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = pipex

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra

# Directories
SRC_DIR = src
INC_DIR = include
LIBFT_DIR = libft

# Paths and Dependencies
HEADER = $(INC_DIR)/pipex.h
LIBFT_A = $(LIBFT_DIR)/libft.a
LIBFT_H = $(INC_DIR)/libft.h
LIBFT_MAKEFILE = $(LIBFT_DIR)/Makefile

# Source and Object Files
# If pipex.c is in the root folder or src folder, adjust accordingly
SRC = $(SRC_DIR)/pipex.c $(SRC_DIR)/error_handle.c $(SRC_DIR)/open_files.c \
$(SRC_DIR)/create_pipe.c $(SRC_DIR)/get_cmd_path.c $(SRC_DIR)/exec_cmd.c \
$(SRC_DIR)/handle_fork.c $(SRC_DIR)/free_2d_array.c
OBJ = $(SRC:.c=.o)

# All rule: Compile everything
all: $(NAME)

# Build pipex executable and link with libft
$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) -I$(INC_DIR) -o $(NAME)

# Rule to build libft
$(LIBFT_A):
	make -C $(LIBFT_DIR)

# Clean object files
clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

# Clean object files and pipex executable
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
