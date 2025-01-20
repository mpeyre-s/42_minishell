/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:28:05 by hduflos           #+#    #+#             */
/*   Updated: 2025/01/20 15:29:54 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_metachar(char *s, int *i)
{
	if (is_metachar(s[*i]))
	{
		if ((s[*i] == '>' || s[*i] == '<') && s[*i + 1] == s[*i])
			(*i) += 2;
		else
			(*i)++;
		return (1); // Métacaractère détecté
	}
	return (0); // Aucun métacaractère traité
}

int	handle_quotes(char *s, int *i, char *quote)
{
	if ((s[*i] == '\'' || s[*i] == '"') && *quote == '\0')
	{
		*quote = s[*i];
		(*i)++;
		return (1);
	}
	else if (s[*i] == *quote && *quote != '\0')
	{
		*quote = '\0';
		(*i)++;
		return (1);
	}
	return (0); // Aucun guillemet traité
}

int	parse_args(char *s, int *i, int *start)
{
	char	quote = '\0';

	// Ignorer les espaces
	while (s[*i] == ' ')
		(*i)++;
	if (s[*i] == '\0')
		return (0); // Plus d'arguments

	*start = *i; // Marquer le début de l'argument

	while (s[*i] != '\0')
	{
		// Gérer les guillemets
		if (handle_quotes(s, i, &quote))
			continue;

		// Gérer les métacaractères
		if (handle_metachar(s, i))
			break;

		// Fin d'un argument standard
		if (quote == '\0' && s[*i] == ' ')
			break;

		(*i)++;
	}
	return (1); // Argument trouvé
}
