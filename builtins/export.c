/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:22:23 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/13 19:42:14 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env_export(t_env *env)
{
	t_env *tmp;
	tmp = env;

		while (tmp)
		{
			ft_putstr("declare -x ");
			ft_putstr(tmp->name);
			if (tmp->value == NULL) 
			{
				write(STDOUT_FILENO, "\n", 1);
				tmp = tmp->next;
				continue ;
			}
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, "\"", 1);
            ft_putstr(tmp->value);
			write(STDOUT_FILENO, "\"", 1);
            write(STDOUT_FILENO, "\n", 1);
			tmp = tmp->next;
		}
}

char  *changeval(char *str)
{
	int i = 0;
	char *newval;

	if (srch_index_c(str, '=') != 0)
	{
		i = srch_index_c(str, '=');
		if(i == 0)
		{
			newval = ft_calloc(1, sizeof(char));
			return(newval);
		}
		newval = ft_calloc(ft_strlen(str + i) + 1, sizeof(char));
		newval = ft_strdup(str + (i + 1));
	}
	return(newval);
}

int	there_is_equal(char *str)
{
	while(*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

char  *createname(char *str)
{
	int i = 0;
	int flag = 0;
	char *newname;
	if (there_is_equal(str))
	{
		flag = srch_index_c(str, '=');
		newname = ft_calloc(flag + 1, sizeof(char));
		while(i < flag)
		{
			newname[i] = str[i];
			i++;
		}	
	}
	else if (srch_index_c(str, '=') == 0)
		return(ft_strdup(str));
	return(newname);
}

void    export_new_var(t_mini *mini, t_env *env, char *cmd)
{
	t_env *envtmp;

	envtmp = env;
	(void)envtmp;
	if(srch_index_c(cmd, '=') != 0)
	{
		envtmp = env;
		env_add_back(mini, envnew(createname(cmd), changeval(cmd)));
	}
	else
	{
		env_add_back(mini, envnew(ft_strdup(cmd), NULL));
	}
}

int	export_name_exist(t_env *env, char *cmd)
{	
	t_env *envtmp;

	envtmp = env;
	while(envtmp)
	{
        if(ft_strcmp(createname(cmd), envtmp->name) == 0) // on check si l arg = name 
        {
			if(srch_index_c(cmd, '=') != 0) // on check si il y a un egal dans l arg
			{
				envtmp->value = ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
				envtmp->value = changeval(cmd);
				return(0);
			}
			return(1);
		}
		envtmp = envtmp->next;
	}
	return(-1);	
}

int    export(t_env *env, char **cmd, t_mini *mini)
{
	t_env   *envtmp;
 	
	int is_in_env;

	int i = 1;
	(void)mini;
	(norm(),is_in_env = 0, envtmp = env);
	if (cmd[1] == NULL)
		print_env_export(env);
	while(cmd[i])
	{
    	//if(cmd) // on check si il y a un arg valide apres export
   		//{
			if(export_name_exist(envtmp, cmd[i]) == 1)
			{
				is_in_env++;
				return (0);
			}
		//}
		if(is_in_env == 0)
			export_new_var(mini, envtmp, cmd[i]);
		i++;
	}
	return(0);
}
