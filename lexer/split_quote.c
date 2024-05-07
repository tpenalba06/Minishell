/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:14:24 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/05 22:03:17 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



char	update_quote(char quote, char cur)
{
	if (!quote && (cur == '\'' || cur == '"'))
		return (cur);
	else if (quote && cur == quote)
		return (0);
	return (quote);
}

static int	iterate(char *quote, char cur)
{
	*quote = update_quote(*quote, cur);
	return (1);
}

static int	count(char *str)
{
	int		i;
	int		count;
	char	quote;

	(norm(),i = 0, quote = 0, count = 0);
	while (str[i])
	{
		if (((str[i] != ' ' &&(what_token(str[i]) == 0)) || quote) && str[i])
		{
			while (((str[i] != ' ' && (what_token(str[i]) == 0))|| quote) && str[i])
			{
				i++;
				iterate(&quote, str[i]);
			}
			count++;
		}
		while (str[i] == ' ' && !quote && str[i])
			i += iterate(&quote, str[i]);
		if(what_token(str[i]) != 0)
		{
			count++;
			i++;
		}
	}
	return (count);
}

static char	*cut_word(char *line)
{
	int		i;
	char	quote;
	char	*word;
	i = 0;
	quote = 0;
	while (((line[i] != ' ' && (what_token(line[i]) == 0)) || quote) && line[i])
		i += iterate(&quote, line[i]);
	word = ft_calloc(i + 1, sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	quote = 0;
	while (((line[i] != ' ' && (what_token(line[i]) == 0)) || quote)  && line[i] != '\0')
	{
		word[i] = line[i];
		iterate(&quote, line[i]);
		i++;
	}
	return (word);
}


char	**split_line(char *str, t_parsing parsing)
{
	char	**list;
	char	quote;

	(norm(),parsing.index = 0, quote = 0);
	list = ft_calloc((count(str) + 10000), sizeof(char *));
	if (list == NULL)
		return (NULL);
	while (*str)
	{
		if (((*str != ' ' && (what_token(*str) == 0)) || quote) && *str)
		{
			list[parsing.index] = cut_word(str);
			if (!list[parsing.index])
				return (NULL);
			parsing.index++;
			while (((*str != ' ' && (what_token(*str) == 0)) || quote) && *str)
				str += iterate(&quote, *str);
		}
		str = fill_token(str, &parsing, list);
		while (*str == ' ' && !quote && *str)
			str += iterate(&quote, *str);
	}
	if(update_quote(quote, *str) != 0)
		rl_on_new_line();
	return (list);
}


