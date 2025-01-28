/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:30:31 by spike             #+#    #+#             */
/*   Updated: 2025/01/28 09:13:57 by spike            ###   ########.fr       */
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
	if (!cmd->args)
		return ;
	i = 0;
	j = 0;
	while (start + j < end)
	{
		if (args->metachar[start + j] == 0)
		{
			cmd->args[i] = ft_strdup(args->av[start + j]);
			if (!cmd->args[i])
				return (free_str(cmd->args)) ;
			i++;
		}
		j++;
	}
	cmd->args[i] = NULL;
}

t_command	*parse_command(t_args *args, int start, int end)
{
	t_command *cmd;

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
	parse_metachar(args, start, end);
}

t_command	*create_command(t_args *args, int start)
{
	int	i;
	t_command *cmd;

	i = start;
	while (i < args->ac && args->pipe[i])
		i++;
	cmd = parse_command(args, start, i);
	if (!cmd)
		return (NULL);

	if (i != args->ac)
	{
		start = i + 1;
		cmd->next = create_command(args, start);
	}
	else
		cmd->next = NULL;
	return (cmd);
}
