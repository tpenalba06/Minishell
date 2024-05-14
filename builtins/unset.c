/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:22:30 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/14 15:11:59 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*getname(char *str)
// {
// 	int		i;
// 	int		flag;
// 	char	*newname;

// 	i = 0;
// 	flag = 0;
// 	if (there_is_equal(str))
// 	{
// 		flag = srch_index_c(str, '=');
// 		newname = ft_calloc(flag + 1, sizeof(char));
// 		while (i < flag)
// 		{
// 			newname[i] = str[i];
// 			i++;
// 		}
// 	}
// 	else if (srch_index_c(str, '=') == 0)
// 	{
// 		return (ft_strdup(str));
// 	}
// 	return (newname);
// }

// int	unset_3(t_env *envtmp, t_env *env, char *name)
// {
// 	if (envtmp == env && ft_strcmp(envtmp->name, name) == 0)
// 	{
// 		free(envtmp->name);
// 		if (envtmp->value)
// 			free(envtmp->value);
// 		env = env->next;
// 		free(envtmp);
// 		return (1);
// 	}
// 	return (0);
// }

// int	unset_2(t_env *envtmp, t_env *prev)
// {
// 	if (envtmp == NULL)
// 	{
// 		prev->next = NULL;
// 		free(envtmp);
// 		envtmp = prev->next;
// 		return (1);
// 	}
// 	return (0);
// }

// void	unset_check(t_env *envtmp, t_env *env, char **cmd, t_env *prev)
// {
// 	int			i;
// 	char		*name;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		name = getname(cmd[i]);
// 		while (envtmp->next)
// 		{
// 			if (unset_3(envtmp, env, name) == 1)
// 				break ;
// 			if (ft_strcmp(name, envtmp->name) == 0)
// 			{
// 				if (unset_2(envtmp, prev) == 1)
// 					continue ;
// 				prev->next = envtmp->next;
// 				free(envtmp);
// 				envtmp = prev->next;
// 			}
// 			prev = envtmp;
// 			envtmp = envtmp->next;
// 		}
// 		i++;
// 		envtmp = env;
// 	}
// }

// int	unset(t_env *env, char **cmd)
// {
// 	t_env	*envtmp;
// 	t_env	*prev;

// 	if (cmd[1] == NULL)
// 		return (0);
// 	(norm(), envtmp = env, prev = env);
// 	unset_check(envtmp, env, cmd, prev);
// 	return (0);
// }

static size_t	env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	free_node(t_mini *mini, t_env *env)
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

int	unset(char **a, t_mini *mini)
{
	t_env	*env;
	t_env	*tmp;

	env = mini->env;
	if (!(a[1]))
		return (0);
	if (ft_strncmp(a[1], env->value, env_size(env->value)) == 0)
	{
		if (env->next)
			mini->env = env->next;
		free_node(mini, env);
		return (0);
	}
	while (env && env->next)
	{
		if (ft_strncmp(a[1], env->next->value, env_size(env->next->value)) == 0)
		{
			tmp = env->next->next;
			free_node(mini, env->next);
			env->next = tmp;
			return (0);
		}
		env = env->next;
	}
	return (0);
}
