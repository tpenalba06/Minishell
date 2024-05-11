/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:12:07 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/10 18:25:15 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_word(const char *str, char c)
{
	int	i;
	int	j;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			j++;
			while (str[i] && str[i] != c)
				i++;
			continue ;
		}
		i++;
	}
	return (j);
}
int	word_len(const char *s, char c, int start)
{
	int	i;
	int	count;
	i = start;
	count = 0;
	while (s[i] && s[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}
char	*ft_getword(const char *s, char c, int start)
{
	int		i;
	int		j;
	int		len;
	char	*word;
	i = start;
	j = 0;
	len = word_len(s, c, start);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (0);
	while (s[i] && s[i] != c)
	{
		word[j++] = s[i++];
	}
	word[j] = '\0';
	return (word);
}
char	**ft_split(char const *s, char c)
{
	char	**r;
	int		i;
	int		j;
	i = 0;
	j = 0;
	if (!s)
		return (0);
	r = malloc (sizeof (char *) * (count_word (s, c) + 1));
	if (!r)
		return (0);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			r[j++] = ft_getword(s, c, i);
			i++;
		}
		while (s[i] != c && s[i])
			i++;
	}
	r[j] = 0;
	return (r);
}