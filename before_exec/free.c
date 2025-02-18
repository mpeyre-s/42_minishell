/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:44:06 by spike             #+#    #+#             */
/*   Updated: 2025/02/18 18:53:44 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_str(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		free_str(cmd->args);
	if (cmd->input_file)
		free(cmd->input_file);
	if (cmd->output_file)
		free(cmd->output_file);
	if (cmd->heredoc_delim)
		free(cmd->heredoc_delim);
	free(cmd);
}

void	free_command_list(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free_command(cmd);
		cmd = tmp;
	}
}

void	free_env(char ***env)
{
	int	i;

	if (!env || !*env)
		return ;
	i = 0;
	while ((*env)[i])
	{
		free((*env)[i]);
		i++;
	}
	free(*env);
	*env = NULL;
}
