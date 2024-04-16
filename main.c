/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:50:05 by tpenalba          #+#    #+#             */
/*   Updated: 2024/04/16 13:26:29 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;
	ft_bzero(&mini, sizeof(t_mini));
	mini.parsing = ft_calloc(1, sizeof(t_parsing));
	mini.lexer = NULL;
	if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	init_data(mini.parsing);
	ft_prompt(&mini, mini.parsing, env);
	free(mini.parsing);
	free(mini.lexer);
	return (0);
}
