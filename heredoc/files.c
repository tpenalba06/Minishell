/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:39:03 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/13 21:01:44 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	here_doc(t_lexer *lexer)
{
	int	i;
	int	ret;

	if (!lexer || !lexer->content)
		return (0);
	i = 0;
	ret = 0;
	while (lexer->next)
	{
		if (lexer->token == less_less && lexer->next)
		{
			ret = create_heredoc(i, lexer->next);
			if (ret)
				return (ret);
			i++;
		}
		lexer = lexer->next;
	}
	if (lexer->token == less_less && lexer->next)
		ret = create_heredoc(i, lexer->next);
	return (ret);
}
