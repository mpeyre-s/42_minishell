/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:30:09 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/14 22:54:27 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_env_array(char **env, int i)
{
	while (i > 0)
		free(env[--i]);
	free(env);
}

static int	get_env_len(char **env)
{
	int	len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

static char	**create_env_copy(char **env, int len)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			free_env_array(new_env, i);
			return (NULL);
		}
		i++;
	}
	new_env[len] = NULL;
	return (new_env);
}

char	***ft_strdup_env(char **env)
{
	char	***env_ptr;
	char	**new_env;
	int		len;

	len = get_env_len(env);
	new_env = create_env_copy(env, len);
	if (!new_env)
		return (NULL);
	env_ptr = (char ***)malloc(sizeof(char **));
	if (!env_ptr)
	{
		free_env_array(new_env, len);
		return (NULL);
	}
	*env_ptr = new_env;
	return (env_ptr);
}

char	*get_env_var(char **env, char *var)
{
	char	*prefix;
	int		i;
	int		prefix_len;

	if (!env || !var)
		return (NULL);
	prefix = ft_strjoin(var, "=");
	if (!prefix)
		return (NULL);
	prefix_len = ft_strlen(prefix);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], prefix, prefix_len) == 0)
		{
			free(prefix);
			return (env[i] + prefix_len);
		}
		i++;
	}
	free(prefix);
	return (NULL);
}
