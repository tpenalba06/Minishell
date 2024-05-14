/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 23:40:18 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/14 14:09:00 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define TEMP "/tmp/shell_here"
#define READ 0
#define WRITE 1

static void	mychild(char *eof, int fd)
{
	eof = ft_strdup(eof);
	signal(SIGINT, SIG_DFL);
	remove_excess_quote(eof);
	write_heredoc(fd, eof);
	free(eof);
	exit(0);
}

int	heredoc_child(int fd, char *eof)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
		mychild(eof, fd);
	signal(SIGINT, sig_catch);
	g_sig_rec = 0;
	while (waitpid(pid, 0, WNOHANG) == 0)
	{
		if (g_sig_rec == SIGINT)
		{
			kill(pid, SIGINT);
			waitpid(pid, 0, 0);
			g_sig_rec = 0;
			signal(SIGINT, handle_signals);
			return (130);
		}
		continue ;
	}
	signal(SIGINT, handle_signals);
	return (0);
}
