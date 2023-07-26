# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/07 15:19:36 by jordan            #+#    #+#              #
#    Updated: 2023/07/26 11:52:31 by abourgue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable Name
ENAME	=	minishell
NAME	=	minishell.a
CFLAGS	=	-g 
AR		=	ar -rsc
FILES	=	main.c parse.c free.c utils.c\
			exec/utils_exec.c exec/get_cmd.c exec/exec_cmd.c \
			exec/cmd_pipe.c exec/cmd_rdr.c exec/cmd_rdr_d.c \
			builtins/cd.c builtins/echo.c builtins/env.c builtins/pwd.c \
			builtins/exit.c builtins/export.c builtins/unset.c builtins/hashmap.c \

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
	@$(CC) $(CFLAGS) -o $@ -c $<     

# Build final Binary
$(NAME): $(OBJ)
	@echo [INFO] Compliling libft
	@make -C $(LIBFT_PATH)
	@echo [INFO] Creating $(Shell uname) Binary Executable [$(NAME)]
	$(AR) $(NAME) $(OBJ) $(LINKFLAGS)
	$(CC) $(CFLAGS) $(NAME) $(LIBFT_PATH)libft.a -lreadline -fsanitize=address -o $(ENAME)

# Clean all the object files and the binary
clean:   
	@echo "[Cleaning]"
	@$(RM) -rfv $(OBJ_PATH)*

fclean: clean
		@$(RM) -rfv $(NAME)
		@$(RM) -rfv $(ENAME)

re: fclean all

san: all
	$(CC) $(CFLAGS) $(NAME) -fsanitize=address -g -o $(ENAME)

.PHONY : clean fclean re