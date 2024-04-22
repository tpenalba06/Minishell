/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:43:38 by tpenalba          #+#    #+#             */
/*   Updated: 2024/04/21 19:24:43 by tpenalba         ###   ########.fr       */
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

void    exit_bt(t_lexer *lexer)
{
   if (lexer->content[0] == 'e' && lexer->content[1] == 'x' 
        && lexer->content[2] == 'i' && lexer->content[3] == 't' 
        && (lexer->content[4] == '\n' || lexer->content[4] == '\0'))
    {
        ft_putstr("exit\n");
        exit(EXIT_SUCCESS);
    }
}

void check_builtins(t_env *env, t_lexer *lexer)
{
    print_env(env, lexer);
    exit_bt(lexer);
}