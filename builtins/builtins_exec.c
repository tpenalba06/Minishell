/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:56:32 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/16 14:23:13 by tpenalba         ###   ########.fr       */
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

int	exec_builtin(t_cmd_processing *cmd, t_env *env, t_mini *mini)
{
	long	ret_val;
	int		save_in;
	int		save_out;
	int		save_err;

	if (cmd->redir.in != -1)
	{
		save_in = dup(STDIN_FILENO);
		save_out = dup(STDOUT_FILENO);
		save_err = dup(STDERR_FILENO);
	}
	ret_val = find_exec_bltn(cmd, env, mini);
	if (cmd->redir.out != -1)
	{
		printf("LA");
		dup2(save_in, STDIN_FILENO);
		dup2(save_out, STDOUT_FILENO);
		dup2(save_err, STDERR_FILENO);
		close(save_in);
		close(save_out);
		close(save_err);
	}
	return (ret_val);
}
