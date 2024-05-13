/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:17:13 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/13 19:45:37 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char srch_index_c(char *str, char c)
{
    int i;
    i = 0;
    while(str[i])
    {
        if(str[i] == c)
            return(i);
        i++;
    }
    return(0);
}


t_env	*envlast(t_env *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	env_add_back(t_mini *mini, t_env *new)
{
	if (!mini->env)
		mini->env = new;
	else
		envlast(mini->env)->next = new;
}

t_env	*envnew(char *name, char *value)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->name = name;
    lst->value = value;
	lst->next = NULL;
	
	return (lst);
}
