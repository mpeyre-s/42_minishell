/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:31:16 by hduflos           #+#    #+#             */
/*   Updated: 2025/02/05 15:20:10 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
C'est ce code qui va lancer ton execution, dans la partie que j'ai faite, je crée la liste chainée
commande, depuis cette fonction t'as du coup "commande" et "exp" que tu pourras utiliser.
*/
int	exec(char *rl, t_args *args, t_exp *exp, char ***env)
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
	//print_command_list(cmd); // print de test, doit aussi etre delete

	/* Ici tu devrais faire une fonction pour lancer ton execution */

	result = start_exec(cmd, env);

	// Libérer la mémoire, il fautdrait tout libérer
	free_command_list(cmd);

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
		return (-1);
	if (check_error_quote(args->av, args->ac))
	{
		if (print_quote(args->av, args->ac) == -1)
			return (-1);
	}
	//print_split_result(args->av); // DEL
	if (parse_exp(args, exp) == -1)
		return (-1);
	if (deal_with_quote(args) == -1)
		return (-1);
	// if (is_new_env(args->av, args, exp) == -2)
	// 	return (-2);
	//print_test_quote(args);
	if (init_all(args) == -1)
		return (-1);
	//print_all(args);
	return (0);
}

void shell_loop(char *rl, t_args *args, t_exp *exp, char ***env)
{
	while (1)
	{
		usleep(2000);
		rl = readline (COMPUTER " Minishell > " RESET);
		if (!rl || (strncmp(rl, "exit", 4) == 0 && (rl[4] == '\0' || rl[4] == ' ')))
		{
			stop_main("\nbye bye\n", args, exp, rl); // doit gerer $?
			exit(0);
		}
		add_history(rl);
		if (parsing(rl, args, exp) == -1)
		{
			free_main("pb parsing\n", args, rl);
			continue;
		}

		if (exec(rl, args, exp, env) == -1)
		{
			free_main("pb exec\n", args, rl);
			continue;
		}
		free_main(NULL, args, rl); // on ne libère pas exp si c'est correct
	}
}

int	main(int ac, char **av, char **env)
{
	t_args	*args;
	t_exp	*exp;
	char *rl;
	char ***shell_env = ft_strdup_env(env);

	printf("%s\n\n\n", MINISHELL_TEST);
	(void)ac;
	(void)av;
	args = malloc(sizeof(t_args));
	exp = malloc(sizeof(t_exp));
	rl = NULL;
	if (!args || !exp)
		return (stop_main("problem w/ malloc\n", args, exp, rl));
	if (init_exp(exp, env) == -1)
		return (stop_main("\nEnv error\n", args, exp, rl));

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);

	shell_loop(rl, args, exp, shell_env);
	return (0);
}
