/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:47:39 by hduflos           #+#    #+#             */
/*   Updated: 2025/01/20 19:42:12 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_metachar(int c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	logic_count_args(char *s, int *i, char quote)
{
	if (s[*i] == '\'' || s[*i] == '"')
	{
		quote = s[*i];
		i++;
		// Parcourir jusqu'à la fin des guillemets ou de la chaîne
		while (s[*i] != quote && s[*i] != '\0')
			i++;
		if (s[*i] == quote)
			i++; // Avancer après le guillemet fermant
	}
	else if (is_metachar(s[*i]))
	{
		// Si c'est un métacaractère, vérifier les doubles métacaractères (<< ou >>)
		if ((s[*i] == '>' || s[*i] == '<') && s[*i + 1] == s[*i])
		{
			if (s[*i + 2] == s[*i])
				return (-1);
			i++; // Ignorer le deuxième caractère des doubles métacaractères
		}
		i++; // Avancer après le métacaractère
	}
	else
	{
		// Parcourir jusqu'au prochain espace ou métacaractère
		while (s[*i] != ' ' && s[*i] != '\0' && !is_metachar(s[*i]) && s[*i] != '\'' && s[*i] != '"')
			i++;
	}
	return (0);
}

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
			if (logic_count_args(s, &i, quote) == -1)
				return (-1);
		}
	}
	printf(" count ==== %d\n", count);
	return (count);
}
