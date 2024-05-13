/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:56:32 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/13 20:15:27 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin(t_cmd_processing *cmd, t_env *env, t_mini *mini)
{
	if (ft_strcmp("echo", cmd->cmd[0]) == 0)
		return (ft_echo(cmd->cmd));
	else if (ft_strcmp("env", cmd->cmd[0]) == 0)
		return (ft_env(env));
	else if (ft_strcmp("export", cmd->cmd[0]) == 0)
		return (export(env, cmd->cmd, mini));
	else if (ft_strcmp("unset", cmd->cmd[0]) == 0)
		return (unset(env, cmd->cmd));
	else if (ft_strcmp("cd", cmd->cmd[0]) == 0)
		return (ft_cd(cmd->cmd, env));
	else if (ft_strcmp("pwd", cmd->cmd[0]) == 0)
		return (ft_pwd());
	return (-1);
}
