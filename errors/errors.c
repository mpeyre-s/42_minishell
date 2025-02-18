/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:02:39 by spike             #+#    #+#             */
/*   Updated: 2025/02/18 19:02:11 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_metachar2(t_args *args)
{
	if (args->append_redirect)
	{
		free(args->append_redirect);
		args->append_redirect = NULL;
	}
	if (args->redirect_input)
	{
		free(args->redirect_input);
		args->redirect_input = NULL;
	}
	if (args->heredoc)
	{
		free(args->heredoc);
		args->heredoc = NULL;
	}
}

int	free_metachar(t_args *args)
{
	if (args->metachar)
	{
		free(args->metachar);
		args->metachar = NULL;
	}
	if (args->was_quoted)
	{
		free(args->was_quoted);
		args->was_quoted = NULL;
	}
	if (args->pipe)
	{
		free(args->pipe);
		args->pipe = NULL;
	}
	if (args->redirect_output)
	{
		free(args->redirect_output);
		args->redirect_output = NULL;
	}
	free_metachar2(args);
	return (-1);
}

int	free_split(char ***str, int index)
{
	if (!str || !*str)
		return (-1);
	while (index > 0)
	{
		index--;
		if ((*str)[index])
		{
			free((*str)[index]);
			(*str)[index] = NULL;
		}
	}
	free(*str);
	*str = NULL;
	return (-1);
}

int	stop_main(char *s, t_args *args, t_exp *exp, char *rl)
{
	if (args)
		free (args);
	if (exp)
	{
		free_split(&exp->av, exp->ac);
		free_split(&exp->translate, exp->ac);
		free (exp);
	}
	if (rl)
	{
		clear_history();
		free (rl);
	}
	if (s)
		ft_putstr_fd(s, 2);
	return (1);
}

int	free_main(char *s, t_args *args, char *rl)
{
	if (args)
	{
		free_split(&args->av, args->ac);
		free_metachar(args);
		args->ac = 0;
	}
	if (rl)
		free (rl);
	if (s)
		ft_putstr_fd(s, 2);
	return (1);
}
