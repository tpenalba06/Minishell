/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:56:32 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/12 23:32:34 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_exec_bltn(t_cmd_processing *cmd, t_mini *mini, bool one)
{
	if (ft_strcmp("echo", cmd->cmd_name) == 0)
		return (echo(cmd->cmd));
	else if (ft_strcmp("env", cmd->cmd_name) == 0)
		return (env(mini->env, false));
	else if (ft_strcmp("export", cmd->cmd_name) == 0)
		return (export(cmd->cmd, &(t->env)));
	else if (ft_strcmp("unset", cmd->cmd_name) == 0)
		return (unset(cmd->cmd, &(t->env)));
	else if (ft_strcmp("cd", cmd->cmd_name) == 0)
		return (cd(cmd->cmd, &t));
	else if (ft_strcmp("pwd", cmd->cmd_name) == 0)
		return (pwd(t->cwd));
}
