/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:22:23 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/14 14:51:41 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*createname(char *str)
{
	int		i;
	int		flag;
	char	*newname;

	i = 0;
	flag = 0;
	if (there_is_equal(str))
	{
		flag = srch_index_c(str, '=');
		newname = ft_calloc(flag + 1, sizeof(char));
		while (i < flag)
		{
			newname[i] = str[i];
			i++;
		}
	}
	else if (srch_index_c(str, '=') == 0)
		return (ft_strdup(str));
	return (newname);
}

void	export_new_var(t_mini *mini, t_env *env, char *cmd)
{
	(void)env;
	if (srch_index_c(cmd, '=') != 0)
		env_add_back(mini, envnew(createname(cmd), changeval(cmd)));
	else
		env_add_back(mini, envnew(ft_strdup(cmd), NULL));
}

int	export_name_exist(t_env *env, char *cmd)
{
	t_env	*envtmp;

	envtmp = env;
	while (envtmp)
	{
		if (ft_strcmp(createname(cmd), envtmp->name) == 0)
		{
			if (srch_index_c(cmd, '=') != 0)
			{
				envtmp->value = ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
				envtmp->value = changeval(cmd);
				return (0);
			}
			return (1);
		}
		envtmp = envtmp->next;
	}
	return (-1);
}

int	export(t_env *env, char **cmd, t_mini *mini)
{
	t_env	*envtmp;
	int		is_in_env;
	int		i;

	i = 1;
	(void)mini;
	(norm(), is_in_env = 0, envtmp = env);
	if (cmd[1] == NULL)
		print_env_export(env);
	while (cmd[i])
	{
		if (export_name_exist(envtmp, cmd[i]) == 0)
			is_in_env++;
		if (export_name_exist(envtmp, cmd[i]) == 1)
			is_in_env++;
		if (is_in_env == 0)
			export_new_var(mini, envtmp, cmd[i]);
		i++;
	}
	return (0);
}
