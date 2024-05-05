/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:29:42 by tpenalba          #+#    #+#             */
/*   Updated: 2024/04/29 19:54:59 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int str_to_fd(char *str)
{
    int pid;
    int fd[2];
    int new_fd;

    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        ft_putstr_fd(str, fd[1]);
        close(fd[1]);
        exit(0);
    }
    close(fd[1]);
    waitpid(pid, NULL, 0);
    new_fd = dup(fd[0]);
    close(fd[0]);
    return (new_fd);
}

void	executor(t_mini *mini)
{
	if (handle_heredocs(mini) == ERROR)
		return ;
	if (!mini->cmd[0]->next)
	{
		if (check_input_list(mini->cmd[0]) == NO_ERROR)
			simple_command(mini, mini->cmd[0]);
	}
	else
	{
		multiple_commands(mini);
	}
	free_after_execution(mini);
	return ;
}