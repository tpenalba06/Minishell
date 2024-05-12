/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:59:10 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/12 23:21:07 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define TEMP "/tmp/shell_here"
#define READ 0
#define WRITE 1

int	get_heredoc_file(int hd, int mode)
{
	char	*itoaed;
	char	*filename;
	int		fd;

	itoaed = ft_itoa(hd);
	if (!itoaed)
		return (-1);
	filename = ft_strjoin(TEMP, itoaed);
	if (!filename)
		return (-1);
	free(itoaed);
	fd = 0;
	unlink(filename);
	if (mode == WRITE)
		fd = open(filename, O_CREAT | O_WRONLY, 0666);
	free(filename);
	return (fd);
}

static void	write_heredoc(int fd, char *eof)
{
	char	*line;
	char	*temp;
	int		lines;

	lines = 0;
	while (++lines)
	{
		line = readline("> ");
		if (!line)
		{
			printf("NONONNNNN\n");
			break ;
		}
		if (!ft_strcmp(line, eof))
		{
			free(line);
			break ;
		}
		temp = ft_strjoin(line, "\n");
		free(line);
		if (!temp)
			break ;
		write(fd, temp, ft_strlen(temp));
		free(temp);
	}
}

void	sig_catch(int sig)
{
	printf("\n");
	rl_replace_line("", 0);
	g_sig_rec = sig;
}

static int	heredoc_child(int fd, char *eof)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		eof = ft_strdup(eof);
		signal(SIGINT, SIG_DFL);
		remove_excess_quote(eof);
		write_heredoc(fd, eof);
		free(eof);
		exit(0);
	}
	signal(SIGINT, sig_catch);
	g_sig_rec = 0;
	while (waitpid(pid, 0, WNOHANG) == 0)
	{
		if (g_sig_rec == SIGINT)
		{
			printf("My child died because I killed it\n");
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

static int	create_heredoc(int index, t_lexer *lexer)
{
	int	fd_heredoc;
	int	ret;

	fd_heredoc = get_heredoc_file(index, WRITE);
	if (fd_heredoc <= 0)
		return (1);
	ret = heredoc_child(fd_heredoc, lexer->content);
	if (ret)
		return (ret);
	close(fd_heredoc);
	return (0);
}

int	here_doc(t_lexer *lexer)
{
	int	i;
	int	ret;

	if (!lexer || !lexer->content)
		return (0);
	i = 0;
	ret = 0;
	while (lexer->next)
	{
		printf("%d\n", lexer->cmds);
		if (lexer->token == less_less && lexer->next)
		{
			ret = create_heredoc(i, lexer->next);
			if (ret)
				return (ret);
			i++;
		}
		lexer = lexer->next;
	}
	if (lexer->token == less_less && lexer->next)
		ret = create_heredoc(i, lexer->next);
	return (ret);
}