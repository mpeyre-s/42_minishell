/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:24:37 by spike             #+#    #+#             */
/*   Updated: 2025/02/18 18:56:35 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	modify_env(char ***env, int i, int level)
{
	char	*new_env;
	char	*lvl;

	lvl = ft_itoa(level);
	if (!lvl)
		return ;
	new_env = ft_strjoin("SHLVL=", lvl);
	free(lvl);
	if (!new_env)
		return ;
	free((*env)[i]);
	(*env)[i] = new_env;
}

void	shell_lvl(char ***env)
{
	int		i;
	int		level;

	if (!env || !*env)
		return ;
	i = 0;
	while ((*env)[i])
	{
		if (strncmp((*env)[i], "SHLVL=", 6) == 0)
			break ;
		i++;
	}
	if (!(*env)[i])
		return ;
	level = ft_atoi((*env)[i] + 6) + 1;
	modify_env(env, i, level);
}
