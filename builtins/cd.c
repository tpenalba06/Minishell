/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:22:34 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/15 21:44:17 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(0), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

static char	*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*oldpwd;
	int		i;
	int		j;
	int		s_alloc;

	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->value, var, len) == 0)
		{
			s_alloc = ft_strlen(env->value) - len;
			oldpwd = malloc(sizeof(char) * s_alloc + 1);
			if (!oldpwd)
				return (NULL);
			(norm(), i = 0, j = 0);
			while (env->value[i++])
			{
				if (i > (int)len)
					oldpwd[j++] = env->value[i];
			}
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

static int	updt_oldpath(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (0);
	if (!oldpwd)
		return (0);
	if (is_in_env(env, oldpwd) == 0)
		env_add(oldpwd, env);
	ft_memdel(oldpwd);
	return (1);
}

static int	get_le_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		updt_oldpath(env);
		env_path = get_env_path(env, "HOME", 4);
		if (!env_path)
			return (0);
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD", 6);
		if (!env_path)
			ft_putendl_fd("minishell : cd: OLDPWD not set", 2);
		if (!env_path)
			return (0);
		updt_oldpath(env);
	}
	ret = chdir(env_path);
	ft_memdel(env_path);
	return (ret);
}

int	ft_cd(char **args, t_env *env)
{
	int		cd_ret;

	if (!args[1])
		return (get_le_path(0, env));
	if (ft_strcmp(args[1], "-") == 0)
		cd_ret = get_le_path(1, env);
	else
	{
		updt_oldpath(env);
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			print_error(args);
	}
	return (cd_ret);
}
