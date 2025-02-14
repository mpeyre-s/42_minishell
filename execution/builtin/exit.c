/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:55:10 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/14 22:08:31 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(t_command *cmd)
{
	int	exit_code;

	if (cmd->args[1])
	{
		exit_code = ft_atoi(cmd->args[1]);
		if (exit_code < 0 || exit_code > 255)
		{
			ft_putstr_fd("exit: exit code out of range\n", STDERR_FILENO);
			exit(255);
		}
		free_command(cmd);
		exit(exit_code);
	}
	free_command(cmd);
	exit(0);
}
