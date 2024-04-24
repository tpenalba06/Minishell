/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:06:42 by tpenalba          #+#    #+#             */
/*   Updated: 2024/04/24 20:43:07 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



////////////////////////////////////////////////////
///////////////////POUR DYDY //////////////////////
//////////////////////////////////////////////////


void    redir(t_lexer *lexer, char *linepid_t pid)
{
    char *delim;
    
    pid_t   pid = fork();
    if (pid == -1) {
        printf("ERREUR");
    } else if (pid == 0) {
        // ENFANT
        fd_tmp = open("/tmp/lol.tmp.1", O_WRITE);
        signal(SIGINT, SIG_DFL);
        while (true) {
                line = readline();
                if (line == NULL) {
                        write(2, "unexpected machin truc");
                        break ;
                }
                if (line == delim) {
                        break ;
                }
                write(fd_tmp, line, ft_strlen(line));
        }
        exit(0);
    } else {
        // PARENT
        signal(SIGINT, sigint_heredoc);
        int status;
        waitpid(pid, &status, 0);

    }
}