/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:25:15 by tpenalba          #+#    #+#             */
/*   Updated: 2024/04/15 15:15:04 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay ();
	}
}

void	set_signal_actions(void)
{
	struct sigaction	act;

	bzero(&act, sizeof(act));
	act.sa_handler = &handle_signals;
	sigaction(SIGINT, &act, NULL);
}

void	ft_prompt(t_mini *mini, t_parsing *parsing)
{

	while (1)
	{
		signal(SIGINT, handle_signals);
		signal(SIGQUIT, SIG_IGN);
		parsing->input = readline("minishell> ");
		add_history(parsing->input);
		if (parsing->input == NULL)
		{
			printf("exit\n");
			exit(EXIT_FAILURE);
		}
		lexluthor(mini, parsing);
		parse_cmds(mini->lexer);
		//getenv
		//del delete_quotes
		//exec;
		del_first_lex(mini, parsing);
	}
}
