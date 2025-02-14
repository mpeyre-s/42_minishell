/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 00:27:39 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/15 00:27:49 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** Executes binary instructions with error recovery capabilities */
int	handle_child_process(t_command *cmd, char ***env, char *path)
{
	char	*full_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	full_path = ft_strjoin(path, cmd->args[0]);
	if (!full_path)
		exit(1);
	if (execve(full_path, cmd->args, *env) == -1)
	{
		free(full_path);
		if (errno == ENOENT)
			exit(127);
		exit(1);
	}
	return (0);
}
