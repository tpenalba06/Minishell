/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:21:32 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/05 21:21:24 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_env *env, t_lexer *lexer)
{
	t_env *tmp;
	tmp = env;
	if (ft_strcmp(tmp->content, "env") == 0)
	{
		while (tmp)
		{
			ft_putstr(tmp->name);
			write(STDOUT_FILENO, "=", 1);
            ft_putstr(tmp->value);
            write(STDOUT_FILENO, "\n", 1);
			tmp = tmp->next;
		}
	}
}