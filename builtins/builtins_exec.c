/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:56:32 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/09 21:09:55 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	find_exec_bltn(t_cmd_processing *cmd, t_tool *t, bool one)
{
	if (ft_strcmp("echo", cmd->cmd_name) == 0)
		return (echo(cmd->cmd));
	else if (ft_strcmp("env", cmd->cmd_name) == 0)
		return (env(t->env, false));
	else if (ft_strcmp("export", cmd->cmd_name) == 0)
		return (export(cmd->cmd, &(t->env)));
	else if (ft_strcmp("unset", cmd->cmd_name) == 0)
		return (unset(cmd->cmd, &(t->env)));
	else if (ft_strcmp("cd", cmd->cmd_name) == 0)
		return (cd(cmd->cmd, &t));
	else if (ft_strcmp("pwd", cmd->cmd_name) == 0)
		return (pwd(t->cwd));
}

static void	builtin_redirections(t_redir_pipe *redir)
{
	while (redir)
	{
		if (redir->fd_end == STDIN_FILENO && redir->fd_read != -1)
			dup2(redir->fd_read, STDIN_FILENO);
		if (redir->fd_end == STDOUT_FILENO && redir->fd_write != -1)
			dup2(redir->fd_write, STDOUT_FILENO);
		if (redir->fd_end == STDERR_FILENO && redir->fd_write != -1)
			dup2(redir->fd_write, STDERR_FILENO);
		redir = redir->next;
	}
}

static void	redir_back(int in, int out, int err)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	dup2(err, STDERR_FILENO);
	close(in);
	close(out);
	close(err);
}

long	exec_bltin(t_cmd_processing *cmd, t_tool *t, bool one)
{
	long	ret_val;
	int		save_in;
	int		save_out;
	int		save_err;

	if (one)
	{
		save_in = dup(STDIN_FILENO);
		save_out = dup(STDOUT_FILENO);
		save_err = dup(STDERR_FILENO);
		builtin_redirections(cmd->redir);
		// if (t->hist)
		// 	print_ps0(t);
	}
	ret_val = find_exec_bltn(cmd, t, one);
	if (one)
		redir_back(save_in, save_out, save_err);
	close_files(cmd->redir);
	exec_cleaner(*cmd);
	return (ret_val);
}