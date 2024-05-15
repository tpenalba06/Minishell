/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:10:10 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/15 22:08:55 by tpenalba         ###   ########.fr       */
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
# include <dirent.h>
# include <termios.h>

extern int	g_sig_rec;

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
	BUILTIN,
	VAR_ASSIGN,
	CMD_DELIM,
	HERE_STRING,
	HERE_DOC_DELIM,
	REDIR_ID,
	IN_OUT_FILE,
	DELIM
}	t_cmds;

typedef struct s_parsing
{
	int		check_int;
	char	*input;
	char	**tab;
	int		index;
	int		i;
}	t_parsing;

//typedef struct s_env	t_env;

typedef struct s_env
{
	char			*name;
	char			*value;
	char			*content;
	bool			is_exported;
	struct s_env	*next;
}	t_env;

typedef struct s_tool
{
	t_env	*env;
	char	**c_env;
	long	rt_val;
	char	*cwd;
}	t_tool;

//typedef struct	s_lexer		t_lexer;

typedef struct s_lexer
{
	int						error;
	char					*content;
	t_token					token;
	t_cmds					cmds;
	struct s_lexer			*tmp;
	struct s_lexer			*next;
	struct s_lexer			*prev;
}	t_lexer;

typedef struct s_command
{
	char				*content;
	enum e_cmds			purpose;
	struct s_command	*next;
}	t_command;

typedef struct t_redir
{
	int	in;
	int	out;
	int	heredoc_no;
}	t_redir;

typedef struct s_dollar
{
	char	*name;
	char	*value;
	char	*end;
	int		i;
}	t_dollar;

typedef struct s_ret_cmd
{
	pid_t			pid;
	int				fd;
	int				pipes[2];
	unsigned long	n_cmd;
	unsigned long	remaining;
}	t_ret_cmd;

typedef struct t_cmd_processing
{
	char			**cmd;
	char			**charenv;
	char			*cmd_name;
	bool			is_builtin;
	char			*full_path;
	t_redir			redir;
	t_ret_cmd		ret;
}	t_cmd_processing;

typedef struct s_path
{
	char	**tabchar;
	char	*tab;
}	t_path;

typedef struct s_mini
{
	int					i;
	int					ret;
	char				**charenv;
	int					fdin;
	int					fdout;
	bool				env_changed;
	int					argg;
	int					countpipe;
	t_dollar			*dollar;
	t_parsing			*parsing;
	t_lexer				*lexer;
	t_env				*env;
	t_redir				*redir;
	t_path				*path;
	t_cmd_processing	cmd_processing;
}	t_mini;

//inuit
void			init_data(t_parsing *data);

//lis bien le prompteur morray
void			ft_prompt(t_mini *mini, t_parsing *parsing, char **env);

//lexluthor
int				lexluthor(t_mini *mini, t_parsing *parsing);
void			print_tab(char **tab);
void			terror(char *str, t_lexer *lexer);
void			check_syntax(t_lexer *lexer);

//split et "qu'o'tes" "a la con"
char			*delete_quotes_value(char *str);
char			remove_excess_quote(char *str);
int				there_is_quotes(t_parsing	*data);
int				check_quote(char *s, char c);
char			**split_line(char *str, t_parsing parsing);
void			is_in(char *in, char c);

//la liste de courses
void			fill_lst(t_mini *mini, t_parsing *parsing);
t_lexer			*lstnew(void *content);
void			del_first_lex(t_mini *mini, t_parsing *parsing);
void			lstadd_back(t_mini *mini, t_lexer *new);
t_lexer			*lstlast(t_lexer *lst);

//void	printList(t_mini *mini);

//oh les tiktokers
void			tokenize(t_mini *mini);
void			tiktoken_error(t_mini *mini);
t_token			is_token(char *str);
char			*fill_token(char *str, t_parsing *parsing, char **list);
char			what_token(char c);

//parsseur
void			parse_cmds(t_lexer *lexer);
void			get_env(t_env *env, t_mini *mini);
char			**re_char_etoile_etoilise_env(t_env *env);
int				is_env_char(char c);

//par ici la money
char			*change_env(char *name, t_mini *mini);
t_env			*envlast(t_env *lst);
void			env_add_back(t_mini *mini, t_env *new);
t_env			*envnew(char *name, char *value);
int				is_env_char(char c);
void			sort_env(t_env *head);

//utilitaires (type Mercedes vito 2015)
void			*ft_calloc(size_t count, size_t size);
void			ft_bzero(void *s, size_t n);
void			norm(void);
char			srch_index_c(char *str, char c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *src);
void			ft_putstr(char *str);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_putstr_fd(char *str, int fd);
size_t			ft_strlen(const char *str);
int				there_is_equal(char *str);
void			redisplay_error(void);
size_t			ft_strlcat(char *s1, const char *s2, size_t n);
int				ft_strlcpy(char *dst, const char *src, unsigned int size);
size_t			ft_strlen(const char *str);
int				ft_strchr_int(char *str, char c);
int				ft_atoi(const char *str);
char			**ft_split(char const *s, char c);
char			*ft_strjoinps(char *s1, char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			ft_putendl_fd(char *s, int fd);
char			*ft_itoa(int n);
void			free_char_tab(char **tab);
void			error_newline(void);

//terminator
void			executor(t_mini *mini);
char			**parse_into_char(t_lexer *lex, t_redir *redir,
					bool *is_builtin);
unsigned long	exec_it(t_cmd_processing *cp, t_mini *mini);
long			wait_father(t_ret_cmd *ret, unsigned long n_cmd, long err);
unsigned long	count_arg(t_lexer *lex);
t_lexer			*go_next_cmd(t_lexer *lex, t_mini *mini);
int				count_pipes(t_mini *mini);
void			init_exec(t_mini *mini);
void			petit_executor(t_mini *mini, t_lexer *lex_tmp);
void			exec_util(t_mini *mini);

//paf
char			*find_path(t_mini *mini, char **env, char **cmd);

//ear doc
int				here_doc(t_lexer *lexer);
void			handle_signals(int signal);
int				heredoc_child(int fd, char *eof);
int				create_heredoc(int index, t_lexer *lexer);
void			write_heredoc(int fd, char *eof);

//bulle tine
int				exec_builtin(t_cmd_processing *cmd, t_env *env, t_mini *mini);
//
int				export(t_env *env, char **cmd, t_mini *mini);
int				there_is_equal(char *str);
char			*changeval(char *str);
void			print_env_export(t_env *env);
//
int				ft_cd(char **args, t_env *env);
char			*get_env_name(char *dest, const char *src);
int				env_add(const char *value, t_env *env);
int				is_in_env(t_env *env, char *args);
void			*ft_memdel(void *ptr);
//
int				unset(char **cmd, t_mini *mini);
int				ft_pwd(void);
int				ft_echo(char **args);
int				ft_env(t_env *env);
char			*dollarwhy(t_mini *mini, char *str);
void			mini_exit(char **cmd, t_mini *mini);

//bzzzzzzzzz
void			sig_catch(int sig);

// //circulez svp
int				handle_redir(t_lexer *lex, t_redir *redir);

#endif