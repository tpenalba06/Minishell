/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:22:30 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/13 16:17:17 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char  *getname(char *str)
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
	{
		return(ft_strdup(str));
	}
	return(newname);
}

int    unset(t_env *env, char **cmd)
{
    t_env   *envtmp;
    t_env   *prev;
    char *name;
	int i;

	i = 0;
	if(cmd[1] == NULL)
		return(0) ;
    envtmp = env;
    prev = env;
    while(cmd[i])
    {
		name = getname(cmd[i]);
        while(envtmp)
        {
			if (envtmp == env && ft_strcmp(envtmp->name, name) == 0) 
			{
				free(envtmp->name);
				if (envtmp->value)
					free(envtmp->value);
				env = env->next;
				free(envtmp);
				break ;
			}
            if(ft_strcmp(name, envtmp->name) == 0)
            {
			    if(envtmp->next == NULL)
                {
                    prev->next = NULL;
                    free(envtmp);
                    envtmp = prev->next;
                    continue;
                }
                prev->next = envtmp->next;
                free(envtmp);
                envtmp = prev->next;
            }
			prev = envtmp;
            envtmp = envtmp->next;
        }
       	i++;
		envtmp = env;
    }
	return(0);
}
