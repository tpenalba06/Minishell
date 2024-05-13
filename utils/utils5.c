/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 21:45:40 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/13 17:12:04 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_len(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n = -n;
		len ++;
	}
	while (n > 0)
	{
		len ++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	s = malloc(sizeof(char) * ((get_len(n) + 1)));
	if (!s)
		return (NULL);
	i = get_len(n);
	if (n < 0)
	{
		n = -n;
		s[0] = '-';
	}
	s[i] = '\0';
	while (n > 0)
	{
		s[i - 1] = '0' + (n % 10);
		n = n / 10;
		i--;
	}
	return (s);
}

void	free_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}