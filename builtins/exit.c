/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:22:20 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/09 20:07:57 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static long	get_exit_code(char **cmd, long ret)
{
	if (cmd && cmd[1])
	{
		if (!is_long(cmd[1], true))
		{
			printfd(ERR, "exit: %s: numeric argument required\n", cmd[1]);
			return (2);
		}
		else
			return (ft_atol(cmd[1]));
	}
	else
		return (ret);
}

int	excuz(char **cmd, long ret, t_tool *tool, bool one)
{
	long	exit_code;

	if (cmd && cmd[1] && cmd[2])
	{
		write(2, "exit: too many arguments\n", 25);
		return (1);
	}
	exit_code = get_exit_code(cmd, ret);
	if (one && tool->c_env)
		free_char_etoile_etoile(tool->c_env);
	if (one && tool->cwd)
		free(tool->cwd);
	free_whole_env(tool->env);
	exit(exit_code % 256);
}