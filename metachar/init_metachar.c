/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_metachar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:27:31 by spike             #+#    #+#             */
/*   Updated: 2025/02/18 18:50:30 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_metachar(int ac, t_args *args)
{
	args->metachar = (int *)ft_calloc(ac, sizeof(int));
	if (!args->metachar)
		return (-1);
	args->pipe = (int *)ft_calloc(ac, sizeof(int));
	if (!args->pipe)
		return (-1);
	args->redirect_output = (int *)ft_calloc(ac, sizeof(int));
	if (!args->redirect_output)
		return (-1);
	args->append_redirect = (int *)ft_calloc(ac, sizeof(int));
	if (!args->append_redirect)
		return (-1);
	args->redirect_input = (int *)ft_calloc(ac, sizeof(int));
	if (!args->redirect_input)
		return (-1);
	args->heredoc = (int *)ft_calloc(ac, sizeof(int));
	if (!args->heredoc)
		return (-1);
	return (0);
}

void	check_metachar(t_args *args, char *av, int quote, int i)
{
	int	len;

	len = ft_strlen(av);
	if (ft_strncmp(av, "|", len) == 0 && quote == 0 && len == 1)
		args->pipe[i] = 1;
	if (ft_strncmp(av, ">", len) == 0 && quote == 0 && len == 1)
		args->redirect_output[i] = 1;
	if (ft_strncmp(av, ">>", len) == 0 && quote == 0 && len == 2)
		args->append_redirect[i] = 1;
	if (ft_strncmp(av, "<", len) == 0 && quote == 0 && len == 1)
		args->redirect_input[i] = 1;
	if (ft_strncmp(av, "<<", len) == 0 && quote == 0 && len == 2)
		args->heredoc[i] = 1;
	if (args->pipe[i] == 1 || args->redirect_input[i] == 1
		|| args->redirect_output[i] == 1
		|| args->append_redirect[i] == 1
		|| args->heredoc[i] == 1)
		args->metachar[i] = 1;
}

int	init_all(t_args *args)
{
	int	i;

	if (init_metachar(args->ac, args) == -1)
	{
		free_metachar(args);
		return (-1);
	}
	i = 0;
	while (i < args->ac)
	{
		check_metachar(args, args->av[i], args->was_quoted[i], i);
		i++;
	}
	return (0);
}
