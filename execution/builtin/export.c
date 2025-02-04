/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:01:43 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/04 19:44:18 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	free_new_env(char **new_env, size_t i)
{
	while (i--)
		free(new_env[i]);
	free(new_env);
	return (-1);
}

static char	*build_var_str(t_command *cmd, char **new_env, size_t i)
{
	char	*var_str;
	char	*tmp;
	size_t	j;

	var_str = ft_strdup("");
	if (!var_str)
		return (NULL);
	j = 1;
	while (cmd->args[j])
	{
		tmp = var_str;
		var_str = ft_strjoin(var_str, cmd->args[j]);
		free(tmp);
		if (!var_str)
		{
			free_new_env(new_env, i);
			return (NULL);
		}
		j++;
	}
	return (var_str);
}

static char	**create_new_env(char **env, size_t *size)
{
	char	**new_env;

	*size = 0;
	while (env[*size])
		(*size)++;
	new_env = malloc(sizeof(char *) * (*size + 2));
	return (new_env);
}

static int	copy_old_env(char ***env, char **new_env, size_t *i)
{
	*i = 0;
	while ((*env)[*i])
	{
		new_env[*i] = ft_strdup((*env)[*i]);
		if (!new_env[*i])
			return (free_new_env(new_env, *i));
		(*i)++;
	}
	return (0);
}

static int	add_env_var(t_command *cmd, char ***env)
{
	char	**new_env;
	size_t	size;
	size_t	i;
	char	*var_str;

	new_env = create_new_env(*env, &size);
	if (!new_env)
		return (-1);
	if (copy_old_env(env, new_env, &i) == -1)
		return (-1);
	var_str = build_var_str(cmd, new_env, i);
	if (!var_str)
		return (-1);
	new_env[i] = var_str;
	new_env[i + 1] = NULL;
	*env = new_env;
	return (0);
}

static int	modify_env_var(t_command *cmd, char **env, int index)
{
	char	*new_value;
	size_t	j;
	char	*tmp;

	new_value = ft_strdup("");
	if (!new_value)
		return (-1);
	j = 1;
	while (cmd->args[j])
	{
		tmp = new_value;
		new_value = ft_strjoin(new_value, cmd->args[j]);
		free(tmp);
		if (!new_value)
			return (-1);
		j++;
	}
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

int ft_export(t_command *cmd, char ***env)
{
	int	index_to_modify;

	if (!cmd->args[1])
		return (ft_env(*env));
	index_to_modify = env_var_exist(cmd, *env);
	if (index_to_modify != -1)
		modify_env_var(cmd, *env, index_to_modify);
	else
		add_env_var(cmd, env);
	return (EXIT_SUCCESS);
}
