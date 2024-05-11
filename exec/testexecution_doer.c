/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_doer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:03:13 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/09 21:15:22 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child(t_cmd_processing *cmd, t_tool *t, char **c_env, t_ret_cmd *ret)
{
	t_tool	empty_tool;

	close(ret->pipes[0]);
	perform_redirections(cmd, ret);
	close(ret->pipes[1]);
	if (ret->fd != -1)
		close(ret->fd);
	// if (t->hist && ret->n_cmd == 1)
	// 	print_ps0(t);
	if (cmd->is_builtin)
		exit(exec_bltin(cmd, t, false));
	else
		execve(cmd->cmd_name, cmd->cmd, c_env);
	exit(0);
}

void	crt_child(t_cmd_processing *cmd, t_tool *t, t_ret_cmd *ret)
{
	ret->pid = fork();
	if (ret->pid == -1)
		perror("fork");
	else if (ret->pid == 0)
		child(cmd, t, t->c_env, ret);
	close(ret->pipes[1]);
	if (ret->fd != -1)
		close(ret->fd);
	ret->fd = dup(ret->pipes[0]);
	close(ret->pipes[0]);
	close_files(cmd->redir);
}

long	wait_father(t_ret_cmd *ret, int n_cmd, long err)
{
	int	exit_st;
	int	status;

	if (ret->fd != -1)
		close(ret->fd);
	exit_st = -1;
	status = 0;
	while (--n_cmd != -1)
	{
		if (waitpid(-1, &status, 0) == ret->pid)
			exit_st = status;
	}
	// if (g_sig_rec == SIGINT)
	// 	printfd(STDOUT_FILENO, "\n");
	// else if (g_sig_rec == SIGQUIT)
	// 	printfd(STDERR_FILENO, "Quit (core dumped)\n");
	if (exit_st == -1)
		exit_st = status;
	if (err)
		return (err);
	return (WEXITSTATUS(exit_st));
}

// void	check_hist(t_command *cmd, t_tool *tool, int n_cmd)
// {
// 	t_hist	*hist;
// 	int		n;

// 	n = 0;
// 	hist = tool->hist;
// 	if (hist && n_cmd == 1 && cmd->content
// 		&& ft_strcmp(cmd->content, "exit") == 0)
// 	{
// 		while (cmd && cmd->purpose != CMD_DELIM && cmd->purpose != DELIM)
// 		{
// 			if (cmd->purpose == COMMAND)
// 				n++;
// 			if (n > 2)
// 				return ;
// 			cmd = cmd->next;
// 		}
// 		if (tool && tool->settings.hist)
// 			write_hist(hist, tool->env);
// 		free_history(hist, true);
// 	}
// }