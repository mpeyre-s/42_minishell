/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:31:16 by hduflos           #+#    #+#             */
/*   Updated: 2025/01/21 13:21:36 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	parsing(char *rl, t_args *args /*t_exp *exp*/)
{
	args->ac = 0;
	args->av = init_av(rl, &args->ac, 0);
	if (!args->av)
		return (free_split(args->av, args->ac));
	if (check_error_quote(args->av, args->ac))
	{
		if (print_quote(args->av, args->ac) == -1)
			return (free_split(args->av, args->ac));
	}
	print_split_result(args->av); // DEL
	return (0);
}

int	main(void)
{
	char	*rl;
	t_args	*args;
	t_exp	*exp;

	printf("%s\n\n\n", MINISHELL_TEST);

	rl = NULL;
	args = malloc(sizeof(t_args));
	exp = malloc(sizeof(t_exp));
	if (!args || !exp)
		return (free_main("problem w/ malloc\n", args, exp, rl));
	init_exp(exp);
	while(1)
	{
		rl = readline (COMPUTER " Minishell > " RESET);
		if (!rl)
			return (free_main("problem with rl fct\n", args, exp, rl));
		if (parsing(rl, args /*, exp*/) == -1)
			return (free_main("pb parsing\n", args, exp, rl));
	}
	free_main("All good\n", args, exp, rl);
	return (0);
}
