/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 09:18:52 by spike             #+#    #+#             */
/*   Updated: 2025/01/31 23:36:29 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int quoted(char *av)
{
	int i = 0;
	int count = 0;
	char quote = '\0';

	while (av[i])
	{
		if ((av[i] == '\'' || av[i] == '"'))
		{
			if (quote == '\0')
			{
				quote = av[i];
				count++;
			}
			else if (quote == av[i])
			{
				quote = '\0';
				count++;
			}
		}
		i++;
	}
	return count;
}

char	*remove_outer_quotes(char *av, char quote, int i, int j)
{
	int		nb_quote;
	int		len;
	char	*new_av;

	nb_quote = quoted(av);
	len = ft_strlen(av) - nb_quote;
	new_av = malloc(len + 1);
	if (!new_av)
		return (NULL);

	while (av[++i])
	{
		if (av[i] == '\'' || av[i] == '"')
		{
			if (quote == '\0') // Ouvrir une quote
				quote = av[i];
			else if (quote == av[i]) // Fermer la quote
				quote = '\0';
			else
				new_av[j++] = av[i]; // Quote interne, on la garde
		}
		else
			new_av[j++] = av[i];
	}
	new_av[j] = '\0';
	return (new_av);
}

int	delete_quote(char **av)
{
	char *new_av = remove_outer_quotes(*av, '\0', -1, 0);
	if (!new_av)
		return (-1);

	free(*av);
	*av = new_av;
	return (0);
}

int	deal_with_quote(t_args *args)
{
	int	i;
	// on initialise quote a 0
	args->was_quoted = (int *)ft_calloc(args->ac, sizeof(int));
	if (!args->was_quoted)
		return (-1);

	// on met quote a 1 si on a trouve un ' ou "
	i = 0;
	while (i < args->ac)
	{
		if (quoted(args->av[i]))
			args->was_quoted[i] = 1;
		i++;
	}

	i = 0;
	while (i < args->ac)
	{
		if (args->was_quoted[i] == 1)
		{
			if (delete_quote(&args->av[i]) == -1)
			{
				free(args->was_quoted);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}
