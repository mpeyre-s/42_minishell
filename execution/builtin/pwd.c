/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:04:34 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/14 22:07:20 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	print_path(t_command *cmd)
{
	char	*buffer;
	size_t	size;

	(void)cmd;
	size = 4916;
	buffer = malloc(size);
	if (buffer == NULL)
	{
		perror("malloc");
		return (1);
	}
	if (getcwd(buffer, size) == NULL)
	{
		perror("getcwd");
		free(buffer);
		return (1);
	}
	write(1, buffer, ft_strlen(buffer));
	write(1, "\n", 1);
	free(buffer);
	return (0);
}

int	ft_pwd(t_command *cmd)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		if (print_path(cmd) != 0)
			exit(1);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
