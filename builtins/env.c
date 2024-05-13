/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:21:32 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/13 23:29:29 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr(tmp->name);
			write(STDOUT_FILENO, "=", 1);
			ft_putstr(tmp->value);
			write(STDOUT_FILENO, "\n", 1);
			tmp = tmp->next;
		}
	}
	return (0);
}
