/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:19:46 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/15 22:43:37 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	condition_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (1);
	if (str[0] == '-' && str[1] != 'n')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(char **tab)
{
	int		option;
	int		i;

	option = 0;
	i = 1;
	if (tab[i] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (tab[i] && condition_n(tab[i]) == 0)
	{
		i++;
		option = 1;
	}
	while (tab[i])
	{
		write(1, tab[i], ft_strlen(tab[i]));
		if (tab[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (option == 0)
		write(1, "\n", 2);
	return (0);
}
