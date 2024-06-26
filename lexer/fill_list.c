/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:39:51 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/15 21:55:25 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_quotes(void)
{
	rl_on_new_line();
}

static void	unlink_here(int n)
{
	char	*lol;

	lol = ft_strjoin("/tmp/shell_here", ft_itoa(n));
	if (!lol)
		return ;
	unlink(lol);
	free(lol);
}

void	del_first_lex(t_mini *mini, t_parsing *parsing)
{
	t_lexer	*tmp;
	t_lexer	*tmp2;
	int		here;
	int		i;

	i = 0;
	here = 0;
	tmp = mini->lexer;
	free(parsing->tab);
	while (tmp)
	{
		if (tmp->cmds == HEREDOC)
		{
			unlink_here(here);
			here++;
		}
		tmp2 = tmp->next;
		free(tmp);
		i++;
		tmp = tmp2;
	}
	mini->lexer = tmp;
	mini->lexer = NULL;
}

void	fill_lst(t_mini *mini, t_parsing *parsing)
{
	int	i;

	i = 0;
	while (parsing->tab[i])
	{
		lstadd_back(mini, lstnew(parsing->tab[i]));
		lstlast(mini->lexer)->token = indefini;
		lstlast(mini->lexer)->cmds = undefined;
		lstlast(mini->lexer)->next = NULL;
		i++;
	}
}

// void printList (t_mini *mini)
// {
// 	t_lexer *tmp;

// 	tmp = mini->lexer;
// 	if (tmp && tmp->token == 5)
// 		terror(tmp->content, mini->lexer);
// 	while (tmp)
// 	{
// 		if (tmp->next)
// 		{
// 			if ((tmp->token != 0 && tmp->token != 5 && tmp->next->token != 0))
// 			{
// 				printf("lol\n");
// 				terror(tmp->content, mini->lexer);
// 			}
// 		}
// 		printf("---------------------\n");
// 		printf("element : %s\n", tmp->content);
// 		printf("token is : %d\n", tmp->token);
// 		printf("---------------------\n");
// 		tmp = tmp->next;
// 	}
// }