/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:27:53 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/01/29 09:38:26 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_env(char **env)
{
	size_t	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}

int	ft_env(char **env)
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
		print_env(env);
		exit(EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
