/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:01:43 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/01/29 13:43:37 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	add_env_var(t_command *cmd, char **env)
{
	size_t	i;
	size_t	size;
	size_t	var_len;
	char	*new_var;

	i = -1;
	size = 0;
	var_len = ft_strlen(cmd->args[1]);
	while (env[++i])
		size++;
	if (ft_realloc(env, size, size + 2) < 0)
		return (-1);
	new_var = (char *)malloc((var_len + 1) * sizeof(char));
	if (!new_var)
		return (-1);
	i = -1;
	while (++i < var_len)
		new_var[i] = cmd->args[1][i];
	new_var[i] = '\0';
	env[size] = new_var;
	env[size + 1] = NULL;
	return (0);
}

static int	modify_env_var(t_command *cmd, char **env, int index)
{
	size_t	size;
	size_t	i;
	char	*new_value;

	size = ft_strlen(cmd->args[1]);
	new_value = (char *)malloc((size + 1) * sizeof(char));
	if (!new_value)
		return (-1);
	i = 0;
	while (cmd->args[1][i] && i < size)
	{
		new_value[i] = cmd->args[1][i];
		i++;
	}
	new_value[i] = '\0';
	free(env[index]);
	env[index] = new_value;
	return (0);
}

static int	env_var_exist(t_command *cmd, char **env)
{
	size_t	i;
	size_t	var_len;
	char	*equal_pos;

	i = -1;
	equal_pos = ft_strchr(cmd->args[1], '=');
	if (equal_pos)
		var_len = (size_t)(equal_pos - cmd->args[1]);
	else
		var_len = ft_strlen(cmd->args[1]);
	while (env[++i])
	{
		if (ft_strncmp(cmd->args[1], env[i], var_len) == 0
			&& (env[i][var_len] == '=' || env[i][var_len] == '\0'))
			return (i);
	}
	return (-1);
}

int ft_export(t_command *cmd, char **env)
{
	int	pid;
	int	index_to_modify;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		if (!cmd->args[1])
			return (ft_env(env));
		index_to_modify = env_var_exist(cmd, env);
		if (index_to_modify != -1)
			modify_env_var(cmd, env, index_to_modify);
		else
			add_env_var(cmd, env);
		exit(EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
