/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:29:42 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/14 19:07:00 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_exec(t_mini *mini)
{
	mini->cmd_processing.ret.n_cmd = count_pipes (mini) + 1;
	mini->cmd_processing.ret.remaining = mini->cmd_processing.ret.n_cmd;
	//if (mini->cmd_processing.charenv)
	//	free_char_tab(mini->cmd_processing.charenv);
	mini->cmd_processing.charenv = re_char_etoile_etoilise_env(mini->env);
	mini->cmd_processing.ret.fd = -1;
	mini->cmd_processing.redir.heredoc_no = 0;
}

void	petit_executor(t_mini *mini, t_lexer *lex_tmp)
{
	mini->cmd_processing.redir.in = -1;
	mini->cmd_processing.redir.out = -1;
	mini->cmd_processing.is_builtin = false;
	//if (mini->cmd_processing.cmd[0])
	//	free_char_tab(mini->cmd_processing.cmd);
	mini->cmd_processing.cmd = parse_into_char(lex_tmp,
			&(mini->cmd_processing.redir),
			&(mini->cmd_processing.is_builtin));
}

void	executor(t_mini *mini)
{
	unsigned long	ret;
	t_lexer			*lex_tmp;
	int				i;

	(norm(), ret = 0, lex_tmp = mini->lexer);
	init_exec(mini);
	while (lex_tmp != NULL)
	{
		i = 0;
		petit_executor(mini, lex_tmp);
		if (mini->cmd_processing.cmd[0] && !mini->cmd_processing.is_builtin)
		{
			// printf("%s\n", mini->cmd_processing.cmd);
			mini-> cmd_processing.full_path = find_path(mini, mini->charenv,
					mini->cmd_processing.cmd);
			if (mini->cmd_processing.full_path == NULL)
			{
				ft_putstr_fd ("command not found\n", STDERR_FILENO);
				ret = 127;
				lex_tmp = go_next_cmd (lex_tmp, mini);
				continue ;
			}
			else if (access(mini->cmd_processing.full_path, X_OK) == -1)
			{
				ret = 126;
				ft_putstr_fd("permission denied\n", STDERR_FILENO);
				lex_tmp = go_next_cmd(lex_tmp, mini);
				continue ;
			}
		}
		if (mini->cmd_processing.cmd)
			ret = exec_it(&(mini->cmd_processing), mini);
		else
			ret = 1;
		if (i == 0)
			lex_tmp = go_next_cmd(lex_tmp, mini);
	}
	printf("%ld\n", wait_father(&(mini->cmd_processing.ret),
			mini->cmd_processing.ret.n_cmd, ret));
	g_sig_rec = ret;
}

// avancer dans t lexer 
// delim = | soit NULL