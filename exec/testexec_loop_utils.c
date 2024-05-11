/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:03:31 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/09 18:35:06 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_cp(t_cmd_processing *cmd_processing, t_tool *tool, t_command *cmd)
{
	cmd_processing->is_builtin = false;
	// cmd_processing->is_parenthesis = (cmd && cmd->content
	// 		&& cmd->content[0] == '(' && ft_strchr(cmd->content, ')'));
	cmd_processing->cmd_name = 0;
	// cmd_processing->sub_cmd = !(tool->hist);
}

bool	has_command(t_command *cmd)
{
	while (cmd)
	{
		if (cmd && cmd->content && cmd->content[0] && cmd->purpose == COMMAND)
			return (true);
		cmd = cmd->next;
	}
	return (false);
}