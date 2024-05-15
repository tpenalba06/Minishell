/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:39:10 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/15 21:37:05 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_util(t_mini *mini)
{
	mini->ret = wait_father(&(mini->cmd_processing.ret),
			mini->cmd_processing.ret.n_cmd, mini->ret);
}

void	init_exec(t_mini *mini)
{
	mini->cmd_processing.ret.n_cmd = count_pipes (mini) + 1;
	mini->cmd_processing.ret.remaining = mini->cmd_processing.ret.n_cmd;
	mini->cmd_processing.charenv = re_char_etoile_etoilise_env(mini->env);
	mini->cmd_processing.ret.fd = -1;
	mini->cmd_processing.redir.heredoc_no = 0;
}

void	petit_executor(t_mini *mini, t_lexer *lex_tmp)
{
	mini->cmd_processing.redir.in = -1;
	mini->cmd_processing.redir.out = -1;
	mini->cmd_processing.is_builtin = false;
	mini->cmd_processing.cmd = parse_into_char(lex_tmp,
			&(mini->cmd_processing.redir),
			&(mini->cmd_processing.is_builtin));
}
