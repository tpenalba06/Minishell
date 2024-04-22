/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:10:10 by tpenalba          #+#    #+#             */
/*   Updated: 2024/04/22 18:37:34 by tpenalba         ###   ########.fr       */
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
	METACHAR,
	
} t_cmds;

typedef struct s_parsing
{
	char	*input;
	char	**tab;
	int 	index;
	int		i;
	int		maillon;
}	t_parsing;

typedef struct s_env t_env;
typedef struct s_env
{
	char *name;
	char *value;
	char *content;
	t_env *next;
}t_env;

typedef struct s_lexer	t_lexer;
typedef struct s_lexer
{
	char			*content;
	t_token			token;
	t_cmds			cmds;
	t_lexer			*next;
	//t_lexer			*prev;
}	t_lexer;

typedef struct s_mini
{
	char 		**charenv;
	int			fdin;
	int			fdout;
	t_parsing	*parsing;
	t_lexer		*lexer;
	t_env		*env;
}	t_mini;

//inuit
void	init_data(t_parsing *data);

//lis bien le prompteur morray
void	ft_prompt(t_mini *mini, t_parsing *parsing, char **env);

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
void	is_in(char *in, char c);

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
void 	get_env(t_env *env, t_mini *mini);
void	print_env(t_env *env, t_lexer *lexer);
void 	check_builtins(t_env *env, t_lexer *lexer);

//par ici la money
char *change_env(char *name, t_mini *mini);

//utilitaires (type Mercedes vito 2015)
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	norm(void);
char 	srch_index_c(char *str, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(char *src);
void 	ft_putstr(char *str);
int	ft_strcmp(const char *s1, const char *s2);
void	ft_putstr_fd(char *str, int fd);

//bulle tine
int is_echo(t_parsing *parsing);

#endif