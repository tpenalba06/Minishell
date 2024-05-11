/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:29:42 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/11 14:46:45 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_tab(char **str)
{
    int i;
    i = -1;
    while (str[++i])
        free(str[i]);
    free(str);
}

t_lexer    *go_next_cmd(t_lexer *lex, t_mini *mini)
{
    while(lex)
    {
        if(lex->token == pipee || lex == NULL)
        {
            lex = lex->next;
            free_tab(mini->cmd_processing.cmd);
            return(lex);
        }
        lex = lex->next;
    }
    return(NULL);
}

unsigned long		count_arg(t_lexer *lex)
{
	unsigned long arg;
    arg = 0;
	while(lex && lex->token != pipee)
	{
		arg += (lex->cmds == COMMAND || lex->cmds == BUILTIN);
		lex = lex->next;
	}
	return(arg);	
}

int		count_pipes(t_mini *mini)
{
	t_lexer *tmp;

	tmp =mini->lexer;
	int pipe;
	while(tmp)
	{
		if(tmp->token == pipee)
			pipe++;
		tmp = tmp->next;
	}
	return(pipe);	
}

static void handle_redir(t_lexer *lex, t_redir *redir) {
    if (lex->cmds == IN_FILE || lex->cmds == HEREDOC) {
        if (redir->in != -1) {
            close(redir->in);
            redir->in = -1;
        }
        if (lex->cmds == IN_FILE)
            redir->in = open(lex->content, O_RDONLY);
    }
    else {
        if (redir->out != -1) {
            close(redir->out);
            redir->out = -1;
        }
        if (lex->cmds == OUT_FILE)
            redir->out = open(lex->content, O_CREAT | O_WRONLY);
        else
            redir->out = open(lex->content, O_CREAT | O_WRONLY | O_APPEND);
    }
}

 char **parse_into_char(t_lexer *lex, t_redir *redir, bool *is_builtin)
 {
    unsigned long nb_arg = count_arg(lex);
    char    **cmd = ft_calloc(nb_arg, sizeof(char *));
    unsigned long index = 0;
    bool    first = true;
    while (cmd && lex && lex->token != pipee)
    {
        if (lex->cmds == COMMAND || lex->cmds == BUILTIN) {
            if (first && lex->cmds == BUILTIN)
                *is_builtin = true;
            cmd[index] = lex->content;
            index++;
            first = false;
        } else if (lex->cmds >= IN_FILE && lex->cmds <= APPEND) {
            handle_redir(lex, redir);
        }
        lex = lex->next;
    }
    cmd[index] = '\0';
    return (cmd);
}

void	executor(t_mini *mini)
{
	//unsigned long n_cmd = count_pipes(mini) + 1;
	mini->charenv = re_char_etoile_etoilise_env(mini->env);
    // for (char **bonjour = mini->charenv; *bonjour; bonjour++) {
    //     printf("%s\n", *bonjour);
    // }
    int i ;
    t_lexer *lex_tmp = mini->lexer;
	while (lex_tmp != NULL) 
	{
        i = 0;
		mini->cmd_processing.redir.in = -1;
		mini->cmd_processing.redir.out = -1;
        mini->cmd_processing.is_builtin = false;
		//if (n_cmd > 1) { pipe(pipe); }
		mini->cmd_processing.cmd = parse_into_char(lex_tmp, &(mini->cmd_processing.redir), &(mini->cmd_processing.is_builtin));
        printf("%s\n", mini->cmd_processing.cmd[0]);
        if (!mini->cmd_processing.is_builtin) 
		{
            if((mini->cmd_processing.full_path = find_path(mini, mini->charenv, mini->cmd_processing.cmd)) == NULL)
            {
                ft_putstr_fd("command not found\n", STDOUT_FILENO);
                lex_tmp = go_next_cmd(lex_tmp, mini);
                i = 1;
			} // = rechercher dans le path 
            //printf("%s\n", mini->cmd_processing.full_path);
        }
        // if (ft_strcmp("export", lex_tmp->content) == 0)
		// 	export(mini->env, mini->cmd_processing.cmd, mini);
        // if (ft_strcmp("unset", lex_tmp->content) == 0)
		// 	unset(mini->env, mini->cmd_processing.cmd);
		
        //pipex(mini, mini->cmd_processing.cmd, mini->charenv);
        /*
		exec_machin() 3
        fork() MAIS QUE SI PAS BUILTIN OU PIPE
        Si builtin tout seul, dans parent
        Si builtin pipe ou cmd pas builtin, fork
        Pere : fork, recupere le pipe avec dup()
        Enfant : utilise le pipe et le fd s'il existe puis execve / builtin */
		if(i == 0)
                lex_tmp = go_next_cmd(lex_tmp, mini); 
	}
	//father_waiting_for_all_children() 4
}


char	*ft_strjoinps(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*sfinal;
	sfinal = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 2);
	i = 0;
	j = 0;
	if (!sfinal)
		return (0);
	while (s1[i])
	{
		sfinal[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		sfinal[i] = s2[j];
		i++;
		j++;
	}
	sfinal[i] = '\0';
	free(s1);
	return (sfinal);
}

char	*good_path(char *str, char **cmd, t_path *path)
{
	char	*charfinal;
	int		i;
    char **tabchar;
    char *tab;

    (void)path;
	if (access(cmd[0], R_OK) == 0)
		return (cmd[0]);
	else
	{
		i = 0;
		tabchar = ft_split(str, ':');
		while (tabchar[i])
		{
			tab = ft_strjoin(tabchar[i], "/");
			charfinal = ft_strjoinps(tab, cmd[0]);
			if (access(charfinal, R_OK) == 0)
			{
				free_tab(tabchar);
				return (charfinal);
			}
			else
				i++;
			free(charfinal);
		}
		free_tab(tabchar);
	}
	return (0);
}

char	*find_path(t_mini *mini, char **env, char **cmd)
{
	int		i;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5)){
            return(good_path(ft_strdup(env[i] + 5), cmd , mini->path));
        }
        else
			i++;
	}
	return (0);
}
// avancer dans t lexer 
// delim = | soit NULL