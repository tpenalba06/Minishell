/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:59:04 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/14 00:15:55 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoinps(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*sfinal;

	if (!s1 || !s2)
		return (NULL);
	sfinal = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 2);
	i = 0;
	j = 0;
	if (!sfinal)
		return (0);
	while (s1[i])
	{
		sfinal[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		sfinal[i] = s2[j];
		i++;
		j++;
	}
	sfinal[i] = '\0';
	free(s1);
	return (sfinal);
}

char	*good_path(char *str, char **cmd)
{
	char	*charfinal;
	int		i;
	char	**tabchar;
	char	*tab;

	i = 0;
	if (ft_strchr_int(cmd[0], '/') != -1 && access(cmd[0], F_OK) == 0)
		return (cmd[0]);
	tabchar = ft_split(str, ':');
	free(str);
	while (tabchar[i])
	{
		tab = ft_strjoin(tabchar[i], "/");
		charfinal = ft_strjoinps(tab, cmd[0]);
		if (access(charfinal, F_OK) == 0)
		{
			free_char_tab(tabchar);
			return (charfinal);
		}
		else
			i++;
		free(charfinal);
	}
	free_char_tab(tabchar);
	return (0);
}

char	*find_path(t_mini *mini, char **env, char **cmd)
{
	int		i;

	i = 0;
	(void)mini;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (good_path(ft_strdup(env[i] + 5), cmd));
		else
			i++;
	}
	return (0);
}
