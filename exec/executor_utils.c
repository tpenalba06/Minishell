/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 00:06:52 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/14 00:08:26 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

t_lexer	*go_next_cmd(t_lexer *lex, t_mini *mini)
{
	mini->cmd_processing.ret.remaining--;
	while (lex)
	{
		if (lex->token == pipee)
		{
			lex = lex->next;
			free (mini->cmd_processing.cmd);
			return (lex);
		}
		lex = lex->next;
	}
	return (NULL);
}

unsigned long	count_arg(t_lexer *lex)
{
	unsigned long	arg;

	arg = 0;
	while (lex && lex->token != pipee)
	{
		arg += (lex->cmds == COMMAND || lex->cmds == BUILTIN);
		lex = lex->next;
	}
	return (arg);
}

int	count_pipes(t_mini *mini)
{
	t_lexer	*tmp;
	int		pipe;

	tmp = mini->lexer;
	pipe = 0;
	while (tmp)
	{
		if (tmp->token == pipee)
			pipe++;
		tmp = tmp->next;
	}
	return (pipe);
}
