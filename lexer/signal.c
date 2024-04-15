/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:11:07 by tpenalba          #+#    #+#             */
/*   Updated: 2024/03/18 21:22:52 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_signal_actions(void)
{
	struct sigaction	act;

	bzero(&act, sizeof(act));
	act.sa_handler = &handle_signals;
	sigaction(SIGINT, &act, NULL);
}

void	handle_signals(int signal)
{
	if (signal == SIGINT)
	{
		printf("'\'C \n");
		rl_on_new_line();
		rl_forced_update_display();
	}
}
