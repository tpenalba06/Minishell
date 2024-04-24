/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:22:23 by tpenalba          #+#    #+#             */
/*   Updated: 2024/04/24 21:30:24 by tpenalba         ###   ########.fr       */
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

int	isnameok(char *str)
{
	if(str[0]== '=')
		return(0);
	else if (there_is_equal(str))
		return(1);
	return(0);
}	

void    export(t_env *env, t_lexer *lexer, t_mini *mini)
{
    t_env   *envtmp;
   t_lexer *lextmp;
	int is_in_env = 0;

	(void)mini;
    envtmp = env;
	lextmp = lexer;
	if (lextmp->next == NULL)
		print_env_export(env);
    lextmp = lexer->next;
	while(lextmp)
	{
    	if(lextmp->cmds == 1) // on check si il y a un arg valide apres export
   		{
        	while(envtmp)
			{
        		if(ft_strcmp(createname(lextmp->content), envtmp->name) == 0) // on check si l arg = name 
        		{
					if(srch_index_c(lextmp->content, '=') != 0) // on check si il y a un egal dans l arg
					{
						envtmp->value = ft_calloc(ft_strlen(lextmp->content) + 1, sizeof(char));
						envtmp->value = changeval(lextmp->content);
						break;
					}
					is_in_env++;
					return;
				}
				envtmp = envtmp->next;
    		}
			//if(is_in_env > 0) // si on a pas croise de = mais que name existe
			//	envtmp->value = '\0';
			if(is_in_env == 0) // si name n est pas dans env
			{
				if(srch_index_c(lextmp->content, '=') != 0)
				{
					envtmp = env;
					env_add_back(mini, envnew(createname(lextmp->content), changeval(lextmp->content)));
				}
				else
					env_add_back(mini, envnew(ft_strdup(lextmp->content), NULL));
			}
		}
	//print_env_export(env);
	lextmp = lextmp->next;
	}
	//envtmp = envlast(env);
		// if(is_env_char(envtmp) == 0)
		//  	free(envtmp);
	//printf("name: -%s-\n", envlast(mini->env)->name);
	//printf("value: -%s-\n", envlast(mini->env)->value);
}
