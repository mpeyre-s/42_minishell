/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_av.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:56:49 by hduflos           #+#    #+#             */
/*   Updated: 2025/02/18 18:54:28 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_words(char *s, int i, int start)
{
	int		length;
	char	*result;

	length = i - start;
	result = malloc((length + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + start, length + 1);
	return (result);
}

char	**init_av(char *str, int *index, int i)
{
	char	**result;
	int		words;
	int		start;

	words = count_args(str);
	if (words == -1)
	{
		perror("You can't use >>> or <<<\n");
		return (NULL);
	}
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (!parse_args(str, &i, &start))
			break ;
		result[*index] = extract_words(str, i, start);
		if (!result[*index])
			return (NULL);
		(*index)++;
	}
	result[*index] = NULL;
	return (result);
}
