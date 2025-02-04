/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:30:09 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/01/29 11:25:36 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_strdup_env(char **env)
{
	int		i;
	int		len;
	char	**new_env;

	i = 0;
	len = 0;
	while (env[len])
		len++;
	new_env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		return (NULL);
	while (i < len)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[len] = NULL;
	return (new_env);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		if (old_size < new_size)
			ft_memcpy(new_ptr, ptr, old_size);
		else
			ft_memcpy(new_ptr, ptr, new_size);
		free(ptr);
	}
	return (new_ptr);
}

