#include "../minishell.h"

int is_env_char(char c)
{
    if ((c >= 'A' && c <= 'Z' ) || (c >= '0' && c <= '9') || c == '_'
        || (c >= 'a' && c <= 'z'))
    {    
        return(1);
    }
    else
        return (0);
}

char    *keep_name(char *str)
{
    int i;
    int j;
    char *name;
    i = 1;
    j = 0;
 
    while(is_env_char(str[i]))
        i++;
    name = ft_calloc(i + 1, sizeof(char));
    i = 1;
    while(is_env_char(str[i]))
    {
        name[j] = str[i];
        i++;
        j++;
    }
    return (name);
}

char *name_to_value(char *name, t_env *env)
{
    t_env *tmp;
    char *value;

    value = NULL;
    tmp = env;

    while (tmp)
    {
        if (strcmp(name, tmp->name) == 0)
        {
            value = ft_strdup(tmp->value);
            break;
        }
        tmp = tmp->next;
    }
    if(value == NULL)
    {
        value = ft_calloc(2, sizeof(char));
    }
    return (value);
}


char    *change_env(char *str, t_mini *mini)
{
    char    *name;
    char    *value;
    char    *end;
    int        i;
    char    in;

    i = 0;
    in = 0;
    printf("str: -%s-\n", str);
    is_in(&in, str[i]);
    while(str[i])
    {
        if (str[i] == '$' && in != '\'')
        {
            name = keep_name(str + i);
            value = name_to_value(name, mini->env);
            str[i] = '\0';
            i++;
            while (is_env_char(str[i]))
                i++;
            end = str + i;
            str = ft_strjoin(str, value);
            str = ft_strjoin(str, end);
            i = -1;
        }
        is_in(&in, str[i]);
        i++;
    }
    printf("newstr: -%s-\n", str);
    return(str);
}
