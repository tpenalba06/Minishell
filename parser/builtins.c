/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:43:38 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/10 16:09:50 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// void	print_env(t_env *env, t_lexer *lexer)
// {
//     (void)lexer;
// 	t_env *tmp;
// 	tmp = env;
// 		while (tmp)
// 		{
//             if (tmp->value) {
// 			ft_putstr(tmp->name);
// 			write(STDOUT_FILENO, "=", 1);
//             ft_putstr(tmp->value);
//             write(STDOUT_FILENO, "\n", 1);
//             }
// 			tmp = tmp->next;
// 		}
// }

// void    exit_bt(t_lexer *lexer)
// {
//    if (lexer->content[0] == 'e' && lexer->content[1] == 'x' 
//         && lexer->content[2] == 'i' && lexer->content[3] == 't' 
//         && (lexer->content[4] == '\n' || lexer->content[4] == '\0'))
//     {
//         ft_putstr("exit\n");
//         exit(EXIT_SUCCESS);
//     }
// }

// void check_builtins(t_env *env, t_parsing *parsing, t_lexer *lexer, t_mini *mini)
// {
//      if (ft_strcmp(lexer->content, "unset") == 0)
//        mini->env = unset(env, lexer);
//     if (ft_strcmp(lexer->content, "export") == 0)
//         export(env, lexer, mini);
//     if (ft_strcmp(lexer->content, "env") == 0)
//         print_env(env, lexer);
//     exit_bt(lexer);
//     is_echo(parsing);
// }
