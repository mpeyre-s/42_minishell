/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:07:03 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/18 23:05:09 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	wait_for_children(pid_t *pids, int count)
{
	int	i;
	int	status;
	int	exit_code;

	exit_code = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	i = 0;
	while (i <= count)
	{
		waitpid(pids[i], &status, 0);
		handle_signal_status(status);
		if (WIFSIGNALED(status))
			exit_code = 128 + WTERMSIG(status);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		i++;
	}
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_DFL);
	return (exit_code);
}

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
