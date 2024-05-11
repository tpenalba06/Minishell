/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:02:18 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/10 13:54:31 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_char_etoile_etoile(char **truc)
{
	int	i;

	i = -1;
	while (truc[++i])
		free(truc[i]);
	free(truc);
}

long	execute_the_line(t_command *cmd, t_tool *tool, int *heredoc_no)
{
	int				n_cmd[2];
	long			ret;
	t_ret_cmd		ret_cmd;

	ret_cmd.heredoc_no = heredoc_no;
	while (cmd && cmd->content && cmd->purpose != CMD_DELIM
		&& (cmd->purpose == VAR_ASSIGN || !cmd->content[0]))
		cmd = cmd->next;
	n_cmd[0] = count_cmds(cmd);
	n_cmd[1] = n_cmd[0];
	if (!cmd || cmd->purpose == CMD_DELIM)
		return (0);
	tool->c_env = re_char_etoile_etoilise_env(tool->env);
	ret_cmd.pid = -1;
	ret_cmd.fd = -1;
	//check_hist(cmd, tool, n_cmd[0]);
	ret = 0;
	while (cmd && n_cmd[0] && ret <= 0)
		ret = ex_loop(&cmd, tool, &ret_cmd, n_cmd);
	if (ret < 0)
		ret *= (-1);
	ret = wait_father(&ret_cmd, n_cmd[1] - n_cmd[0], ret);
	if (tool->c_env)
		free_char_etoile_etoile(tool->c_env);
	return (ret);
}