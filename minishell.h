/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:10:10 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/12 23:12:57 by tpenalba         ###   ########.fr       */
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

extern int g_sig_rec;

typedef enum e_token
{
	indefini,
	less_than,
	more_than,
	less_less,
	more_more,
	pipee
}	t_token;
/*
typedef enum e_built
{
	undefined,
	b_echo,
	b_cd,
	b_pwd,
	b_export,
	b_unset,
	b_env,
	b_exit,
}	t_built;
*/

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
	
} t_cmds;

typedef struct s_parsing
{
	char	*input;
	char	**tab;
	int 	index;
	int		i;
}	t_parsing;

typedef struct s_env t_env;
typedef struct s_env
{
	char 	*name;
	char	*value;
	char 	*content;
	bool	is_exported;
	t_env 	*next;
}t_env;

typedef struct s_tool
{
	t_env	*env;
	char	**c_env;
	long	rt_val;
	char	*cwd;
}t_tool;

typedef struct s_lexer	t_lexer;
typedef struct s_lexer
{
	int				error;
	char			*content;
	t_token			token;
	t_cmds			cmds;
	t_lexer			*next;
	t_lexer			*prev;
}	t_lexer;

typedef struct s_command
{
	char				*content;
	enum e_cmds			purpose;
	struct s_command	*next;
}t_command;

typedef struct t_redir {
	int in;
	int out;
	int	heredoc_no;
}	t_redir;

typedef struct s_ret_cmd
{
	pid_t	pid;
	int		fd;
	int		pipes[2];
	unsigned long	n_cmd;
	unsigned long	remaining;
}	t_ret_cmd;

typedef struct t_cmd_processing {
	char			**cmd;
	char 			**charenv;
	char			*cmd_name;
	bool			is_builtin;
	char			*full_path;
	t_redir			redir;
	t_ret_cmd		ret;
}	t_cmd_processing;

typedef struct s_path
{
	char **tabchar;
	char *tab;
} t_path;

typedef struct s_mini
{
	char 				**charenv;
	int					fdin;
	int					fdout;
	bool				env_changed;
	int					argg;
	int					countpipe;
	t_parsing			*parsing;
	t_lexer				*lexer;
	t_env				*env;
	t_redir				*redir;
	t_path				*path;
	t_cmd_processing 	cmd_processing;
}	t_mini;


//inuit
void	init_data(t_parsing *data);

//lis bien le prompteur morray
void	ft_prompt(t_mini *mini, t_parsing *parsing, char **env);

//lexluthor
void	lexluthor(t_mini *mini, t_parsing *parsing);
void	print_tab(char **tab);
void 	terror(char *str, t_lexer *lexer);
void 	check_syntax(t_lexer *lexer);

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
void	lstadd_back(t_mini *mini, t_lexer *new);

//oh les tiktokers
void	tokenize(t_mini *mini);
void	tiktoken_error(t_mini *mini);
t_token	is_token(char *str);
char 	*fill_token(char *str, t_parsing *parsing, char **list);
char	what_token(char c);

int	here_doc(t_lexer *lexer);
void	handle_signals(int signal);

//parsseur
void    parse_cmds(t_lexer *lexer);
void 	get_env(t_env *env, t_mini *mini);
char	**re_char_etoile_etoilise_env(t_env *env);

//par ici la money
char 	*change_env(char *name, t_mini *mini);
t_env	*envlast(t_env *lst);
void	env_add_back(t_mini *mini, t_env *new);
t_env	*envnew(char *name, char *value);
int 	is_env_char(char c);
void	sort_env(t_env *head);

//utilitaires (type Mercedes vito 2015)
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	norm(void);
char 	srch_index_c(char *str, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *src);
void 	ft_putstr(char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_putstr_fd(char *str, int fd);
size_t	ft_strlen(const char *str);
int		there_is_equal(char *str);
void 	redisplay_error(void);
size_t	ft_strlcat(char *s1, const char *s2, size_t n);
int		ft_strlcpy(char *dst, const char *src, unsigned int size);
size_t	ft_strlen(const char *str);
int 	ft_strchr_int(char *str, char c);
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strjoinps(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putendl_fd(char *s, int fd);
char	*ft_itoa(int n);


//path
void	executor(t_mini *mini);
char	*find_path(t_mini *mini, char **env, char **cmd);
void	pipex(t_mini *mini, char **av, char **envp);

//bulle tine
//int 	is_echo(t_parsing *parsing);
int    export(t_env *env, char **cmd, t_mini *mini);
// void 	check_builtins(t_env *env, t_parsing *parsing, t_lexer *lexer, t_mini *mini);
// void	print_env(t_env *env, t_lexer *lexer);
int    *unset(t_env *env, char **cmd);
// long	exec_bltin(t_cmd_processing *cmd, t_tool *t, bool one);
int		ft_cd(char **args, t_env *env);
int		env_add(const char *value, t_env *env);
int		is_in_env(t_env *env, char *args);
void	*ft_memdel(void *ptr);
char	*get_env_name(char *dest, const char *src);

int		ft_pwd(void);

// //circulez svp
// int			get_heredoc_file(int hd, int mode);
// void		unlink_heredocs(t_command *cmd);
// int			here_doc(t_command *cmd, t_tool *tool);
// void		close_files(t_redir_pipe *redir);
// void		perform_redirections(t_cmd_processing *cmd, t_ret_cmd *ret);

// //exector
// long	execute_the_line(t_command *cmd, t_tool *tool, int *heredoc_no);

// //mainloop
// long		ex_loop(t_command **cmd, t_tool *tool, t_ret_cmd *ret, int *n_cmd);
// static long	aexec(t_cmd_processing *c_p, t_tool *t, t_ret_cmd *ret, int *n_cmd);
// static long	c_get_ret(long err_status, t_ret_cmd *ret, int *n_cmd, bool n_empty);
// static long	c_get(t_cmd_processing *c_p, t_command **cmd, t_ret_cmd *r, int *n);
// static long	qaexec(t_cmd_processing *c_p, long err, t_ret_cmd *ret, int *n_cmd);
// //exec_doer
// long		wait_father(t_ret_cmd *ret, int n_cmd, long err);
// void		crt_child(t_cmd_processing *cmd, t_tool *t, t_ret_cmd *ret);
// static void	child(t_cmd_processing *cmd, t_tool *t, char **c_env, t_ret_cmd *ret);
// //exec utils
// void		close_pipes(int *pipes);
// void		exec_cleaner(t_cmd_processing cmd_processing);
// t_command	*go_to_next_cmd(t_command *cmd);
// void		free_redirs(t_redir_pipe *redir);
// int			count_cmds(t_command *cmd);
// //exec_loop_utils
// void	init_cp(t_cmd_processing *cmd_processing, t_tool *tool, t_command *cmd);
// bool	has_command(t_command *cmd);
// //cmd
// int	get_cmd(t_cmd_processing *cmd_processing, t_command *cmd, int *hd_no);

#endif