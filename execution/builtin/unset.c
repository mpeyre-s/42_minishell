/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:56:10 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/14 22:07:03 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_tabfree(char **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

static int	delete_env_var(char ***env, int index)
{
	char	**new_env;
	size_t	size;
	size_t	i;
	size_t	j;

	size = 0;
	while ((*env)[size])
		size++;
	new_env = malloc(sizeof(char *) * size);
	if (!new_env)
		return (-1);
	i = -1;
	j = 0;
	while (j < size - 1)
	{
		if ((int)++i != index)
			new_env[j++] = ft_strdup((*env)[i]);
	}
	new_env[size - 1] = NULL;
	ft_tabfree(*env);
	*env = new_env;
	return (0);
}

int	ft_unset(t_command *cmd, char ***env)
{
	int	index_to_modify;

	if (!cmd->args[1])
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		return (2);
	}
	index_to_modify = env_var_exist(cmd, *env);
	if (index_to_modify != -1)
	{
		if (delete_env_var(env, index_to_modify) == -1)
			return (1);
	}
	return (0);
}
