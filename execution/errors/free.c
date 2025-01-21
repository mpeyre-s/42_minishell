/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:35:07 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/01/21 15:35:30 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_command(t_command *command)
{
	size_t	i;

	i = -1;
	if (command)
	{
		if (command->args)
		{
			while (command->args[++i])
				free(command->args[i]);
			free(command->args);
		}
		if (command->input_file)
			free(command->input_file);
		if (command->heredoc_delim)
			free(command->heredoc_delim);
		if (command->output_file)
			free(command->output_file);
		free(command);
	}
}
