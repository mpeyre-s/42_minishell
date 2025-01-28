/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:55:10 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/01/23 14:32:21 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(t_command *cmd)
{
	free_command(cmd);
	exit(EXIT_SUCCESS);
}

void	free_command(t_command *command)
{
	t_command	*tmp;
	size_t		i;

	while (command)
	{
		tmp = command;
		command = command->next;
		i = -1;
		if (tmp->args)
		{
			while (tmp->args[++i])
				free(tmp->args[i]);
			free(tmp->args);
		}
		if (tmp->input_file)
			free(tmp->input_file);
		if (tmp->heredoc_delim)
			free(tmp->heredoc_delim);
		if (tmp->output_file)
			free(tmp->output_file);
		free(tmp);
	}
}
