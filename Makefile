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


NAME = libftpipex.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra

AR = ar rcs

# Directories
SRC_DIR = src
INC_DIR = include
LIBFT_DIR = libft

# Paths and Dependencies
MAKEFILE = makefile
HEADER = $(INC_DIR)/pipex.h
LIBFT_A = libft.a
LIBFT_H = $(LIBFT_DIR)/libft.h
LIBFT_MAKEFILE = $(LIBFT_DIR)/$(MAKEFILE)
INC = -I$(INC_DIR) -I$(LIBFT_DIR)
DEP = $(HEADER) $(MAKEFILE)

SRC =

OBJ = $(SRC:.c=.o)

LIBFT_SRC =

LIBFT_OBJ = $(LIBFT_SRC:.c=.o)

all: $(NAME)

# Rule to create the archive libftpipex.a from object files.
$(NAME): $(OBJ) $(LIBFT_DIR)/$(LIBFT_A)
	cp
