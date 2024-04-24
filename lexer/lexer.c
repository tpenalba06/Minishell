/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:15:34 by tpenalba          #+#    #+#             */
/*   Updated: 2024/04/23 13:09:02 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	move_back(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}

void	is_in(char *in, char c)
{
	if (c == '"' || c == '\'')
	{
		if (*in == 0)
			*in = c;
		else if (*in == c)
			*in = 0;
	}
}

// fais défiler la string pour supprimer les quotes qui doivent être
// retiré pour récupérer le mot final (en prenant en compte env)

char	remove_excess_quote(char *str)
{
	int		i;
	char	in;

	i = 0;
	in = 0;
	while (str && str[i])
	{
		is_in(&in, str[i]);
		if (!in)
			i++;
		else if (str[i])
		{
			move_back(str + i);
			while (in && str[i])
			{
				is_in(&in, str[i]);
				if (in)
					i++;
			}
			move_back(str + i);
		}
	}
	return (in);
}

void	lexluthor(t_mini *mini, t_parsing *parsing)
{
	parsing->tab = split_line(parsing->input, *parsing);
	fill_lst(mini, parsing);
	tokenize(mini);
	printList(mini);

}
void terror(char *str)
{
	printf("syntax error near unexpected token `%s' \n", str);
	rl_on_new_line();
}


//gerer les pipes mm qd ils sont colles avancer 1 char par 1 char
//les tokens sont separateurs aussi
/*
premiere etape : prompt qui reste en attente d une commande / input de l utilisateur 
lexer :
decouper toutes les entrees et gerer les exceptions, on part depuis une sorte de split 
modifie qui va prendre en caractere separateur les " et ' on a vu avec le test d echo
qu il faut rentrer dans un state quote des qu on en rencontre un que ce soit un " ou un '
tout parser avec les espaces (sauf si il y a des quotes)
une fois les input tries et recuperes on fill une liste chainee struct mini 

dissocier commandes et input type text : les quotes servent seulement a pouvoir ecrire des commandes type :
| ou echo ou cat, etc .... sans utiliser leurs actions 
les guillemets doubles permettent l'expansion des variables et l'interprétation de caractères spéciaux, 
tandis que les guillemets simples préservent 
littéralement le texte à l'intérieur sans expansion des variables ni interprétation de caractères spéciaux, 
à l'exception de l'apostrophe elle-même.

commande puis arg puis token

*/
