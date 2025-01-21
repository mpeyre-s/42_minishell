/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:36:22 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/01/21 15:41:23 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_exec(t_command *command)
{
	if (ft_strncmp(command->args[0], "exit", 4) == 0)
		exit_properly(command);
}

void	exit_properly(t_command *command)
{
	free_command(command);
}
