/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:31:16 by hduflos           #+#    #+#             */
/*   Updated: 2025/01/31 18:30:08 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
C'est ce code qui va lancer ton execution, dans la partie que j'ai faite, je crée la liste chainée
commande, depuis cette fonction t'as du coup "commande" et "exp" que tu pourras utiliser.
*/
int	exec(char *rl, t_args *args, t_exp *exp)
{
	t_command	*cmd;

	cmd = create_command(args, 0);
	if (!cmd)
	{
		ft_putstr_fd("Error: failed to parse commands\n", 2);
		return (-1);
	}
	//free_main(NULL, args, NULL, rl);
	print_command_list(cmd); // test

	/* Ici tu devrais faire une fonction pour lancer ton execution */

	// Libérer la mémoire
	free_command_list(cmd);
	//free(rl);
	rl = "hi";
	printf("\n\n\n\n\nrl = %s, exp->ac = %d\n", rl, exp->ac);

	return (0);
}

/*
Ici je fais juste mon parsing avec ma structure perso, c'est pas interessant pour toi
*/
int	parsing(char *rl, t_args *args, t_exp *exp)
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
	//print_split_result(args->av); // DEL
	if (parse_exp(args, exp) == -1)
		return (-1);  // est ce que je dois free_split ou est ce que mon free main fait deja tout ? meme chose au dessus ?
	if (deal_with_quote(args) == -1)
		return ((free_split(args->av, args->ac)));
	//print_test_quote(args);
	if (init_all(args) == -1)
		return (-1);
	//print_all(args);
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

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);

	while(1)
	{
		rl = readline (COMPUTER " Minishell > " RESET);
		 if (!rl)  // Si readline est interrompue
		{
			printf("\n");
			continue;  // On recommence au prompt sans quitter
		}
		add_history(rl);
		if (parsing(rl, args, exp) == -1)
			return (free_main("pb parsing\n", args, exp, rl));
		exec(rl, args, exp); // peut etre faire un if ?

	}
	clear_history();
	free_main("All good\n", args, exp, rl);
	return (0);
}
