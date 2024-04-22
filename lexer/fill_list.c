/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:39:51 by tpenalba          #+#    #+#             */
/*   Updated: 2024/04/22 17:38:28 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*lstlast(t_lexer *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

t_lexer	*lstnew(void *content)
{
	t_lexer	*lst;

	lst = malloc(sizeof(t_lexer));
	if (!lst)
		return (NULL);
	lst -> content = content;
	lst -> next = NULL;
	return (lst);
}

void	lstadd_front(t_lexer *lst, t_lexer *new)
{
	new -> next = lst;
	lst = new;
}

void	lstadd_back(t_mini *mini, t_lexer *new)
{
	if (!mini->lexer)
		mini->lexer = new;
	else
		lstlast(mini->lexer)->next = new;
}

void	tokenize(t_mini *mini)
{
	t_lexer *tmp;

	tmp = mini->lexer;
	while (mini->lexer != NULL)
	{
		if (!mini->lexer->content)
			mini->lexer = mini->lexer->next;
		else if (mini->lexer->content[0] == '>' && mini->lexer->content[1] == '>')
			mini->lexer->token = more_more;
		else if (mini->lexer->content[0] == '<' && mini->lexer->content[1] == '<')
			mini->lexer->token = less_less;
		else if (mini->lexer->content[0] == '<')
			mini->lexer->token = less_than;
		else if (mini->lexer->content[0] == '>')
			mini->lexer->token = more_than;
		else if (mini->lexer->content[0] == '|')
			mini->lexer->token = pipee;
		mini->lexer = mini->lexer->next;
	}
	mini->lexer = tmp;
}
void printList (t_mini *mini)
{
	t_lexer *tmp;

	tmp = mini->lexer;
	if (tmp && tmp->token == 5)
		terror(tmp->content);
	while (tmp)
	{
		if(tmp->next)
		{
			if((tmp->token != 0 && tmp->token != 5 && tmp->next->token != 0) ) {
				printf("lol\n");
				terror(tmp->content);
			}
		}
		//remove_excess_quote(mini->lexer->content);	
	//	printf("---------------------\n");
	//	printf("element : %s\n\n", tmp->content);
		//printf("token is : %d\n\n", tmp->token);
	//	printf("---------------------\n");
		tmp = tmp->next;
	}
}

void del_first_lex(t_mini *mini, t_parsing *parsing)
{
	t_lexer *tmp;
	t_lexer *tmp2;
	tmp = mini->lexer;
	free(parsing->tab);
	while(tmp)
	{
		free(tmp->content);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	mini->lexer = tmp;
	mini->lexer = NULL;
}

void fill_lst (t_mini *mini, t_parsing *parsing)
{
	int	i;

	i = 0;
	while (parsing->tab[i])
	{
		parsing->tab[i] = change_env(parsing->tab[i], mini);
		remove_excess_quote(parsing->tab[i]);
		lstadd_back(mini, lstnew(parsing->tab[i]));
		lstlast(mini->lexer)->token = indefini;
		lstlast(mini->lexer)->cmds = undefined;
		lstlast(mini->lexer)->next = NULL;
		i++;
	}
}

