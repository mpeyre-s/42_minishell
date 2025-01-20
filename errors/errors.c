/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:02:39 by spike             #+#    #+#             */
/*   Updated: 2025/01/20 19:31:09 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		free_split(exp->transltate, args->ac);
		free (exp);
	}
	if (rl)
		free (rl);
	perror(s);
	return (1);
}

