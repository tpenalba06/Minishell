/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:25:15 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/15 21:59:47 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_exit(void)
{
	printf("exit\n");
	exit(EXIT_FAILURE);
}

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
// void printList (t_mini *mini)
// {
// 	t_lexer *tmp;

// 	tmp = mini->lexer;
// 	if (tmp && tmp->token == 5)
// 		terror(tmp->content, mini->lexer);
// 	while (tmp)
// 	{
// 		if (tmp->next)
// 		{
// 			if ((tmp->token != 0 && tmp->token != 5 && tmp->next->token != 0))
// 			{
// 				printf("lol\n");
// 				terror(tmp->content, mini->lexer);
// 			}
// 		}
// 		printf("---------------------\n");
// 		printf("element : %s\n", tmp->content);
// 		printf("token is : %d\n", tmp->token);
// 		printf("---------------------\n");
// 		tmp = tmp->next;
// 	}
// }

void	ft_prompt(t_mini *mini, t_parsing *parsing, char **env)
{
	mini->charenv = env;
	get_env(mini->env, mini);
	while (1)
	{
		signal(SIGINT, handle_signals);
		signal(SIGQUIT, SIG_IGN);
		parsing->input = readline("minishell> ");
		add_history(parsing->input);
		if (parsing->input == NULL)
			exit_exit();
		if (lexluthor(mini, parsing) == 130)
			continue ;
		if (mini->lexer == NULL)
			continue ;
		if (mini->lexer->error == 1)
			continue ;
		parse_cmds(mini->lexer);
		sort_env(mini->env);
		executor(mini);
		del_first_lex(mini, parsing);
	}
}
