/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:30:41 by spike             #+#    #+#             */
/*   Updated: 2025/02/03 14:45:01 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	inside_single_quote(char *av, int limit)
{
	int	i;
	int	count;

	if (limit == -1)
		limit = ft_strlen(av);

	i = 0;
	count = 0;
	while (i < limit)
	{
		if (av[i] == '\'')
			count++;
		i++;
	}
	return (count % 2 != 0);
}

int	search_and_count_dollars(char *av)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (av[i])
	{
		if (av[i] == '$' && !inside_single_quote(av, i))
			count++;
		i++;
	}
	return (count);
}

char	*substr_dollar(char *av)
{
	int	i;
	int	start;
	char *sub_av;

	i = 0;
	while (av[i])
	{
		if (av[i] == '$' && !inside_single_quote(av, i))
			break ;
		i++;
	}
	start = i;
	printf("start a cb ? %d\n", start); // del
	i++;
	while (av[i])
	{
		if (av[i] == '$' || av[i] == '"' || av[i] == ' ')
			break ;
		i++;
	}
	printf("i a cb ? %d\n", i); // del
	sub_av = ft_substr(av, start, i - start);
	if (!sub_av)
		return (NULL);
	return (sub_av);
}

int	parse_exp(t_args *args, t_exp *exp) // je vais probablement devoir mettre i dans les args pour gagner des lignes
{
	int	i;
	int dollars;
	char *sub_av;

	i = 0;
	while (i < args->ac)
	{
		dollars = search_and_count_dollars(args->av[i]);
		while (dollars--)
		{
			if (!inside_single_quote(args->av[i], -1))
			{
				sub_av = substr_dollar(args->av[i]); // pas besoin de free si l'allocation ne fonctionne pas ?
				if (!sub_av)
					return (-1);
				if (replace_av(sub_av, &args->av[i], 0, exp) == -1)
				{
					free(sub_av);
					return (-1);
				}
				printf("av[%d] // new av = %s\n\n", i, args->av[i]); //del
				free(sub_av);
			}
		}
		i++;
	}
	return (0);
}
