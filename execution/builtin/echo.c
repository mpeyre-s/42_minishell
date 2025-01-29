/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:23:15 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/01/29 08:58:15 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_string(char **args, int option)
{
	size_t	i;

	i = 1;
	if (option)
		i = 2;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!option)
		ft_putchar_fd('\n', 1);
}

static int	is_option(t_command *cmd)
{
	if (cmd->args[1] && cmd->args[1][0])
	{
		if (ft_strncmp(cmd->args[1], "-n", ft_strlen(cmd->args[1])) == 0)
			return (1);
	}
	return (0);
}

int	ft_echo(t_command *cmd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		print_string(cmd->args, is_option(cmd));
		exit(EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
