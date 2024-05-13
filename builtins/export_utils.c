/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 23:31:36 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/14 00:05:19 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr("declare -x ");
		ft_putstr(tmp->name);
		if (tmp->value == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			tmp = tmp->next;
			continue ;
		}
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, "\"", 1);
		if (tmp->value)
			ft_putstr(tmp->value);
		write(STDOUT_FILENO, "\"", 1);
		write(STDOUT_FILENO, "\n", 1);
		tmp = tmp->next;
	}
}

char	*changeval(char *str)
{
	int		i;
	char	*newval;

	i = 0;
	if (srch_index_c(str, '=') != 0)
	{
		i = srch_index_c(str, '=');
		if (i == 0)
		{
			newval = ft_calloc(1, sizeof(char));
			return (newval);
		}
		newval = ft_calloc(ft_strlen(str + i) + 1, sizeof(char));
		newval = ft_strdup(str + (i + 1));
	}
	return (newval);
}

int	there_is_equal(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}
