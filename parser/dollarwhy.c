/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   $?.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:13:41 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/15 14:52:39 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *dollarwhy(char *str)
{
	char *position;
	char *error_code;
    char *new_str;
	int len;

	position = strchr(str, '?');
	error_code = ft_itoa(g_sig_rec);
	len = ft_strlen(str) + ft_strlen(error_code);
	new_str = malloc(sizeof(char) * len - 1);
	if (position != NULL)
	{
        strncpy(new_str, str, position - str);
        new_str[len] = '\0';
        strcat(new_str, error_code);
        strcat(new_str, position + 1);
		return(new_str);
	}
	return(NULL);
}
