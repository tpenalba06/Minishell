/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:49:02 by tpenalba          #+#    #+#             */
/*   Updated: 2024/04/27 19:09:16 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void parse_uber_command(t_lexer *lexer)
{
    t_lexer *tmp;

    tmp = lexer;

    if (tmp->token == 0 && tmp->cmds == 0)
        tmp->cmds = COMMAND;
    if(tmp->token == less_than || tmp->token == more_more || tmp->token == more_than
        || tmp->token == less_less || tmp->token == pipee)
        tmp->cmds = METACHAR;
    if(tmp->token == less_than && tmp->next)
        tmp->next->cmds = IN_FILE;
    if(tmp->token == more_than && tmp->next)
        tmp->next->cmds = OUT_FILE;
    if(tmp->token == less_less && tmp->next)
        tmp->next->cmds = HEREDOC;
    if(tmp->token == more_more && tmp->next)
        tmp->next->cmds = APPEND;
    if(tmp->token == 0 && tmp->cmds == 1 && (ft_strcmp(tmp->content, "echo") == 0
        || ft_strcmp(tmp->content, "pwd") == 0 || ft_strcmp(tmp->content, "unset") == 0
        || ft_strcmp(tmp->content, "env") == 0 || ft_strcmp(tmp->content, "export") == 0
        || ft_strcmp(tmp->content, "exit") == 0 || ft_strcmp(tmp->content, "cd") == 0)
        && (tmp->prev != NULL && tmp->prev->token == pipee))
        tmp->cmds = BUILTIN;

}

void parse_uber_first_command(t_lexer *lexer)
{
    t_lexer *tmp;

    tmp = lexer;

    if (tmp->token == 0 && tmp->cmds == 0)
        tmp->cmds = COMMAND;
    if(tmp->token == less_than || tmp->token == more_more || tmp->token == more_than
        || tmp->token == less_less || tmp->token == pipee)
        tmp->cmds = METACHAR;
    if(tmp->token == less_than && tmp->next)
        tmp->next->cmds = IN_FILE;
    if(tmp->token == more_than && tmp->next)
        tmp->next->cmds = OUT_FILE;
    if(tmp->token == less_less && tmp->next)
        tmp->next->cmds = HEREDOC;
    if(tmp->token == more_more && tmp->next)
        tmp->next->cmds = APPEND;
    if(tmp->token == 0 && tmp->cmds == 1 && (ft_strcmp(tmp->content, "echo") == 0
        || ft_strcmp(tmp->content, "pwd") == 0 || ft_strcmp(tmp->content, "unset") == 0
        || ft_strcmp(tmp->content, "env") == 0 || ft_strcmp(tmp->content, "export") == 0
        || ft_strcmp(tmp->content, "exit") == 0 || ft_strcmp(tmp->content, "cd") == 0))
        tmp->cmds = BUILTIN;

}

void    parse_cmds(t_lexer *lexer)
{
    t_lexer *tmp;

    tmp = lexer;
    parse_uber_first_command(tmp);
    while(tmp)
    {
        parse_uber_command(tmp);
        printf("{ \n string = %s \n", tmp->content);
        printf("token = %d\n", tmp->token);
        printf("cmds = %d\n } \n\n\n\n\n", tmp->cmds);
        tmp = tmp->next;
    }
}


