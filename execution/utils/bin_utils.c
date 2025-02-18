/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 00:27:39 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/18 14:43:31 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** Executes binary instructions with error recovery capabilities */
int	handle_child_process(t_command *cmd, char ***env, char *path)
{
	char	*self_bin_path;

	self_bin_path = ft_strjoin("/", cmd->args[0]);
	if (!ft_strncmp(self_bin_path, path, ft_strlen(self_bin_path)))
	{
		free(path);
		path = ft_strdup(cmd->args[0]);
	}
	free(self_bin_path);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(path, cmd->args, *env) == -1)
	{
		if (errno == ENOENT)
			exit(127);
		exit(1);
	}
	return (0);
}

/** Split the PATH environment variable into an array of paths */
char	**split_path(char *path_env)
{
	char	**paths;
	int		i;
	int		len;
	char	**new_paths;

	len = 0;
	i = -1;
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	while (paths[len])
		len++;
	new_paths = malloc((len + 2) * sizeof(char *));
	if (!new_paths)
		return (NULL);
	new_paths[0] = ft_strdup("");
	while (++i < len)
		new_paths[i + 1] = paths[i];
	new_paths[len + 1] = NULL;
	free(paths);
	return (new_paths);
}
