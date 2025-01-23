/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:19:28 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/01/23 14:57:58 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exec_builtin(t_command *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])) == 0)
		return (ft_echo(cmd));
	else if (ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])) == 0)
		return (ft_exit(cmd));
	// else if (ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])) == 0)
	// 	return (ft_cd(cmd));
	// else if (ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])) == 0)
	// 	return (ft_pwd(cmd));
	// else if (ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])) == 0)
	// 	return (ft_export(cmd));
	// else if (ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])) == 0)
	// 	return (ft_unset(cmd));
	// else if (ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])) == 0)
	// 	return (ft_env(cmd));
	return (1);
}

static int	exec_bin(t_command *cmd, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd->args[0], cmd->args, env) == -1)
			exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		printf("\nFailed to fork\n");
		return (0);
	}
	else
	{
		// Waits for the child process with the given pid to finish execution.
		//The &status argument is used to store the exit status of the child process.
		waitpid(pid, &status, 0);
		// checks if the child process terminated normally
		if (WIFEXITED(status))
			// If the child process terminated normally,
			//this macro returns the exit status of the child process.
			return (WEXITSTATUS(status));
	}
	return (0);
}

/** Unique entry point for command execution.
* Execution of the entire commandS stocked in the linked list. Depending on the
* presence of pipes or redirections, it modifies the standard input/output
(stdin/stdout) accordingly. */
void	start_exec(t_command *cmd, char **env)
{
	while (cmd)
	{
		if (cmd->output_file)
			modify_stdout_and_exec(cmd, env);
		else
			exec_cmd(cmd, env);
		cmd = cmd->next;
	}
}

/** This function is called only to execute the command after checking
if it is an external command or an internal (builtin) command. */
void	exec_cmd(t_command *cmd, char **env)
{
	if (exec_builtin(cmd))
		return ;
	else if (exec_bin(cmd, env))
		return ;
	else
		printf("\n%s: command not found\n", cmd->args[0]);
}
