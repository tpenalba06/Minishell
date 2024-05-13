/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:05:24 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/13 22:25:44 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	move_back(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}

void	is_in(char *in, char c)
{
	if (c == '"' || c == '\'')
	{
		if (*in == 0)
			*in = c;
		else if (*in == c)
			*in = 0;
	}
}

// fais défiler la string pour supprimer les quotes qui doivent être
// retiré pour récupérer le mot final (en prenant en compte env)

char	remove_excess_quote(char *str)
{
	int		i;
	char	in;

	i = 0;
	in = 0;
	while (str && str[i])
	{
		is_in(&in, str[i]);
		if (!in)
			i++;
		else if (str[i])
		{
			move_back(str + i);
			while (in && str[i])
			{
				is_in(&in, str[i]);
				if (in)
					i++;
			}
			move_back(str + i);
		}
	}
	return (in);
}
