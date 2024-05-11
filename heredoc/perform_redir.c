/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:33:19 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/09 21:33:38 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup_redir(t_redir_pipe *redir, t_ret_cmd *ret)
{
	if (redir->fd_read != -1)
		dup2(redir->fd_read, redir->fd_end);
	if (redir->fd_write == STDOUT_FILENO && ret->n_cmd != 1)
		dup2(ret->pipes[1], redir->fd_end);
	else if (redir->fd_write != -1)
		dup2(redir->fd_write, redir->fd_end);
	if (redir->here_string)
	{
		perror(redir->here_string);
		write(redir->fd_end, redir->here_string, ft_strlen(redir->here_string));
	}
}

void	perform_redirections(t_cmd_processing *cmd, t_ret_cmd *ret)
{
	bool			is_in_read_duped;
	bool			is_out_write_duped;
	t_redir_pipe	*redir;

	is_in_read_duped = 0;
	is_out_write_duped = 0;
	redir = cmd->redir;
	while (redir)
	{
		is_in_read_duped = (is_in_read_duped
				|| (redir->fd_end == STDIN_FILENO && redir->fd_read != -1));
		is_out_write_duped = (is_out_write_duped
				|| (redir->fd_end == STDOUT_FILENO && redir->fd_write != -1));
		dup_redir(redir, ret);
		redir = redir->next;
	}
	if (!is_in_read_duped && ret->fd > -1)
		dup2(ret->fd, STDIN_FILENO);
	else if (!is_in_read_duped)
		dup2(ret->pipes[0], STDIN_FILENO);
	if (!is_out_write_duped && ret->n_cmd != 1)
		dup2(ret->pipes[1], STDOUT_FILENO);
}