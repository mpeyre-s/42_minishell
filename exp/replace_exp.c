/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:08:11 by spike             #+#    #+#             */
/*   Updated: 2025/02/18 19:05:04 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_strings(char *before, char *after, char *exp)
{
	if (before)
		free(before);
	if (after)
		free(after);
	if (exp)
		free(exp);
	return (-1);
}

int	split_av(char *av, int start, char **before, char **after)
{
	int	len;
	int	i;

	*before = ft_substr(av, 0, start);
	if (!*before)
		return (-1);
	i = start + 1;
	len = 0;
	while (av[i] && av[i] != ' ' && av[i] != '"' && av[i] != '$')
	{
		len++;
		i++;
	}
	*after = ft_substr(av, start + 1 + len, ft_strlen(av) - (start + 1 + len));
	if (!*after)
	{
		free(*before);
		return (-1);
	}
	return (0);
}

int	find_variable_start(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] == '$' && !inside_single_quote(av, i))
			return (i);
		i++;
	}
	return (-1);
}

int	replace_av(char *substr, char **av, int start, t_exp *exp)
{
	char	*before;
	char	*after;
	char	*expansion;
	char	*new_av;
	int		i;

	start = find_variable_start(*av);
	if (start == -1)
		return (-1);
	if (split_av(*av, start, &before, &after) == -1)
		return (-1);
	i = check_expansion(substr, exp);
	if (i == -1)
		expansion = ft_strdup("");
	else
		expansion = ft_strdup(exp->translate[i]);
	new_av = build_new_av(before, expansion, after);
	free_strings(before, after, expansion);
	if (!new_av)
		return (-1);
	free(*av);
	*av = new_av;
	return (0);
}
