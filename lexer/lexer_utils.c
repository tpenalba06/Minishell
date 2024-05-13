/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:22:21 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/13 21:34:33 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm(void)
{
}

char	what_token(char c)
{
	if (c == '|')
		return (c);
	if (c == '<')
		return (c);
	if (c == '>')
		return (c);
	return (0);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("element numero %d du tab %s\n", i, tab[i]);
		i++;
	}
	return ;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	str = malloc(sizeof(*str) * (count * size));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}
