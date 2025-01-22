/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:23:15 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/01/22 20:00:22 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_args(char **args, int option)
{
	printf("(%d)", option);
	size_t	i;

	i = 0;
	while (args[i])
		i++;
	ft_putstr_fd(args[i - 1], 1);
	if (!option)
		ft_putchar_fd('\n', 1);
}


static int	is_option(t_command *cmd)
{
	size_t	i;

	i = 1;
	while (cmd->args[i] && cmd->args[i][0] == '-')
	{
		if (ft_strncmp(cmd->args[i], "-n", ft_strlen(cmd->args[i])) == 0)
			return (1);
		i++;
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
		print_args(cmd->args, is_option(cmd));
		exit(EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
