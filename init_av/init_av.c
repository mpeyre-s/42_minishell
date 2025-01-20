/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_av.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:56:49 by hduflos           #+#    #+#             */
/*   Updated: 2025/01/20 15:27:16 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_args(char *s, int *i, int *start)
{
	char	quote = '\0';

	// Ignorer les espaces
	skip_spaces(s, i);
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



/* Cette fonction va comme son nom l'indique initialiser **av avec
av[0] = le programme demandé
av[1], av[2], etc pour les arguments du programme
Les fonctions du haut represente simplement un split particulier à ce projet */
char	**init_av(char *str, int *error)
{
	int		i;
	char	**result;
	int		words;
	int		start;
	int		index;

	words = count_args(str);
	if (words == -1) // => erreur dans les metachars >>> ou <<<
	{
		error_handle("You can't use >>> or <<<");
		return (NULL);
	}

	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	index = 0;
	i = 0;
	while (str[i])
	{
		if (!parse_args(str, &i, &start))
			break ;
		result[index] = extract_words(str, i, start);
		if (!result[index])
			return (error_malloc(result, index, error));
		index++;
	}
	result[index] = NULL;
	if (check_error_quote(result, index))
		quote_prompt(result, index);
	return (result);
}
