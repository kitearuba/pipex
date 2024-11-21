# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 21:23:07 by chrrodri          #+#    #+#              #
#    Updated: 2024/11/21 21:23:16 by chrrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = pipex

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra

# Directories
SRC_DIR := src
BONUS_SRC_DIR := src_bonus
INC_DIR := include
LIBFT_DIR := libft

# Paths and Dependencies
MAKEFILE = Makefile
HEADER = $(INC_DIR)/pipex.h
LIBFT_A = $(LIBFT_DIR)/libft.a
LIBFT_H = $(LIBFT_DIR)/$(INC_DIR)/libft.h
LIBFT_MAKEFILE = $(LIBFT_DIR)/Makefile
DEPS := $(HEADER) $(MAKEFILE)

# Source and Object Files
SRC := $(SRC_DIR)/core/pipex.c \
       $(SRC_DIR)/error/error_handle.c $(SRC_DIR)/error/fatal_error.c \
       $(SRC_DIR)/error/free_on_error.c \
       $(SRC_DIR)/file/open_files.c $(SRC_DIR)/file/create_pipe.c \
       $(SRC_DIR)/cmd/get_cmd_path.c $(SRC_DIR)/cmd/get_path_dirs.c \
       $(SRC_DIR)/cmd/exec_cmd.c $(SRC_DIR)/cmd/handle_fork.c \
       $(SRC_DIR)/utils/free_2d_array.c $(SRC_DIR)/utils/free_pipex.c \
       $(SRC_DIR)/utils/init_pipex.c $(SRC_DIR)/utils/cleanup_and_handle.c


# Source and Object Files for Bonus Part
SRC_BONUS := 	$(BONUS_SRC_DIR)/pipex_bonus.c $(BONUS_SRC_DIR)/error_handle_bonus.c \
		$(BONUS_SRC_DIR)/open_files_bonus.c $(BONUS_SRC_DIR)/create_pipe_bonus.c \
		$(BONUS_SRC_DIR)/get_cmd_path_bonus.c $(BONUS_SRC_DIR)/exec_cmd_bonus.c \
		$(BONUS_SRC_DIR)/handle_fork_bonus.c $(BONUS_SRC_DIR)/free_2d_array_bonus.c

# Object Files
OBJ := $(SRC:.c=.o)
OBJ_BONUS := $(SRC_BONUS:.c=.o)

LIBFT_SRCS := $(LIBFT_DIR)/$(SRC_DIR)/ft_isalpha.c $(LIBFT_DIR)/$(SRC_DIR)/ft_isdigit.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_isalnum.c $(LIBFT_DIR)/$(SRC_DIR)/ft_isascii.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_isprint.c $(LIBFT_DIR)/$(SRC_DIR)/ft_strlen.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_memset.c $(LIBFT_DIR)/$(SRC_DIR)/ft_bzero.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_memcpy.c $(LIBFT_DIR)/$(SRC_DIR)/ft_memmove.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_strlcpy.c $(LIBFT_DIR)/$(SRC_DIR)/ft_strlcat.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_toupper.c $(LIBFT_DIR)/$(SRC_DIR)/ft_tolower.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_strchr.c $(LIBFT_DIR)/$(SRC_DIR)/ft_strrchr.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_strncmp.c $(LIBFT_DIR)/$(SRC_DIR)/ft_memchr.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_memcmp.c $(LIBFT_DIR)/$(SRC_DIR)/ft_strnstr.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_atoi.c $(LIBFT_DIR)/$(SRC_DIR)/ft_calloc.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_strdup.c $(LIBFT_DIR)/$(SRC_DIR)/ft_substr.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_strjoin.c $(LIBFT_DIR)/$(SRC_DIR)/ft_strtrim.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_split.c $(LIBFT_DIR)/$(SRC_DIR)/ft_itoa.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_strmapi.c $(LIBFT_DIR)/$(SRC_DIR)/ft_striteri.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_putchar_fd.c $(LIBFT_DIR)/$(SRC_DIR)/ft_putstr_fd.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_putendl_fd.c $(LIBFT_DIR)/$(SRC_DIR)/ft_putnbr_fd.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_lstnew_bonus.c $(LIBFT_DIR)/$(SRC_DIR)/ft_lstadd_front_bonus.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_lstsize_bonus.c $(LIBFT_DIR)/$(SRC_DIR)/ft_lstlast_bonus.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_lstadd_back_bonus.c $(LIBFT_DIR)/$(SRC_DIR)/ft_lstdelone_bonus.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_lstclear_bonus.c $(LIBFT_DIR)/$(SRC_DIR)/ft_lstiter_bonus.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_lstmap_bonus.c $(LIBFT_DIR)/$(SRC_DIR)/ft_printf.c \
             $(LIBFT_DIR)/$(SRC_DIR)/print_format.c $(LIBFT_DIR)/$(SRC_DIR)/ft_putunbr.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_puthex.c $(LIBFT_DIR)/$(SRC_DIR)/handle_char.c \
             $(LIBFT_DIR)/$(SRC_DIR)/handle_string.c $(LIBFT_DIR)/$(SRC_DIR)/handle_pointer.c \
             $(LIBFT_DIR)/$(SRC_DIR)/handle_int.c $(LIBFT_DIR)/$(SRC_DIR)/handle_uint.c \
             $(LIBFT_DIR)/$(SRC_DIR)/handle_hex.c $(LIBFT_DIR)/$(SRC_DIR)/handle_percent.c \
             $(LIBFT_DIR)/$(SRC_DIR)/utils.c $(LIBFT_DIR)/$(SRC_DIR)/get_next_line.c \
             $(LIBFT_DIR)/$(SRC_DIR)/get_next_line_bonus.c $(LIBFT_DIR)/$(SRC_DIR)/ft_strappend.c

LIBFT_OBJS := $(LIBFT_SRCS:.c=.o)

# All rule: Compile everything
all: $(NAME)

# Build pipex executable and link with libft
$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) -I$(INC_DIR) -o $(NAME)

# Rule to rebuild libft.a if libft.h or any libft source files change
$(LIBFT_A): $(LIBFT_MAKEFILE) $(LIBFT_SRCS) $(LIBFT_H)
	$(MAKE) -C $(LIBFT_DIR)

# Pattern rule for compiling object files from source files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Pattern rule for compiling bonus object files from source files
$(BONUS_SRC_DIR)/%.o: $(BONUS_SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Bonus Rule
bonus: $(OBJ_BONUS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT_A) -I$(INC_DIR) -o $(NAME)_bonus

# Clean object files (including bonus objects)
clean:
	rm -f $(OBJ) $(OBJ_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) clean

# Full clean including libft.a and pipex executable
fclean: clean
	rm -f $(NAME) $(NAME)_bonus
	rm -f $(LIBFT_A)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re bonus
