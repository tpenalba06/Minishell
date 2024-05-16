/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:06:42 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/16 13:40:25 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	h_redir1(t_lexer *lex, t_redir *redir)
// {
// 	if (redir->in != -1)
// 	{
// 		close(redir->in);
// 		redir->in = -1;
// 	}
// 	if (lex->cmds == IN_FILE)
// 		redir->in = open(lex->content, O_RDONLY);
// 	else
// 	{
// 		redir->in = open(ft_strjoin("/tmp/shell_here",
// 					ft_itoa(redir->heredoc_no)), O_RDONLY);
// 		redir->heredoc_no++;
// 	}
// }

// static void	h_redir2(t_lexer *lex, t_redir *redir)
// {
// 	if (redir->out != -1)
// 	{
// 		close(redir->out);
// 		redir->out = -1;
// 	}
// 	if (lex->cmds == OUT_FILE)
// 		redir->out = open(lex->content, O_CREAT | O_WRONLY);
// 	else
// 		redir->out = open(lex->content, O_CREAT | O_WRONLY | O_APPEND);
// }

int	handle_redir(t_lexer *lex, t_redir *redir)
{
	if (lex->cmds == IN_FILE || lex->cmds == HEREDOC)
	{
		if (redir->in != -1)
		{
			close(redir->in);
			redir->in = -1;
		}
		if (lex->cmds == IN_FILE)
			redir->in = open(lex->content, O_RDONLY);
		else
		{
			redir->in = open(ft_strjoin("/tmp/shell_here",
						ft_itoa(redir->heredoc_no)), O_RDONLY);
			redir->heredoc_no++;
		}
		if (redir->in == -1)
		{
			write(2, "No such file or directory\n", 27);
			return (1);
		}
	}
	else
	{
		if (redir->out != -1)
		{
			close(redir->out);
			redir->out = -1;
		}
		if (lex->cmds == OUT_FILE)
			redir->out = open(lex->content, O_CREAT | O_WRONLY);
		else
			redir->out = open(lex->content, O_CREAT | O_WRONLY | O_APPEND);
		if (redir->out == -1)
		{
			write(2, "Permission denied\n", 19);
			return (1);
		}
	}
	return (0);
}
