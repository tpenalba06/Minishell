/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:22:20 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/15 21:49:57 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

void	mini_exit(char **cmd, t_mini *mini)
{
	if (cmd[1] == NULL)
	{
		ft_putstr_fd("exit\n1\n", 1);
		exit(EXIT_FAILURE);
	}
	else if (!(ft_isnum(cmd[1])))
	{
		printf("exit : %s: numeric argument required\n2\n", cmd[1]);
		exit(2);
	}
	else if (cmd[2] == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd(cmd[1], 1);
		ft_putstr_fd("\n", 1);
		exit(ft_atoi(cmd[1]));
	}
	else
	{
		ft_putstr_fd("exit : too many arguments\n", 1);
		mini->ret = 1;
	}
}
