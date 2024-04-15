/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:10:10 by tpenalba          #+#    #+#             */
/*   Updated: 2024/04/15 15:28:12 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <linux/limits.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdarg.h>
# include <string.h>

typedef enum e_token
{
	indefini,
	less_than,
	more_than,
	less_less,
	more_more,
	pipee
}	t_token;

typedef enum e_cmds
{
	undefined,
	COMMAND,
	IN_FILE,
	OUT_FILE,
	HEREDOC,
	APPEND,
	METACHAR
	
} t_cmds;

typedef struct s_parsing
{
	char	*input;
	char	**tab;
	int 	index;
	int		i;
	int		maillon;
}	t_parsing;

typedef struct s_env 
{
	char *name;
	char *value;
	t_env *next;
}t_env;

typedef struct s_lexer	t_lexer;
typedef struct s_lexer
{
	char			*content;
	t_token			token;
	t_cmds			cmds;
	t_lexer			*next;
	t_lexer			*prev;
}	t_lexer;

typedef struct s_mini
{
	t_parsing	*parsing;
	t_lexer		*lexer;
}	t_mini;

//inuit
void	init_data(t_parsing *data);

//lis bien le prompteur morray
void	ft_prompt(t_mini *mini, t_parsing *parsing);

//lexluthor
void	lexluthor(t_mini *mini, t_parsing *parsing);
void	print_tab(char **tab);
void 	terror(char *str);

//split et "qu'o'tes" "a la con"
char	*delete_quotes_value(char *str);
char	remove_excess_quote(char *str);
int		there_is_quotes(t_parsing	*data);
int		check_quote(char *s, char c);
char	**split_line(char *str, t_parsing parsing);

//la liste de courses
void	fill_lst(t_mini *mini, t_parsing *parsing);
void 	printList (t_mini *mini);
t_lexer	*lstnew(void *content);
void 	del_first_lex(t_mini *mini, t_parsing *parsing);

//oh les tiktokers
void	tokenize(t_mini *mini);
void	tiktoken_error(t_mini *mini);
t_token	is_token(char *str);
char 	*fill_token(char *str, t_parsing *parsing, char **list);
char	what_token(char c);

//parsseur
void    parse_cmds(t_lexer *lexer);

//utilitaires (type Mercedes vito 2015)
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	norm(void);

#endif