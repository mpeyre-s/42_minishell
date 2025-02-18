/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:30:31 by spike             #+#    #+#             */
/*   Updated: 2025/02/18 18:53:16 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_args(t_args *args, int start, int end)
{
	int	i;
	int	nb_metachar;
	int	len;

	i = 0;
	nb_metachar = 0;
	while (i + start < end)
	{
		if (args->metachar[i + start])
			nb_metachar++;
		i++;
	}
	len = end - start - nb_metachar;
	return (len);
}

void	parse_args_cmd(t_args *args, t_command *cmd, int start, int end)
{
	int	len;
	int	i;
	int	j;

	len = len_args(args, start, end);
	cmd->args = (char **)malloc((len + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (start + j < end)
	{
		if (args->metachar[start + j] == 0)
		{
			cmd->args[i] = ft_strdup(args->av[start + j]);
			if (!cmd->args[i])
				return (free_str(cmd->args));
			i++;
		}
		else if (args->redirect_input[start + j]
			|| args->redirect_output[start + j]
			|| args->append_redirect[start + j]
			|| args->heredoc[start + j])
			j++;
		j++;
	}
	cmd->args[i] = NULL;
}

void	parse_metachar(t_args *args, t_command *cmd, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (args->redirect_input[i] == 1)
			cmd->input_file = ft_strdup(args->av[i + 1]);
		else if (args->redirect_output[i] == 1)
		{
			cmd->output_file = ft_strdup(args->av[i + 1]);
			cmd->append = 1;
		}
		else if (args->append_redirect[i] == 1)
		{
			cmd->output_file = ft_strdup(args->av[i + 1]);
			cmd->append = 2;
		}
		else if (args->heredoc[i] == 1)
			cmd->heredoc_delim = ft_strdup(args->av[i + 1]);
		if (args->metachar[i])
			i++;
		i++;
	}
}

t_command	*parse_command(t_args *args, int start, int end)
{
	t_command	*cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	parse_args_cmd(args, cmd, start, end);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	parse_metachar(args, cmd, start, end);
	return (cmd);
}

t_command	*create_command(t_args *args, int start)
{
	int			i;
	t_command	*cmd;

	i = start;
	while (i < args->ac && !args->pipe[i])
		i++;
	cmd = parse_command(args, start, i);
	if (!cmd)
		return (NULL);
	if (i != args->ac)
	{
		start = i + 1;
		cmd->pipe_out = 1;
		cmd->next = create_command(args, start);
	}
	else
		cmd->next = NULL;
	return (cmd);
}
