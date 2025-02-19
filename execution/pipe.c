/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeyre-s <mpeyre-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:02:46 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/19 15:13:50 by mpeyre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_fds(int i, int count, int (*pipe_fds)[2], t_command *cur)
{
	int	f;

	if (i == 0 && cur->pipe_out)
		dup2(pipe_fds[0][1], STDOUT_FILENO);
	else if (i == count)
	{
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
		if (cur->output_file)
		{
			if (cur->append == 2)
				f = open(cur->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				f = open(cur->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (f == -1)
				handle_error("open output_file", NULL, NULL);
			dup2(f, STDOUT_FILENO);
			close(f);
		}
	}
	else
	{
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
		dup2(pipe_fds[i][1], STDOUT_FILENO);
	}
	close_pipes(pipe_fds, count);
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

int	execute_command(t_command *cmd, char ***env, int (*pipe_fds)[2],
		pid_t *pids)
{
	int			i;
	int			result;
	int			count;
	t_command	*cur;

	i = 0;
	cur = cmd;
	result = 1;
	count = count_pipes(cmd);
	while (i <= count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			handle_error("fork", pids, pipe_fds);
		if (pids[i] == 0)
		{
			setup_fds(i, count, pipe_fds, cur);
			close_pipes(pipe_fds, count);
			result = exec_cmd(cur, env);
			exit(EXIT_FAILURE);
		}
		cur = cur->next;
		i++;
	}
	return (result);
}

int	(*allocate_pipe_fds(int count))[2]
{
	int	(*pipe_fds)[2];

	pipe_fds = malloc(count * sizeof(*pipe_fds));
	if (!pipe_fds)
		handle_error("malloc", NULL, pipe_fds);
	return (pipe_fds);
}

int	execute_pipe(t_command *cmd, char ***env)
{
	int		count;
	pid_t	*pids;
	int		(*pipe_fds)[2];
	int		result;

	count = count_pipes(cmd);
	pids = allocate_pids(count);
	pipe_fds = allocate_pipe_fds(count);
	create_pipes(pipe_fds, count, pids);
	execute_command(cmd, env, pipe_fds, pids);
	close_pipes(pipe_fds, count);
	result = wait_for_children(pids, count);
	free(pids);
	free(pipe_fds);
	return (result);
}
