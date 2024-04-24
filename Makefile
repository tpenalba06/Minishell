# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 15:08:16 by tpenalba          #+#    #+#              #
#    Updated: 2024/04/24 19:45:18 by tpenalba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = 	main.c \
	 	lexer/lexer.c \
		prompt.c \
		init.c \
		lexer/split_quote.c \
		lexer/fill_list.c \
		lexer/tokenize.c \
		parser/parse_cmds.c \
		parser/builtins.c \
		parser/get_env.c \
		parser/checkdollz.c \
		builtins/echo.c \
		builtins/export.c \
		builtins/unset.c \
		utils/utils.c
		
		



OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
LDFLAGS = -lreadline

.c.o:
	gcc $(CFLAGS) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
		gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all
