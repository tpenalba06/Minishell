/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:56:32 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/16 15:45:02 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_exec_bltn(t_cmd_processing *cmd, t_env *env, t_mini *mini)
{
	if (ft_strcmp("echo", cmd->cmd[0]) == 0)
		return (ft_echo(cmd->cmd));
	else if (ft_strcmp("env", cmd->cmd[0]) == 0)
		return (ft_env(env));
	else if (ft_strcmp("export", cmd->cmd[0]) == 0)
		return (export(env, cmd->cmd, mini));
	else if (ft_strcmp("unset", cmd->cmd[0]) == 0)
		return (unset(cmd->cmd, mini));
	else if (ft_strcmp("cd", cmd->cmd[0]) == 0)
		return (ft_cd(cmd->cmd, env));
	else if (ft_strcmp("pwd", cmd->cmd[0]) == 0)
		return (ft_pwd());
	else if (ft_strcmp("exit", cmd->cmd[0]) == 0)
		mini_exit(cmd->cmd, mini);
	return (0);
}

int	exec_builtin(t_cmd_processing *cmd, t_env *env, t_mini *mini, bool one)
{
	long	ret_val;
	int		tmpin;
	int		tmpout;

	(norm(), tmpin = -1, tmpout = -1);
	if (one)
	{
		if (cmd->redir.in != -1)
			tmpin = dup(STDIN_FILENO);
		if (cmd->redir.out != -1)
			tmpout = dup(STDOUT_FILENO);
		dup2(cmd->redir.in, STDIN_FILENO);
		dup2(cmd->redir.out, STDOUT_FILENO);
	}
	ret_val = find_exec_bltn(cmd, env, mini);
	if (one)
	{
		if (tmpin != -1)
			dup2(tmpin, STDIN_FILENO);
		if (tmpout != -1)
			dup2(tmpout, STDOUT_FILENO);
		close(tmpin);
		close(tmpout);
	}
	return (ret_val);
}
