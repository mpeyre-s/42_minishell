/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:10:35 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/04 18:21:24 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Redirects stdout to a file and executes a command.
 * @cmd: Command structure with command and output file path.
 */
int	modify_stdout_and_exec(t_command *cmd, char ***env)
{
	int	original_stdout;
	int	file_fd;

	original_stdout = dup(STDOUT_FILENO);
	file_fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd < 0)
		return (1);
	if (dup2(file_fd, STDOUT_FILENO) < 0)
	{
		close(file_fd);
		return (1);
	}
	exec_cmd(cmd, env);
	if (dup2(original_stdout, STDOUT_FILENO) < 0)
	{
		close(file_fd);
		close(original_stdout);
		return (1);
	}
	close(file_fd);
	close(original_stdout);
	return (0);
}
