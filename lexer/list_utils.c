/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:18:27 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/13 23:53:31 by tpenalba         ###   ########.fr       */
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
	lst -> prev = NULL;
	return (lst);
}

void	lstadd_front(t_lexer *lst, t_lexer *new)
{
	new -> next = lst;
	lst = new;
}

void	lstadd_back(t_mini *mini, t_lexer *new)
{
	t_lexer	*temp;

	if (!mini->lexer)
		mini->lexer = new;
	else
	{
		temp = lstlast(mini->lexer);
		temp->next = new;
		new->prev = temp;
	}
}
