/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:22:20 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/14 00:36:31 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	mini_exit(t_mini *mini, char **cmd)
{
	// mini->exit = 1;
	// ft_putstr_fd("exit ", STDERR);
	// //cmd[1] ? ft_putendl_fd("", STDERR) : ft_putendl_fd("💚", STDERR);
	// if (cmd[1] && cmd[2])
	// {
	// 	mini->ret = 1;
	// 	ft_putendl_fd("minishell: exit: too many arguments", STDERR);
	// }
	// else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	// {
	// 	mini->ret = 255;
	// 	ft_putstr_fd("minishell: exit: ", STDERR);
	// 	ft_putstr_fd(cmd[1], STDERR);
	// 	ft_putendl_fd(": numeric argument required", STDERR);
	// }
	// else if (cmd[1])
	// 	mini->ret = ft_atoi(cmd[1]);
	// else
	// 	mini->ret = 0;
}
