# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/07 15:19:36 by jordan            #+#    #+#              #
#    Updated: 2023/10/24 01:05:07 by jchapell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable Name
ENAME	=	minishell
NAME	=	minishell.a
CFLAGS	=	-g -Wall -Wextra -Werror
AR		=	ar -rsc
FILES	=	main.c parse.c free.c utils.c expander.c start.c signal.c \
			sep_parse.c spacer.c exec/split_cmd.c \
			exec/exec_cmd.c exec/exec_line.c exec/pipe.c exec/heredoc.c \
			exec/write_file.c exec/utils_exec.c exec/exec_cmd_utils.c \
			exec/parse_cmds.c \
			builtins/cd.c builtins/echo.c builtins/env.c builtins/pwd.c \
			builtins/exit.c builtins/export.c builtins/unset.c \
			builtins/hashmap.c quote.c\

# Path for .c , .h and .o Files 
SRC_PATH := ./src/
OBJ_PATH := ./src/OBJ/
LIBFT_PATH := ./inc/libft/

all : $(LIBFT) $(NAME)

# Files to compile
OBJ1 := $(FILES:.c=.o)
OBJ := $(patsubst %,$(OBJ_PATH)%,$(OBJ1))

# Build .o first
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo [CC] $<
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I/Users/${USER}/.brew/opt/readline/include -o $@ -c $<     

# Build final Binary
$(NAME): $(OBJ)
	@make -C $(LIBFT_PATH)
	@echo [INFO] Creating $(Shell uname) Binary Executable [$(NAME)]
	$(AR) $(NAME) $(OBJ) $(LINKFLAGS)
	$(CC) $(CFLAGS) $(NAME) $(LIBFT_PATH)libft.a -L/Users/${USER}/.brew/opt/readline/lib -lreadline -o $(ENAME)

# Clean all the object files and the binary
clean:   
	@echo "[Cleaning]"
	@$(RM) -rfv $(OBJ_PATH)*

fclean: clean
		@$(RM) -rfv $(NAME)
		@$(RM) -rfv $(ENAME)

re: fclean all

san: all
	@make -C $(LIBFT_PATH)
	@echo [INFO] Creating $(Shell uname) Binary Executable [$(NAME)]
	$(AR) $(NAME) $(OBJ) $(LINKFLAGS)
	$(CC) $(CFLAGS) $(NAME) $(LIBFT_PATH)libft.a -lreadline -fsanitize=address -o $(ENAME)

.PHONY : clean fclean re
