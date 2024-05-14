/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:49:02 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/14 19:42:05 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redisplay_error(void)
{
	printf("syntax error near token \n");
	rl_on_new_line();
}

void	parse_uber_command(t_lexer *lexer)
{
	if (lexer->token == 0 && lexer->cmds == 0)
		lexer->cmds = COMMAND;
	if (lexer->token == less_than || lexer->token == more_more
		|| lexer->token == more_than
		|| lexer->token == less_less || lexer->token == pipee)
		lexer->cmds = METACHAR;
	if (lexer->token == less_than && lexer->next)
		lexer->next->cmds = IN_FILE;
	if (lexer->token == more_than && lexer->next)
		lexer->next->cmds = OUT_FILE;
	if (lexer->token == less_less && lexer->next)
		lexer->next->cmds = HEREDOC;
	if (lexer->token == more_more && lexer->next)
		lexer->next->cmds = APPEND;
	if (lexer->token == 0 && lexer->cmds == 1
		&& (ft_strcmp(lexer->content, "echo") == 0
			|| ft_strcmp(lexer->content, "pwd") == 0
			|| ft_strcmp(lexer->content, "unset") == 0
			|| ft_strcmp(lexer->content, "env") == 0
			|| ft_strcmp(lexer->content, "export") == 0
			|| ft_strcmp(lexer->content, "exit") == 0
			|| ft_strcmp(lexer->content, "cd") == 0))
		lexer->cmds = BUILTIN;
}

void	parse_uber_first_command(t_lexer *lexer)
{
	if (lexer->token == 0 && lexer->cmds == 0)
		lexer->cmds = COMMAND;
	if (lexer->token == less_than || lexer->token == more_more
		|| lexer->token == more_than
		|| lexer->token == less_less || lexer->token == pipee)
		lexer->cmds = METACHAR;
	if (lexer->token == less_than && lexer->next)
		lexer->next->cmds = IN_FILE;
	if (lexer->token == more_than && lexer->next)
		lexer->next->cmds = OUT_FILE;
	if (lexer->token == less_less && lexer->next)
		lexer->next->cmds = HEREDOC;
	if (lexer->token == more_more && lexer->next)
		lexer->next->cmds = APPEND;
	if (lexer->token == 0 && lexer->cmds == 1
		&& (ft_strcmp(lexer->content, "echo") == 0
			|| ft_strcmp(lexer->content, "pwd") == 0
			|| ft_strcmp(lexer->content, "unset") == 0
			|| ft_strcmp(lexer->content, "env") == 0
			|| ft_strcmp(lexer->content, "export") == 0
			|| ft_strcmp(lexer->content, "exit") == 0
			|| ft_strcmp(lexer->content, "cd") == 0))
		lexer->cmds = BUILTIN;
}

void	parse_cmds(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	parse_uber_first_command(tmp);
	while (tmp)
	{
		parse_uber_command(tmp);
		tmp = tmp->next;
	}
}
