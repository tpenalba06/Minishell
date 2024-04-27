/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:22:23 by tpenalba          #+#    #+#             */
/*   Updated: 2024/04/27 16:49:43 by tpenalba         ###   ########.fr       */
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

void    export_new_var(t_mini *mini, t_env *env, t_lexer *lexer)
{
	t_env *envtmp;
	t_lexer *lextmp;

	lextmp = lexer;
	envtmp = env;
	(void)envtmp;
	if(srch_index_c(lextmp->content, '=') != 0)
	{
		envtmp = env;
		env_add_back(mini, envnew(createname(lextmp->content), changeval(lextmp->content)));
	}
	else
		env_add_back(mini, envnew(ft_strdup(lextmp->content), NULL));
}

int	export_name_exist(t_env *env, t_lexer *lexer)
{	
	t_env *envtmp;
	t_lexer *lextmp;

	envtmp = env;
	lextmp = lexer;
	while(envtmp)
	{
        if(ft_strcmp(createname(lextmp->content), envtmp->name) == 0) // on check si l arg = name 
        {
			if(srch_index_c(lextmp->content, '=') != 0) // on check si il y a un egal dans l arg
			{
				envtmp->value = ft_calloc(ft_strlen(lextmp->content) + 1, sizeof(char));
				envtmp->value = changeval(lextmp->content);
				return(0);
			}
			return(1);
		}
		envtmp = envtmp->next;
	}
	return(-1);	
}
void    export(t_env *env, t_lexer *lexer, t_mini *mini)
{
	t_env   *envtmp;
	t_lexer *lextmp;
	int is_in_env;

	(void)mini;
	(norm(),is_in_env = 0, envtmp = env, lextmp = lexer);
	if (lextmp->next == NULL)
		print_env_export(env);
    lextmp = lexer->next;
	while(lextmp)
	{
    	if(lextmp->cmds == 1) // on check si il y a un arg valide apres export
   		{
			if(export_name_exist(envtmp, lextmp) == 1)
			{
				is_in_env++;
				return;
			}
		}
		if(is_in_env == 0)
			export_new_var(mini, envtmp, lextmp);
		lextmp = lextmp->next;
	}
}
