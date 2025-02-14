/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:10:35 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/14 22:50:05 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	modify_stdout(t_command *cmd, char ***env)
{
	int	original_stdout;
	int	file_fd;
	int	result;

	original_stdout = dup(STDOUT_FILENO);
	file_fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd < 0)
		return (1);
	if (dup2(file_fd, STDOUT_FILENO) < 0)
	{
		close(file_fd);
		return (1);
	}
	result = exec_cmd(cmd, env);
	if (dup2(original_stdout, STDOUT_FILENO) < 0)
	{
		close(file_fd);
		close(original_stdout);
		return (1);
	}
	close(file_fd);
	close(original_stdout);
	return (result);
}

int	modify_stdout_append(t_command *cmd, char ***env)
{
	int	original_stdout;
	int	file_fd;
	int	result;

	original_stdout = dup(STDOUT_FILENO);
	file_fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file_fd < 0)
		return (1);
	if (dup2(file_fd, STDOUT_FILENO) < 0)
	{
		close(file_fd);
		return (1);
	}
	result = exec_cmd(cmd, env);
	if (dup2(original_stdout, STDOUT_FILENO) < 0)
	{
		close(file_fd);
		close(original_stdout);
		return (1);
	}
	close(file_fd);
	close(original_stdout);
	return (result);
}

/**
 * Redirects stdout to a file and executes a command.
 * @cmd: Command structure with command and output file path.
 */
int	modify_stdout_and_exec(t_command *cmd, char ***env)
{
	if (cmd->append == 1)
		return (modify_stdout(cmd, env));
	else if (cmd->append == 2)
		return (modify_stdout_append(cmd, env));
	return (0);
}

/**
 * Redirects stdin to a file and executes a command.
 * @cmd: Command structure with command and input file path.
 */

int	modify_stdin_and_exec(t_command *cmd, char ***env, int *flag)
{
	int	original_stdin;
	int	file_fd;
	int	result;

	*flag = 1;
	original_stdin = dup(STDIN_FILENO);
	file_fd = open(cmd->input_file, O_RDONLY);
	if (file_fd < 0)
		return (1);
	if (dup2(file_fd, STDIN_FILENO) < 0)
	{
		close(file_fd);
		return (1);
	}
	result = start_exec(cmd, env, *flag);
	if (dup2(original_stdin, STDIN_FILENO) < 0)
	{
		close(file_fd);
		close(original_stdin);
		return (1);
	}
	close(file_fd);
	close(original_stdin);
	return (result);
}
