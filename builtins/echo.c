/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:19:46 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/15 21:48:41 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int	n_opt(char **args, int i)
{
	int	n_opt;
	int	j;

	n_opt = 0;
	j = 0;
	if (args[i][0] == '-')
	{
		while (args[i][j] == '-' && args[i][j])
			j ++;
		if (args[i][j] == 'n')
		{
			while (args[i][j] == 'n' && args[i][j])
				j++;
		}
		if (args[i][j] == '\0')
			n_opt = 1;
		else
			n_opt = 0;
	}
	return (n_opt);
}

int	ft_echo(char **args)
{
	int		i;
	int		n_pt;

	i = 1;
	n_pt = 0;
	if (nb_args(args) > 1)
	{
		while (args[i] && args[i][0] == '-')
		{
			n_pt = n_opt(args, i);
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n_pt == 0)
		write(1, "\n", 1);
	return (0);
}
