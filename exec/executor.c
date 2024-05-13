/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:29:42 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/13 21:02:36 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

t_lexer	*go_next_cmd(t_lexer *lex, t_mini *mini)
{
	mini->cmd_processing.ret.remaining--;
	while (lex)
	{
		if (lex->token == pipee)
		{
			lex = lex->next;
			free (mini->cmd_processing.cmd);
			return (lex);
		}
		lex = lex->next;
	}
	return (NULL);
}

unsigned long	count_arg(t_lexer *lex)
{
	unsigned long	arg;

	arg = 0;
	while (lex && lex->token != pipee)
	{
		arg += (lex->cmds == COMMAND || lex->cmds == BUILTIN);
		lex = lex->next;
	}
	return (arg);
}

int	count_pipes(t_mini *mini)
{
	t_lexer	*tmp;
	int		pipe;

	tmp = mini->lexer;
	pipe = 0;
	while (tmp)
	{
		if (tmp->token == pipee)
			pipe++;
		tmp = tmp->next;
	}
	return (pipe);
}

char	**parse_into_char(t_lexer *lex, t_redir *redir, bool *is_builtin)
{
	unsigned long	nb_arg;
	unsigned long	index;
	bool			first;
	char			**cmd;

	(norm (), first = true, index = 0, nb_arg = count_arg (lex));
	cmd = ft_calloc(nb_arg + 1, sizeof(char *));
	while (cmd && lex && lex->token != pipee)
	{
		if (lex->cmds == COMMAND || lex->cmds == BUILTIN)
		{
			if (first && lex->cmds == BUILTIN)
				*is_builtin = true;
			cmd[index] = lex->content;
			index++;
			first = false;
		}
		else if (lex->cmds >= IN_FILE && lex->cmds <= APPEND)
		{
			if (handle_redir(lex, redir))
				return (NULL);
		}
		lex = lex->next;
	}
	return (cmd);
}

static unsigned long	exec_it(t_cmd_processing *cp, t_mini *mini)
{
	if (cp->is_builtin && cp->ret.n_cmd == 1)
	{
		return (exec_builtin(cp, mini->env, mini));
	}
	if (pipe(cp->ret.pipes) == -1)
	{
		perror("pipe");
		return (2);
	}
	cp->ret.pid = fork();
	if (cp->ret.pid == -1)
	{
		perror("fork");
		return (2);
	}
	else if (cp->ret.pid == 0)
	{
		if (cp->redir.in != -1)
			dup2(cp->redir.in, STDIN_FILENO);
		else if (cp->ret.fd != -1)
		{
			dup2(cp->ret.fd, STDIN_FILENO);
		}
		else if (cp->ret.remaining != cp->ret.n_cmd)
			dup2(cp->ret.pipes[0], STDIN_FILENO);
		close(cp->ret.pipes[0]);
		if (cp->redir.out != -1)
			dup2(cp->redir.out, STDOUT_FILENO);
		else if (cp->ret.remaining != 1)
		{
		// FAIS ATTENTION ICI TU NE DOIS FAIRE CE ELSE QUE SIL RESTE UN CMD APRES DONC COMPTE OU CHECK QUIL Y A UN AUTRE PIPE EN TOUT CAS PARCE QUE SINON CA NE ECHOERA PAS DANS LE STDOUT MAIS DANS UN PIPE QUI NE SERA PAS AFFICHE DANS LE TERMINAL CE QUI NE CORRESPOND PAS A CE QUE LON ATTEND
			dup2(cp->ret.pipes[1], STDOUT_FILENO);
		}
		close(cp->ret.pipes[1]);
		if (cp->ret.fd != -1)
			close(cp->ret.fd);
		if (cp->is_builtin)
			exit(exec_builtin(cp, mini->env, mini));
		else
			execve(cp->full_path, cp->cmd, cp->charenv);
		exit(1);
	}
	else
	{
		if (cp->ret.fd != -1)
			close(cp->ret.fd);
		cp->ret.fd = dup(cp->ret.pipes[0]);
		close(cp->ret.pipes[1]);
		close(cp->ret.pipes[0]);
		if (cp->redir.in != -1)
			close(cp->redir.in);
		if (cp->redir.out != -1)
			close(cp->redir.out);
	}
	return (0);
}

long	wait_father(t_ret_cmd *ret, unsigned long n_cmd, long err)
{
	int	exit_st;
	int	status;

	if (ret->fd != -1)
		close(ret->fd);
	exit_st = -1;
	status = 0;
	while (n_cmd != 0)
	{
		if (waitpid(-1, &status, 0) == ret->pid)
			exit_st = status;
		n_cmd--;
	}
	if (exit_st == -1)
		exit_st = status;
	if (err)
		return (err);
	return (WEXITSTATUS(exit_st));
}

void	executor(t_mini *mini)
{
	unsigned long	ret;
	t_lexer			*lex_tmp;
	int 			i;

	(norm(), ret = 0, lex_tmp = mini->lexer);
	mini->cmd_processing.ret.n_cmd = count_pipes (mini) + 1;
	mini->cmd_processing.ret.remaining = mini->cmd_processing.ret.n_cmd;
	if (mini->cmd_processing.charenv)
		free_char_tab(mini->cmd_processing.charenv);
	mini->cmd_processing.charenv = re_char_etoile_etoilise_env(mini->env);
	mini->cmd_processing.ret.fd = -1;
	mini->cmd_processing.redir.heredoc_no = 0;
	while (lex_tmp != NULL)
	{
		i = 0;
		mini->cmd_processing.redir.in = -1;
		mini->cmd_processing.redir.out = -1;
		mini->cmd_processing.is_builtin = false;
		if (mini->cmd_processing.cmd)
			free_char_tab(mini->cmd_processing.cmd);
		mini->cmd_processing.cmd = parse_into_char(lex_tmp,
				&(mini->cmd_processing.redir),
				&(mini->cmd_processing.is_builtin));
		if (mini->cmd_processing.cmd && !mini->cmd_processing.is_builtin)
		{
			mini->cmd_processing.full_path = find_path(mini, mini->charenv,
					mini->cmd_processing.cmd);
			if (mini->cmd_processing.full_path == NULL)
			{
				ft_putstr_fd ("command not found\n", STDERR_FILENO);
				ret = 127;
				lex_tmp = go_next_cmd (lex_tmp, mini);
				continue ;
			}
			else if (access(mini->cmd_processing.full_path, X_OK) == -1)
			{
				ret = 126;
				ft_putstr_fd("permission denied\n", STDERR_FILENO);
				lex_tmp = go_next_cmd(lex_tmp, mini);
				continue ;
			}
		}
		if (mini->cmd_processing.cmd)
			ret = exec_it(&(mini->cmd_processing), mini);
		else
			ret = 1;
		if (i == 0)
			lex_tmp = go_next_cmd(lex_tmp, mini);
	}
	printf("%ld\n", wait_father(&(mini->cmd_processing.ret),
			mini->cmd_processing.ret.n_cmd, ret));
}

// avancer dans t lexer 
// delim = | soit NULL