/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:02:46 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/14 16:10:37 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_fds(int i, int count, int (*pipe_fds)[2], t_command *cur)
{
	if (i == 0 && cur->pipe_out)
		dup2(pipe_fds[0][1], STDOUT_FILENO);
	else if (i == count)
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
		dup2(pipe_fds[i][1], STDOUT_FILENO);
	}
}

void	close_pipes(int (*pipe_fds)[2], int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
	}
}

void	execute_command(t_command *cmd, char ***env, int (*pipe_fds)[2], int count, pid_t *pids)
{
	int			i;
	t_command	*cur;

	i = 0;
	cur = cmd;
	while (i <= count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			handle_error("fork", pids, pipe_fds);
		if (pids[i] == 0)
		{
			setup_fds(i, count, pipe_fds, cur);
			close_pipes(pipe_fds, count);
			exec_cmd(cur, env);
			exit(EXIT_FAILURE);
		}
		cur = cur->next;
		i++;
	}
}

void	wait_for_children(pid_t *pids, int count)
{
	int	i;
	int	status;

	i = 0;
	while (i <= count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
}

void	execute_pipe(t_command *cmd, char ***env)
{
	int		count;
	pid_t	*pids;
	int		(*pipe_fds)[2];

	count = count_pipes(cmd);
	pids = allocate_pids(count);
	pipe_fds = allocate_pipe_fds(count);
	create_pipes(pipe_fds, count, pids);
	execute_command(cmd, env, pipe_fds, count, pids);
	close_pipes(pipe_fds, count);
	wait_for_children(pids, count);
	free(pids);
	free(pipe_fds);
}
