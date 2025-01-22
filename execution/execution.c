/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:19:28 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/01/22 19:01:12 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Unique entry point for command execution.
* Execution of the entire commandS stocked in the linked list. Depending on the
* presence of pipes or redirections, it modifies the standard input/output
(stdin/stdout) accordingly. */
void	start_exec(t_command *cmd)
{
	while (cmd)
	{
		if (cmd->output_file)
			modify_stdout_and_exec(cmd);
		else
			exec_cmd(cmd);
		cmd = cmd->next;
	}
}

/** This function is called only to execute the command after checking
if it is an external command or an internal (builtin) command. */
void	exec_cmd(t_command *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])) == 0)
		ft_echo(cmd);
}
