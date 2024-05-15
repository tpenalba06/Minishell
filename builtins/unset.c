/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:22:30 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/15 21:48:55 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	free_maill(t_mini *mini, t_env *env)
{
	if (mini->env == env && env->next == NULL)
	{
		ft_memdel(mini->env->value);
		mini->env->value = NULL;
		mini->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

int	unset(char **c, t_mini *mini)
{
	t_env	*env;
	t_env	*tmp;

	env = mini->env;
	if (!(c[1]))
		return (0);
	if (ft_strncmp(c[1], env->value, env_size(env->value)) == 0)
	{
		if (env->next)
			mini->env = env->next;
		free_maill(mini, env);
		return (0);
	}
	while (env && env->next)
	{
		if (ft_strncmp(c[1], env->next->value, env_size(env->next->value)) == 0)
		{
			tmp = env->next->next;
			free_maill(mini, env->next);
			env->next = tmp;
			return (0);
		}
		env = env->next;
	}
	return (0);
}
