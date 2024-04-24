/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:22:30 by tpenalba          #+#    #+#             */
/*   Updated: 2024/04/24 22:00:20 by tpenalba         ###   ########.fr       */
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

t_env    *unset(t_env *env, t_lexer *lexer)
{
    t_lexer *lextmp;
    t_env   *envtmp;
    t_env   *prev;
    char *name;

	if(lexer->next == NULL)
		return(env) ;
    envtmp = env;
    lextmp = lexer->next;
    prev = env;

    while(lextmp)
    {
		name = getname(lextmp->content);
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
        lextmp = lextmp->next;
		envtmp = env;
    }
	return(env);
}
