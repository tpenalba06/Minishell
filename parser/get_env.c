#include "../minishell.h"

char srch_index_c(char *str, char c)
{
    int i;
    i = 0;
    while(str[i])
    {
        if(str[i] == c)
            return(i);
        i++;
    }
    return(0);
}

char **split_env(char *str, char c)
{
    int i;
    int j;
    int flag;
    char **env;

    flag = 0;
    i = 0;
    j = 0;
    flag = srch_index_c(str, c);
    env = ft_calloc(3, sizeof(char *));
    env[0] = ft_calloc((flag + 1), sizeof(char));
    env[1] = ft_calloc((strlen(str) - flag + 1), sizeof(char));
    while(i < flag)
        env[0][j++] = str[i++];
    env[0][j] = '\0';
    j = 0;
    i++;
    while(str[i])
        env[1][j++] = str[i++];
    env[1][j] = '\0';
    env[2] = NULL;
    return(env);
}

t_env	*envlast(t_env *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	env_add_back(t_mini *mini, t_env *new)
{
	if (!mini->env)
		mini->env = new;
	else
		envlast(mini->env)->next = new;
}
t_env	*envnew(char *name, char *value)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst -> name = name;
    lst->value = value;
	lst -> next = NULL;
	return (lst);
}
void get_env(t_env *env, t_mini *mini)
{
    t_env *tmp;
    char **str;
    int i;

    i = 0;
    tmp = env;
    while(mini->charenv[i])
    {
        str = split_env(mini->charenv[i], '=');
        tmp = envnew(str[0], str[1]);
        env_add_back(mini, tmp);
        i++;
    }
    tmp = mini->env;
    while (tmp)
    {
           tmp = tmp->next;
    }
}

static void	swap_content(t_env *env, t_env *next)
{
	char	*yo_name;
	char	*yo_value;
	//bool	yo_is_exp;
	yo_name = env->name;
	yo_value = env->value;
	//yo_is_exp = env->is_exported;
	env->name = next->name;
	env->value = next->value;
	//env->is_exported = next->is_exported;
	next->name = yo_name;
	next->value = yo_value;
	//next->is_exported = yo_is_exp;
}
void	sort_env(t_env *head)
{
	int		swapped;
	t_env	*ptr;
	swapped = 1;
	while (swapped == 1)
	{
		swapped = 0;
		ptr = head;
		while (ptr && ptr->next)
		{
			if (ft_strcmp(ptr->name, ptr->next->name) > 0)
			{
				swap_content(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
	}
}