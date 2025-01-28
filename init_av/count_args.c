/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:47:39 by hduflos           #+#    #+#             */
/*   Updated: 2025/01/26 10:26:11 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_metachar(int c)
{
	return (c == '|' || c == '>' || c == '<');
}


int	logic_count_args(char *s, int *i, char *quote)
{
	if (s[*i] == '\'' || s[*i] == '"') // Détecter le début d'un guillemet
	{
		*quote = s[*i]; // Enregistrer le type de guillemet
		(*i)++;
		// Parcourir jusqu'à la fin des guillemets ou de la chaîne
		while (s[*i] != *quote && s[*i] != '\0')
			(*i)++;
		// Si fin de chaîne atteinte sans guillemet fermant, retourner une erreur
		if (s[*i] == '\0')
			return (-2);

		(*i)++; // Avancer après le guillemet fermant
		*quote = '\0'; // Réinitialiser quote
	}
	else if (is_metachar(s[*i])) // Gestion des métacaractères
	{
		// Si c'est un double métacaractère (>> ou <<)
		if ((s[*i] == '>' || s[*i] == '<') && s[*i + 1] == s[*i])
		{
			if (s[*i + 2] == s[*i]) // Erreur si triple métacaractère
				return (-1);
			(*i) += 2; // Avancer de 2 pour les doubles métacaractères
		}
		else
			(*i)++; // Avancer après le métacaractère
	}
	else
	{
		// Parcourir jusqu'au prochain espace ou métacaractère
		while (s[*i] != ' ' && s[*i] != '\0' && !is_metachar(s[*i]) && s[*i] != '\'' && s[*i] != '"')
			(*i)++;
	}
	return (0);
}

/* il y a un pb ici, pour les inputs du style test'ici' il faudrait compter seulement un mot. Tout le reste est correct */
int	count_args(char *s)
{
	int		i;
	int		count;
	char	quote;

	count = 0;
	i = 0;
	quote = '\0';
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != '\0')
		{
			count++;
			if (logic_count_args(s, &i, &quote) == -1)
				return (-1);
		}
	}
	printf("count ==== %d\n", count);
	return (count);
}
