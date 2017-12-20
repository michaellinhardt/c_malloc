# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/17 00:38:09 by mlinhard          #+#    #+#              #
#    Updated: 2017/12/20 21:40:02 by mlinhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS	= -Wall -Wextra -Werror
CC		= gcc $(FLAGS)
INCS 	= -I./incs -I./libft/includes
LIBS	= ./libft
LIBFT 	= -L$(LIBS) -lft
LANGAGE	= c

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME	= libft_malloc_$(HOSTTYPE).so

SRC_DIR = srcs
OBJ_DIR = objs

LIST	=	ft_malloc \
			ft_malloc_print

SRC := $(addprefix $(SRC_DIR)/, $(addsuffix .$(LANGAGE), $(LIST)))
OBJ := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(LIST)))

C_END	= "\033[0m"
C_GOOD	= "\033[32m"
C_GREY  = "\033[1;30m"
C_BAD	= "\033[31m"
C_BLUE	= "\033[34;1m"

all: $(NAME)

hosttype:
	@echo "HostType is $(HOSTTYPE)"

test: $(NAME)
	@echo ============== TEST ==============
	@$(CC) $(FLAGS) $(INCS) -o libtest ./srcs/test.c -L./ -lft_malloc_$(HOSTTYPE)
	@./libtest
	@rm ./libtest

$(NAME): $(OBJ)
	@make -C $(LIBS)
	$(CC) $(FLAGS) $(INCS) $(LIBFT) -shared -o $@ $(OBJ)
	@echo "✅  ["$(C_GOOD) $(NAME) $(C_END)"] created"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(LANGAGE)
	@mkdir -p $(dir $@)
	$(CC) -fpic $(INCS) -o $@ -c $<

clean:
#	@make clean -C $(LIBS)
	@/bin/rm -rf $(OBJ_DIR)
	@echo "⚰  ["$(C_GREY) $(NAME) $(C_END)"] $(OBJ_DIR) folder deleted"

fclean: clean
	@/bin/rm -rf *.dSYM
#	@make fclean -C $(LIBS)
	@/bin/rm -f $(NAME)
	@echo "⚰  ["$(C_GREY) $(NAME) $(C_END)"] bin deleted"

re: fclean $(NAME)

.PHONY: all clean fclean re
