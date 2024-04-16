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
t_env	*envnew(void *name, void *value)
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
        printf("l env name : [%s] = l env value [%s]\n\n", tmp->name, tmp->value);
        tmp = tmp->next;
        i++;
    }
}