/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_av.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:56:49 by hduflos           #+#    #+#             */
/*   Updated: 2025/01/20 14:48:24 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



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
