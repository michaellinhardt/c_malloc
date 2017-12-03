# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/08 03:40:52 by mlinhard          #+#    #+#              #
#    Updated: 2016/05/25 22:53:18 by mlinhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra
NAME			= libft.a
LIST_HEADER		= libft.h
LIST_C_LIBFT	= ft_strlen.c ft_strcmp.c ft_strdup.c ft_strcpy.c ft_strncpy.c \
				  ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
				  ft_strstr.c ft_strnstr.c ft_strncmp.c ft_putendl.c ft_itoa.c \
				  ft_putchar.c ft_putchar_fd.c ft_putstr.c ft_putstr_fd.c \
				  ft_putnbr_fd.c ft_putnbr.c ft_stralloc.c ft_putendl_fd.c \
				  ft_islower.c ft_isupper.c ft_toupper.c ft_tolower.c \
				  ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
				  ft_isprint.c ft_isspace.c ft_strdel.c ft_strclr.c \
				  ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c \
				  ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
				  ft_memchr.c ft_memcmp.c ft_memalloc.c ft_memdel.c \
				  ft_atoi.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
				  ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
				  ft_strtolower.c ft_strtoupper.c ft_countwords.c ft_pow.c \
				  ft_pcol.c ft_imaxtoa_base.c ft_uimaxtoa_base.c \
				  ft_wchartostr.c ft_strrealloc.c ft_ldtoa.c ft_atoimax.c \
				  ft_strrchr.c ft_lstmap.c ft_striter.c ft_strnequ.c \
				  ft_strnew.c ft_strsplit.c ft_lstiter.c ft_strrev.c \
				  ft_wstrtostr.c
LIST_C_PRINTF	= ft_printf.c ft_printf_join.c ft_printf_parse.c \
				  ft_printf_parse_option.c ft_printf_build_color.c \
				  ft_printf_build_array.c ft_printf_build_format.c \
				  ft_printf_build_tools.c ft_printf_build_str.c \
				  ft_printf_build_int.c ft_printf_build_int_base.c \
				  ft_printf_build_int_tools.c ft_printf_build_double.c \
				  ft_printf_build_double_short.c ft_printf_build_n.c \
				  ft_printf_build_write.c
LIST_C_GNL		= get_next_line.c
PATH_LIBFT		= $(addprefix libft/, $(LIST_C_LIBFT))
PATH_PRINTF		= $(addprefix printf/, $(LIST_C_PRINTF))
PATH_GNL		= $(addprefix gnl/, $(LIST_C_GNL))
LIST_OBJ_LIBFT	= $(subst .c,.o,$(PATH_LIBFT))
LIST_OBJ_PRINTF	= $(subst .c,.o,$(PATH_PRINTF))
LIST_OBJ_GNL	= $(subst .c,.o,$(PATH_GNL))

C_END	= "\033[0m"
C_GOOD	= "\033[32m"
C_GREY  = "\033[1;30m"
C_BAD	= "\033[31m"
C_BLUE	= "\033[34;1m"

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I./includes/ -c -o $@ $<

$(NAME): $(LIST_OBJ_LIBFT) $(LIST_OBJ_PRINTF) $(LIST_OBJ_GNL)
	@ar rc $(NAME) $(LIST_OBJ_LIBFT) $(LIST_OBJ_PRINTF) $(LIST_OBJ_GNL)
	@ranlib $(NAME)
	@echo "✅  ["$(C_GOOD) $(NAME) $(C_END)"] created"

clean:
	@rm -rf $(LIST_OBJ_LIBFT)
	@rm -rf $(LIST_OBJ_PRINTF)
	@rm -rf $(LIST_OBJ_GNL)
	@echo "⚰  ["$(C_GREY) $(NAME) $(C_END)"] objs deleted"

fclean: clean
	@rm -rf $(NAME)
	@echo "⚰  ["$(C_GREY) $(NAME) $(C_END)"] bin deleted"

re: fclean all

-main:
	$(CC) $(CFLAGS) -I./includes/ main.c libft.a

test: all -main
	./a.out
	rm -rf ./a.out

leaks: all -main -leaks
-leaks:
	@valgrind --leak-check=yes --track-origins=yes ./a.out

.PHONY: clean fclean re clear test leaks libft
