# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jordan <jordan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/07 15:19:36 by jordan            #+#    #+#              #
#    Updated: 2023/06/16 22:37:52 by jordan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable Name
ENAME	=	minishell
NAME	=	minishell.a
CFLAGS	=	-g 
AR		=	ar -rsc
FILES	=	main.c parse.c free.c\
			exec/utils_exec.c exec/get_cmd.c exec/exec_cmd.c \
			builtins/cd.c builtins/echo.c builtins/env.c \
			builtins/exit.c builtins/export.c builtins/unset.c \

# Path for .c , .h and .o Files 
SRC_PATH := ./src/
OBJ_PATH := ./src/OBJ/
LIBFT_PATH := ./inc/libft/

all : $(LIBFT) $(NAME)

$(LIBFT) :
	@echo [INFO] Compliling libft
	@make -C $(LIBFT_PATH)

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
	@echo [INFO] Creating $(Shell uname) Binary Executable [$(NAME)]
	$(AR) $(NAME) $(OBJ) $(LINKFLAGS)
	$(CC) $(CFLAGS) $(NAME) $(LIBFT_PATH)libft.a -lreadline -o $(ENAME)

# Clean all the object files and the binary
clean:   
	@echo "[Cleaning]"
	@$(RM) -rfv $(OBJ_PATH)*

fclean: clean
		@$(RM) -rfv $(NAME)
		@$(RM) -rfv $(ENAME)

re: fclean all

san: all
	$(CC) $(CFLAGS) $(NAME) -fsanitize=address -o $(ENAME)

.PHONY : clean fclean re