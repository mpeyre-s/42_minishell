/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 00:27:39 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/17 22:12:52 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** Executes binary instructions with error recovery capabilities */
int	handle_child_process(t_command *cmd, char ***env, char *path)
{
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
	if (!path_env)
		return (NULL);
	return (ft_split(path_env, ':'));
}
