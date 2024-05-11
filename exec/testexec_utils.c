/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:03:25 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/09 18:29:55 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmds(t_command *cmd)
{
	int		n;

	n = 1;
	while (cmd && cmd->purpose != CMD_DELIM)
	{
		if (cmd->purpose == DELIM)
			n++;
		cmd = cmd->next;
	}
	return (n);
}

void	free_redirs(t_redir_pipe *redir)
{
	t_redir_pipe	*next;

	while (redir)
	{
		next = redir->next;
		free(redir);
		redir = next;
	}
}

t_command	*go_to_next_cmd(t_command *cmd)
{
	cmd = cmd->next;
	while (cmd && cmd->purpose != DELIM && cmd->purpose != CMD_DELIM)
		cmd = cmd->next;
	if (!cmd || cmd->purpose == CMD_DELIM)
		return (cmd);
	return (cmd->next);
}

void	exec_cleaner(t_cmd_processing cmd_processing)
{
	free(cmd_processing.cmd);
	free_redirs(cmd_processing.redir);
	if (cmd_processing.cmd_name)
		free(cmd_processing.cmd_name);
}

void	close_pipes(int *pipes)
{
	close(pipes[0]);
	close(pipes[1]);
}