/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:04:05 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/11 17:22:55 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_mini *mini, char **av, char **envp, int *fdpipe)
{
    int infile;
	close(fdpipe[0]);
	infile = open(av[1], O_RDONLY);
	dup2(infile, STDIN_FILENO);
	dup2(fdpipe[1], STDOUT_FILENO);
	execve(mini->cmd_processing.full_path, av, envp);
	if (execve(mini->cmd_processing.full_path, av, envp) == -1)
		printf("childERROR\n");

        //ft_error(&cmd, "Error\nexecve");
	close(fdpipe[1]);
}
/*void	parent_process(t_mini *mini, char **av, char **envp, int *fdpipe)
{
	int	fd;
	close(fdpipe[1]);
	fd = open(av[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(fdpipe[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	execve(mini->cmd_processing.full_path, av, envp);
	if (execve(mini->cmd_processing.full_path, av, envp) == -1)
		exit(printf("parentERROR\n"));
        //ft_error(&cmd, "Error\nexceve2");
	close(fdpipe[0]);
}*/


void    first_process(t_mini *mini, char **av, char **envp, int *fdpipe)
{
    int infile;
    close(fdpipe[0]);
    infile = open(av[1], O_RDONLY);
    dup2(infile, STDIN_FILENO);
    dup2(fdpipe[1], STDOUT_FILENO);
    execve(mini->cmd_processing.full_path, av, envp);
    if (execve(mini->cmd_processing.full_path, av, envp) == -1)
        printf("childERROR\n");
        //ft_error(&cmd, "Error\nexecve");
    close(fdpipe[1]);
}

void    middle_process(t_mini *mini, char **av, char **envp, int *fdpipe)
{
    close(fdpipe[0]);
    dup2(fdpipe[0], STDIN_FILENO);
    dup2(fdpipe[1], STDOUT_FILENO);
    execve(mini->cmd_processing.full_path, av, envp);
    if (execve(mini->cmd_processing.full_path, av, envp) == -1)
        printf("childERROR\n");
        //ft_error(&cmd, "Error\nexecve");
    close(fdpipe[1]);
}
void    last_process(t_mini *mini, char **av, char **envp, int *fdpipe)
{
    int fd;
    close(fdpipe[0]);
    fd = open(av[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    dup2(fdpipe[0], STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    execve(mini->cmd_processing.full_path, av, envp);
    if (execve(mini->cmd_processing.full_path, av, envp) == -1)
        exit(printf("parentERROR\n"));
        //ft_error(&cmd, "Error\nexceve2");
    close(fdpipe[0]);
}
void    pipex(t_mini *mini, char **av, char **envp)
{
    pid_t parent;
    int fdpipe[2];
    if (pipe(fdpipe) == -1)
        printf("pipeERROR\n");
        //ft_error(&cmd, "Error\npipe");
    parent = fork();
    if (parent < 0)
            printf("ERROR\n");
        //ft_error(&cmd, "Error\nfork");
    if (parent == 0)
        {
            if(mini->argg == 0)
                first_process(mini, av, envp, fdpipe);
            if(mini->argg > 0 && mini->argg < mini->countpipe)
                middle_process(mini, av, envp, fdpipe);
            if(mini->argg == mini->countpipe)
                last_process(mini, av, envp, fdpipe);
        }
    else
        waitpid(-1, NULL, 0);
}