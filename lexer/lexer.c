/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:15:34 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/03 17:14:36 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void terror(char *str)
{
	printf("syntax error near unexpected token `%s' \n", str);
	rl_on_new_line();
}

void check_syntax(t_lexer *lexer)
{
	t_lexer *tmp;

	tmp = lexer;
	if(tmp == NULL)
		return;
	if(tmp->content[0] == '\0' || tmp->content[0] == '\n')
		return(terror(tmp->content));
	if(tmp->token == pipee)
		return(terror(tmp->content));
	if(tmp->content[0] == '\0' || tmp->content[0] == '\n')
		return(terror(tmp->content));
	while (tmp)
	{
		if(tmp->next)
		{
			if((tmp->token != 0 && tmp->token != 5 && tmp->next->token != 0) ) 
				return(terror(tmp->content));
		}
		if(tmp->token != 0 && tmp->next == NULL)
			return(terror(tmp->content));
		tmp = tmp->next;
	}
	tmp = lexer;
}

void	lexluthor(t_mini *mini, t_parsing *parsing)
{
	parsing->tab = split_line(parsing->input, *parsing);
	fill_lst(mini, parsing);
	tokenize(mini);
	check_syntax(mini->lexer);
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
