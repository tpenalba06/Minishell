/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:19:46 by tpenalba          #+#    #+#             */
/*   Updated: 2024/04/27 17:38:14 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int		nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int				ft_echo(char **args)
{
	int		i;
	int		n_option;

	i = 1;
	n_option = 0;
	if (nb_args(args) > 1)
	{
		while (args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			n_option = 1;
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
	if (n_option == 0)
		write(1, "\n", 1);
	return (1);
}

int is_echo(t_parsing *parsing)
{
    if (parsing->tab[0][0] == 'e' && parsing->tab[0][1] == 'c' 
        && parsing->tab[0][2] == 'h' && parsing->tab[0][3] == 'o' 
        && (parsing->tab[0][4] == '\n' || parsing->tab[0][4] == '\0')
        && (what_token(parsing->tab[1][0]) == 0))
        {
            if(ft_echo(parsing->tab) == 1)
                return(1);
        }
    return(0);
}
