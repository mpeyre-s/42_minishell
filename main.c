/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:31:16 by hduflos           #+#    #+#             */
/*   Updated: 2025/01/29 13:38:45 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
C'est ce code qui va lancer ton execution, dans la partie que j'ai faite, je crée la liste chainée
commande, depuis cette fonction t'as du coup "commande" et "exp" que tu pourras utiliser.
*/
int	exec(char *rl, t_args *args, t_exp *exp, char **env)
{
	t_command	*cmd;
	int			result;

	(void)rl;
	(void)exp;

	cmd = create_command(args, 0);
	if (!cmd)
	{
		ft_putstr_fd("Error: failed to parse commands\n", 2);
		return (-1);
	}
	//free_main(NULL, args, NULL, rl); // provoque un bug je crois

	//print_command_list(cmd); // print de test, doit aussi etre delete


	/* Ici tu devrais faire une fonction pour lancer ton execution */

	result = start_exec(cmd, env);

	// Libérer la mémoire, il fautdrait tout libérer
	free_command_list(cmd);

	// Faut delete ces 2 lignes, c'est juste pour ne pas etre stop par un -Werror
	rl = "hi";
	//printf("\n\n\n\n\nrl = %s, exp->ac = %d\n", rl, exp->ac);
	return (result);
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

int	main(int ac, char **av, char **ev)
{
	char	*rl;
	char	**env;
	t_args	*args;
	t_exp	*exp;

	(void)ac;
	(void)av;
	env = ft_strdup_env(ev);
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
		if (parsing(rl, args, exp) == -1)
			return (free_main("pb parsing\n", args, exp, rl));
		exec(rl, args, exp, env); // peut etre faire un if ?
		usleep(2000);
	}
	free_main("All good\n", args, exp, rl);
	return (0);
}
