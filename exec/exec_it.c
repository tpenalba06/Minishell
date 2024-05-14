/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:36:16 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/14 17:13:07 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	exec_wut(t_cmd_processing *cp)
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

static void	exec_that(t_cmd_processing *cp, t_mini *mini)
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

unsigned long	exec_it(t_cmd_processing *cp, t_mini *mini)
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
		exec_that(cp, mini);
	else
		exec_wut(cp);
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
	g_sig_rec = WEXITSTATUS(exit_st);
	return (WEXITSTATUS(exit_st));
}
