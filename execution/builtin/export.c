/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeyre-s <mpeyre-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:01:43 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/17 16:22:52 by mpeyre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	add_env_var(t_command *cmd, char ***env)
{
	char	**new_env;
	size_t	size;
	size_t	i;

	new_env = create_new_env(*env, &size);
	if (!new_env)
		return (-1);
	if (copy_old_env(env, new_env, &i) == -1)
		return (-1);
	new_env[i] = create_full_var(cmd->args[1], cmd->args[3]);
	if (!new_env[i])
		return (free_new_env(new_env, i));
	new_env[i + 1] = NULL;
	free_env(env);
	*env = new_env;
	return (0);
}

static int	modify_env_var(t_command *cmd, char **env, int index)
{
	char	*var_name;
	char	*var_value;
	char	*full_var;
	char	*new_value;

	var_name = cmd->args[1];
	var_value = cmd->args[3];
	if (var_value && var_value[0] == '"'
		&& var_value[ft_strlen(var_value)-1] == '"')
	{
		var_value++;
		var_value[ft_strlen(var_value) - 1] = '\0';
	}
	full_var = ft_strjoin(var_name, "=");
	if (!full_var)
		return (-1);
	new_value = ft_strjoin(full_var, var_value);
	free(full_var);
	if (!new_value)
		return (-1);
	free(env[index]);
	env[index] = new_value;
	return (0);
}

int	env_var_exist(t_command *cmd, char **env)
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

int	ft_export(t_command *cmd, char ***env)
{
	int	index_to_modify;

	if (!cmd->args[1])
		return (ft_env(*env));
	if (!cmd || !env || !*env)
		return (1);
	index_to_modify = env_var_exist(cmd, *env);
	if (index_to_modify != -1)
	{
		if (modify_env_var(cmd, *env, index_to_modify) == -1)
			return (1);
	}
	else
	{
		if (add_env_var(cmd, env) == -1)
			return (1);
	}
	return (0);
}
