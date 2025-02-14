/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:07:03 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/14 23:10:07 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_error(const char *msg, pid_t *pids, int (*pipe_fds)[2])
{
	perror(msg);
	if (pids)
		free(pids);
	if (pipe_fds)
		free(pipe_fds);
	exit(EXIT_FAILURE);
}

int	count_pipes(t_command *cmd)
{
	int			count;
	t_command	*cur;

	count = 0;
	cur = cmd;
	while (cur->next)
	{
		if (cur->pipe_out == 1)
			count++;
		cur = cur->next;
	}
	return (count);
}

pid_t	*allocate_pids(int count)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * (count + 1));
	if (!pids)
		handle_error("malloc", NULL, NULL);
	return (pids);
}

int	(*allocate_pipe_fds(int count))[2]
{
	int	(*pipe_fds)[2];

	pipe_fds = malloc(count * sizeof(*pipe_fds));
	if (!pipe_fds)
		handle_error("malloc", NULL, pipe_fds);
	return (pipe_fds);
}

void	create_pipes(int (*pipe_fds)[2], int count, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pipe(pipe_fds[i]) == -1)
			handle_error("pipe", pids, pipe_fds);
		i++;
	}
}
