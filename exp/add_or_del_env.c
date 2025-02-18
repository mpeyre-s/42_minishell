/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_or_del_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:52:18 by spike             #+#    #+#             */
/*   Updated: 2025/02/18 19:04:42 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_and_free(t_exp *exp, char **new_av, char **new_translate)
{
	int	i;

	i = -1;
	while (++i < exp->ac)
	{
		new_av[i] = ft_strdup(exp->av[i]);
		new_translate[i] = ft_strdup(exp->translate[i]);
	}
	i = -1;
	while (++i < exp->ac)
	{
		free(exp->av[i]);
		free(exp->translate[i]);
	}
}

void	add_new_exp(t_exp *exp, char *s1, char *s2)
{
	char	**new_av;
	char	**new_translate;

	new_av = malloc((exp->ac + 1) * sizeof(char *));
	new_translate = malloc((exp->ac + 1) * sizeof(char *));
	if (!new_av || !new_translate)
		return ;
	add_and_free(exp, new_av, new_translate);
	new_av[exp->ac] = ft_strdup(s1);
	new_translate[exp->ac] = ft_strdup(s2);
	free(exp->av);
	free(exp->translate);
	exp->av = new_av;
	exp->translate = new_translate;
	exp->ac++;
}

void	del_one(t_exp *exp, int n, char **new_av, char **new_translate)
{
	int	i;

	i = -1;
	while (++i < exp->ac)
	{
		if (i != n)
		{
			new_av[i] = ft_strdup(exp->av[i]);
			new_translate[i] = ft_strdup(exp->translate[i]);
		}
	}
	i = -1;
	while (++i < exp->ac)
	{
		free(exp->av[i]);
		free(exp->translate[i]);
	}
}

void	delete_one_exp(t_exp *exp, int n)
{
	char	**new_av;
	char	**new_translate;

	if (n == exp->ac)
		return ;
	new_av = malloc((exp->ac - 1) * sizeof(char *));
	new_translate = malloc((exp->ac - 1) * sizeof(char *));
	if (!new_av || !new_translate)
		return ;
	del_one(exp, n, new_av, new_translate);
	free(exp->av);
	free(exp->translate);
	exp->av = new_av;
	exp->translate = new_translate;
	exp->ac--;
}
