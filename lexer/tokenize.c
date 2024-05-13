/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:13:33 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/14 00:26:23 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*t_more_more(char *str, char **list, t_parsing *parsing)
{
	list[parsing->index] = ft_calloc(3, sizeof(char));
	list[parsing->index][0] = '>';
	list[parsing->index][1] = '>';
	list[parsing->index][2] = '\0';
	parsing->index++;
	str = str + 2;
	return (str);
}

char	*t_less(char *str, char **list, t_parsing *parsing)
{
	list[parsing->index] = ft_calloc(2, sizeof(char));
	list[parsing->index][0] = '<';
	list[parsing->index][1] = '\0';
	parsing->index++;
	str = str + 1;
	return (str);
}

char	*t_less_less(char *str, char **list, t_parsing *parsing)
{
	list[parsing->index] = ft_calloc(3, sizeof(char));
	list[parsing->index][0] = '<';
	list[parsing->index][1] = '<';
	list[parsing->index][2] = '\0';
	parsing->index++;
	str = str + 2;
	return (str);
}

char	*fill_token(char *str, t_parsing *parsing, char **list)
{
	if ((what_token(*str) == '|'))
	{
		list[parsing->index] = ft_calloc(2, sizeof(char));
		list[parsing->index][0] = '|';
		list[parsing->index][1] = '\0';
		parsing->index++;
		str = str + 1;
		return (str);
	}
	if ((what_token(*str) == '>' && what_token(*(str + 1)) != '>'))
	{
		list[parsing->index] = ft_calloc(2, sizeof(char));
		list[parsing->index][0] = '>';
		list[parsing->index][1] = '\0';
		parsing->index++;
		str = str + 1;
		return (str);
	}
	if ((what_token(*str) == '>' && what_token(*(str + 1)) == '>'))
		str = t_more_more(str, list, parsing);
	if ((what_token(*str) == '<' && what_token(*(str + 1)) != '<'))
		str = t_less(str, list, parsing);
	if ((what_token(*str) == '<' && what_token(*(str + 1)) == '<'))
		str = t_less_less(str, list, parsing);
	return (str);
}

void	tokenize(t_mini *mini)
{
	t_lexer	*tmp;

	tmp = mini->lexer;
	while (mini->lexer != NULL)
	{
		if (!mini->lexer->content)
			mini->lexer = mini->lexer->next;
		else if (mini->lexer->content[0] == '>'
			&& mini->lexer->content[1] == '>'
			&& mini->lexer->content[3] == '\0')
			mini->lexer->token = more_more;
		else if (mini->lexer->content[0] == '<'
			&& mini->lexer->content[1] == '<')
			mini->lexer->token = less_less;
		else if (mini->lexer->content[0] == '<')
			mini->lexer->token = less_than;
		else if (mini->lexer->content[0] == '>')
			mini->lexer->token = more_than;
		else if (mini->lexer->content[0] == '|')
			mini->lexer->token = pipee;
		mini->lexer = mini->lexer->next;
	}
	mini->lexer = tmp;
}
