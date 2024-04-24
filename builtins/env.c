/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:21:32 by tpenalba          #+#    #+#             */
/*   Updated: 2024/04/24 17:02:28 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_env *env, t_lexer *lexer)
{
	t_env *tmp;
	tmp = env;
	if (lexer->content[0] == 'e' && lexer->content[1] == 'n' 
        && lexer->content[2] == 'v' && (lexer->content[3] == '\n' 
        || lexer->content[3] == '\0'))
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