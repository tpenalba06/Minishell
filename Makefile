# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 15:08:16 by tpenalba          #+#    #+#              #
#    Updated: 2024/05/15 18:04:15 by tpenalba         ###   ########.fr        #
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
		parser/get_env.c \
		parser/checkdollz.c \
		heredoc/heredoc.c \
		heredoc/heredoc_child.c\
		heredoc/files.c\
		builtins/echo.c \
		lexer/remove_quotes.c \
		lexer/lexer_utils.c \
		lexer/list_utils.c \
		utils/utils.c \
		utils/utils2.c \
		utils/utils3.c\
		utils/utils4.c\
		utils/utils5.c\
		parser/env_utils.c\
		parser/env_utils2.c\
		exec/executor.c\
		exec/exec_it.c\
		exec/path.c\
		exec/executor_utils.c\
		builtins/export.c\
		builtins/export_utils.c\
		builtins/unset.c\
		builtins/pwd.c\
		builtins/cd.c\
		builtins/cd_utils.c\
		parser/dollarwhy.c\
		builtins/builtins_exec.c\
		builtins/env.c\
		builtins/exit.c\
		redir/redir.c

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
