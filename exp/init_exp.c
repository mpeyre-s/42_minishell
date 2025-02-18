/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:05:41 by spike             #+#    #+#             */
/*   Updated: 2025/02/18 19:05:16 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_each_env(t_exp *exp, char *env)
{
	int	i;
	int	total_len;

	total_len = ft_strlen(env);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	exp->av[exp->ac] = ft_substr(env, 0, i);
	if (!exp->av[exp->ac])
		return (-1);
	if (env[i] == '=')
		exp->translate[exp->ac] = ft_substr(env, i + 1, total_len - (i + 1));
	else
		exp->translate[exp->ac] = ft_strdup("");
	if (!exp->translate[exp->ac])
		return (-1);
	exp->ac++;
	return (0);
}

int	init_exp(t_exp *exp, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	exp->av = calloc(i + 2, sizeof(char *));
	exp->translate = calloc(i + 2, sizeof(char *));
	if (!exp->av || !exp->translate)
		return (-1);
	exp->av[0] = ft_strdup("?");
	exp->translate[0] = ft_strdup("0");
	exp->ac = 1;
	i = 0;
	while (env[i])
	{
		if (parse_each_env(exp, env[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
