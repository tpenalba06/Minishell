# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 15:08:16 by tpenalba          #+#    #+#              #
#    Updated: 2024/05/13 17:04:16 by tpenalba         ###   ########.fr        #
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
		heredoc/heredoc.c \
		builtins/echo.c \
		lexer/remove_quotes.c \
		lexer/lexer_utils.c \
		utils/utils.c \
		utils/utils2.c \
		utils/utils3.c\
		utils/utils4.c\
		utils/utils5.c\
		parser/env_utils.c\
		parser/env_utils2.c\
		exec/pipe.c\
		exec/executor.c\
		builtins/export.c\
		builtins/unset.c\
		builtins/pwd.c\
		builtins/cd.c\
		builtins/builtins_exec.c\
		builtins/env.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=leak
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
