/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkdollz.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:03:23 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/15 21:52:23 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*keep_name(char *str)
{
	int		i;
	int		j;
	char	*name;

	i = 1;
	j = 0;
	while (is_env_char(str[i]))
		i++;
	name = ft_calloc(i + 1, sizeof(char));
	i = 1;
	while (is_env_char(str[i]))
	{
		name[j] = str[i];
		i++;
		j++;
	}
	return (name);
}

char	*name_to_value(char *name, t_env *env)
{
	t_env	*tmp;
	char	*value;

	value = NULL;
	tmp = env;
	while (tmp)
	{
		if (strcmp(name, tmp->name) == 0)
		{
			value = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	if (value == NULL)
	{
		value = ft_calloc(2, sizeof(char));
	}
	return (value);
}

int	one_dollar(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"' && str[i] != '$')
			count++;
		i++;
	}
	if (count > 0)
		return (0);
	return (1);
}

char	*change_env2(t_mini *mini, char *str, t_dollar *dollar, char *in)
{
	is_in((*&in), str[dollar->i]);
	while (str[dollar->i])
	{
		if (str[dollar->i] == '$' && str[dollar->i + 1] == '?')
		{
			str = dollarwhy(mini, str);
			dollar->i = 0;
		}
		if (str[dollar->i] == '$' && *in != '\'')
		{
			dollar->name = keep_name(str + dollar->i);
			dollar->value = name_to_value(dollar->name, mini->env);
			str[dollar->i] = '\0';
			dollar->i++;
			while (is_env_char(str[dollar->i]))
				dollar->i++;
			dollar->end = str + dollar->i;
			str = ft_strjoin(str, dollar->value);
			str = ft_strjoin(str, dollar->end);
			dollar->i = -1;
		}
		dollar->i++;
		is_in(*(&in), str[dollar->i]);
	}
	return (str);
}

char	*change_env(char *str, t_mini *mini)
{
	char		in;
	t_dollar	dollar;

	(norm(), dollar.i = 0, in = 0);
	if (one_dollar(str) == 1)
		return (str);
	str = change_env2(mini, str, &dollar, &in);
	return (str);
}
