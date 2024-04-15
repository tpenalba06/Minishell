/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:13:33 by tpenalba          #+#    #+#             */
/*   Updated: 2024/04/12 18:25:04 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *t_more_more(char *str, char **list, t_parsing *parsing)
{
    list[parsing->index] = ft_calloc(3, sizeof(char));
	list[parsing->index][0] = '>';
	list[parsing->index][1] = '>';
    list[parsing->index][2] = '\0';
    parsing->index++;
    str = str + 2;
    return(str);   
}

char *t_less(char *str, char **list, t_parsing *parsing)
{

    list[parsing->index] = ft_calloc(2, sizeof(char));
	list[parsing->index][0] = '<';
	list[parsing->index][1] = '\0';
    parsing->index++;
    str = str + 1;
    return(str);
}

char *t_less_less(char *str, char **list, t_parsing *parsing)
{
    

    list[parsing->index] = ft_calloc(3, sizeof(char));
	list[parsing->index][0] = '<';
	list[parsing->index][1] = '<';
    list[parsing->index][2] = '\0';
    parsing->index++;
    str = str + 2;
    return(str);  
}

char    *fill_token(char *str, t_parsing *parsing, char **list)
{
    if((what_token(*str) == '|'))
	{
        list[parsing->index] = ft_calloc(2, sizeof(char));
	    list[parsing->index][0] = '|';
	    list[parsing->index][1] = '\0';
        parsing->index++;
        str = str + 1;
        return(str);
    }
    if((what_token(*str) == '>' && what_token(*(str + 1)) != '>'))
    {
        list[parsing->index] = ft_calloc(2, sizeof(char));
	    list[parsing->index][0] = '>';
	    list[parsing->index][1] = '\0';
        parsing->index++;
        str = str + 1;
        return(str); 
    }
    if((what_token(*str) == '>' && what_token(*(str + 1)) == '>'))
        str = t_more_more(str, list, parsing);
    if((what_token(*str)== '<' && what_token(*(str + 1)) != '<'))
        str = t_less(str, list, parsing);
    if((what_token(*str) == '<' &&  what_token(*(str + 1)) == '<'))
        str = t_less_less(str, list, parsing);
    return(str);
}
