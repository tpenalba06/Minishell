/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:29:42 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/15 21:37:16 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*exec3(t_mini *mini, t_lexer *lex_tmp)
{
	mini->ret = 126;
	ft_putstr_fd("permission denied\n", STDERR_FILENO);
	lex_tmp = go_next_cmd(lex_tmp, mini);
	return (lex_tmp);
}

t_lexer	*exec2(t_mini *mini, t_lexer *lex_tmp)
{
	if (mini->cmd_processing.cmd)
		mini->ret = exec_it(&(mini->cmd_processing), mini);
	else
		mini->ret = 1;
	lex_tmp = go_next_cmd(lex_tmp, mini);
	return (lex_tmp);
}

t_lexer	*exec1(t_mini *mini, t_lexer *lex_tmp)
{
	ft_putstr_fd ("command not found\n", STDERR_FILENO);
	mini->ret = 127;
	lex_tmp = go_next_cmd (lex_tmp, mini);
	return (lex_tmp);
}

void	executor(t_mini *mini)
{
	t_lexer			*lex_tmp;

	(norm(), mini->ret = 0, lex_tmp = mini->lexer);
	init_exec(mini);
	while (lex_tmp != NULL)
	{
		petit_executor(mini, lex_tmp);
		if (mini->cmd_processing.cmd[0] && !mini->cmd_processing.is_builtin)
		{
			mini-> cmd_processing.full_path = find_path(mini, mini->charenv,
					mini->cmd_processing.cmd);
			if (mini->cmd_processing.full_path == NULL)
			{
				lex_tmp = exec1(mini, lex_tmp);
				continue ;
			}
			else if (access(mini->cmd_processing.full_path, X_OK) == -1)
			{
				lex_tmp = exec3(mini, lex_tmp);
				continue ;
			}
		}
		lex_tmp = exec2(mini, lex_tmp);
	}
	exec_util(mini);
}

// avancer dans t lexer 
// delim = | soit NULL