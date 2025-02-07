/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:55:38 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/07 16:46:57 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	free_new_env(char **new_env, size_t i)
{
	while (i--)
		free(new_env[i]);
	free(new_env);
	return (-1);
}

char	**create_new_env(char **env, size_t *size)
{
	char	**new_env;

	*size = 0;
	while (env[*size])
		(*size)++;
	new_env = malloc(sizeof(char *) * (*size + 2));
	return (new_env);
}

int	copy_old_env(char ***env, char **new_env, size_t *i)
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

char	*create_full_var(char *var_name, char *var_value)
{
	char	*full_var;
	char	*result;

	if (var_value && var_value[0] == '"'
		&& var_value[ft_strlen(var_value) - 1] == '"')
	{
		var_value++;
		var_value[ft_strlen(var_value) - 1] = '\0';
	}
	full_var = ft_strjoin(var_name, "=");
	if (!full_var)
		return (NULL);
	result = ft_strjoin(full_var, var_value);
	free(full_var);
	return (result);
}

int	ft_arraylen(char **array)
{
	int	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}
