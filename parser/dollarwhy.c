/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarwhy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:13:41 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/15 21:55:14 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dollarwhy(t_mini *mini, char *str)
{
	char	*position;
	char	*error_code;
	char	*new_str;
	int		len;

	position = strchr(str, '$');
	error_code = ft_itoa(mini->ret);
	len = ft_strlen(str) + ft_strlen(error_code);
	if (position != NULL)
	{
		new_str = ft_calloc(len -1, sizeof(char));
		strncpy(new_str, str, position - str);
		new_str[len] = '\0';
		strcat(new_str, error_code);
		strcat(new_str, position + 2);
		return (new_str);
	}
	return (NULL);
}
