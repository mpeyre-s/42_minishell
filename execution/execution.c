/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeyre-s <mpeyre-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:19:28 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/19 15:13:33 by mpeyre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exec_builtin(t_command *cmd, char ***env)
{
	if (ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])) == 0)
		return (ft_echo(cmd));
	else if (ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])) == 0)
		return (ft_pwd(cmd));
	else if (ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])) == 0)
		return (ft_cd(cmd, env));
	else if (ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])) == 0)
		return (ft_export(cmd, env));
	else if (ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])) == 0)
		return (ft_unset(cmd, env));
	else if (ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])) == 0)
		return (ft_env(*env));
	return (-1);
}

static int	exec_bin(t_command *cmd, char ***env, char *path)
{
	pid_t	pid;
	int		status;
	char	*full_path;
	char	*temp_path;

	temp_path = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp_path, cmd->args[0]);
	free(temp_path);
	if (!full_path)
		return (127);
	pid = fork();
	if (pid == 0)
		return (handle_child_process(cmd, env, full_path));
	else if (pid < 0)
		return (ft_putstr_fd("\nFailed to fork\n", 2), -1);
	handle_signals_and_wait(pid, &status);
	free(full_path);
	handle_signal_status(status);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

static int	process_cmd_sequence(t_command *cmd, char ***env, int result)
{
	t_command	*next_cmd;

	while (cmd)
	{
		next_cmd = cmd->next;
		if (cmd->pipe_out && next_cmd)
		{
			if (cmd->output_file)
				result = modify_stdout_and_exec(cmd, env);
			result = execute_pipe(cmd, env);
			while (cmd && cmd->pipe_out)
				cmd = cmd->next;
			if (cmd)
				cmd = cmd->next;
		}
		else
		{
			if (cmd->output_file)
				result = modify_stdout_and_exec(cmd, env);
			else
				result = exec_cmd(cmd, env);
			cmd = cmd->next;
		}
	}
	return (result);
}

int	start_exec(t_command *cmd, char ***env, int flag)
{
	int	result;

	result = 0;
	if (!flag && (cmd->heredoc_delim || cmd->input_file))
	{
		if (cmd->heredoc_delim)
			result = stdin_heredoc(cmd, cmd->heredoc_delim, env, &flag);
		else if (cmd->input_file)
			result = modify_stdin_and_exec(cmd, env, &flag);
		return (result);
	}
	result = process_cmd_sequence(cmd, env, 0);
	return (result);
}

int	exec_cmd(t_command *cmd, char ***env)
{
	int		builtin_result;
	int		bin_result;
	char	**paths;
	char	*path_env;
	int		i;

	builtin_result = exec_builtin(cmd, env);
	if (builtin_result >= 0)
		return (builtin_result);
	path_env = get_env_var(*env, "PATH");
	paths = split_path(path_env);
	if (!paths)
		return (printf("%s: command not found\n", cmd->args[0]), 127);
	i = -1;
	while (paths[++i])
	{
		bin_result = exec_bin(cmd, env, paths[i]);
		if (bin_result != 127)
		{
			free_str(paths);
			return (bin_result);
		}
	}
	free_str(paths);
	return (printf("%s: command not found\n", cmd->args[0]), 127);
}
