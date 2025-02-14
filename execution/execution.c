/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:19:28 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/14 22:51:47 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exec_builtin(t_command *cmd, char ***env)
{
	if (ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])) == 0)
		return (ft_echo(cmd));
	else if (ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])) == 0)
		return (ft_exit(cmd));
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

/** Executes binary instructions with error recovery capabilities */
static int	exec_bin(t_command *cmd, char ***env, char *path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(ft_strjoin(path, cmd->args[0]), cmd->args, *env) == -1)
			exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		printf("\nFailed to fork\n");
		return (-1);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_sigint);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

/** Unique entry point for command execution.
* Execution of the entire commandS stocked in the linked list. Depending on the
* presence of pipes or redirections, it modifies the standard input/output
(stdin/stdout) accordingly. */
int	start_exec(t_command *cmd, char ***env, int flag)
{
	t_command	*next_cmd;
	int			result;

	if (!flag && (cmd->heredoc_delim || cmd->input_file))
	{
		if (cmd->heredoc_delim)
			result = stdin_heredoc(cmd, cmd->heredoc_delim, env, &flag);
		else if (cmd->input_file)
			result = modify_stdin_and_exec(cmd, env, &flag);
		return (0);
	}
	while (cmd)
	{
		next_cmd = cmd->next;
		if (cmd->pipe_out && next_cmd)
		{
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

/** This function is called only to execute the command after checking
if it is an external command or an internal (builtin) command. */
int	exec_cmd(t_command *cmd, char ***env)
{
	int	builtin_result;
	int	bin_result;

	builtin_result = exec_builtin(cmd, env);
	if (builtin_result >= 0)
		return (builtin_result);
	bin_result = exec_bin(cmd, env, "");
	if (bin_result != 1)
		return (bin_result);
	bin_result = exec_bin(cmd, env, "/bin/");
	if (bin_result != 1)
		return (bin_result);
	bin_result = exec_bin(cmd, env, "/usr/bin/");
	if (bin_result != 1)
		return (bin_result);
	printf("%s: command not found\n", cmd->args[0]);
	return (127);
}
