/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:31:16 by hduflos           #+#    #+#             */
/*   Updated: 2025/01/20 10:56:20 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	parsing(char *rl, t_args *args, t_exp *exp)
{
	args->av = init_av(rl);
}

int	main(void)
{
	char	*rl;
	t_args	*args;
	t_exp	*expansion;

	printf("%s\n\n\n", MINISHELL_TEST);

	args = malloc(sizeof(t_args));
	if (!args)
		return (error_handle("problem with args allocation\n"));
	expansion = malloc(sizeof(t_exp));
	if (!expansion)
		return (error_handle("problem with expansion allocation\n"));
	// TODO : init basic extantions
	while(1)
	{
		rl = readline (COMPUTER " Minishell > " RESET);
		if (!rl)
			return (error_handle("problem with rl fct\n"));
		if (parsing(rl, args, expansion) == -1)
			return (parsing_error(rl, args, expansion));
	}
	return (0);
}


//TODO : errors
