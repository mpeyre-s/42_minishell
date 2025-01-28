/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:02:39 by spike             #+#    #+#             */
/*   Updated: 2025/01/28 13:37:05 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_metachar(t_args *args)
{
	if (args->metachar)
		free(args->metachar);
	if (args->was_quoted)
		free(args->was_quoted);
	if (args->pipe)
		free(args->pipe);
	if (args->redirect_output)
		free(args->redirect_output);
	if (args->append_redirect)
		free(args->append_redirect);
	if (args->redirect_input)
		free(args->redirect_input);
	if (args->heredoc)
		free(args->heredoc);
	return (-1);
}
int	free_split(char **str, int index)
{
	while (index--)
	{
		if (str[index])
			free(str[index]);
	}
	free(str);
	return (-1);
}

int	free_main(char *s, t_args *args, t_exp *exp, char *rl)
{
	if (args)
	{
		free_split(args->av, args->ac);
		free (args);
	}
	if (exp)
	{
		free_split(exp->av, args->ac);
		free_split(exp->translate, args->ac);
		free (exp);
	}
	if (rl)
		free (rl);
	if (s)
		perror(s); // perror pas ouf
	return (1);
}

