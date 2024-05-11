/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:39:03 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/09 19:39:19 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_files(t_redir_pipe *redir)
{
	while (redir)
	{
		if (redir->opened_read && redir->fd_read >= 0)
			close(redir->fd_read);
		if (redir->opened_write && redir->fd_write >= 0)
			close(redir->fd_write);
		redir = redir->next;
	}
}