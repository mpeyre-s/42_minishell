/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:31:16 by hduflos           #+#    #+#             */
/*   Updated: 2025/02/14 18:11:39 by spike            ###   ########.fr       */
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
	result = start_exec(cmd, env, 0);

	// Libérer la mémoire, il fautdrait tout libérer
	free_command_list(cmd);
	return (result);
}

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
	if (parse_exp(args, exp) == -1)
		return (-1);
	if (deal_with_quote(args) == -1)
		return (-1);
	if (init_all(args) == -1)
		return (-1);
	return (0);
}

void shell_loop(char *rl, t_args *args, t_exp *exp, char ***env)
{
	while (1)
	{
		usleep(5000);
		rl = readline (COMPUTER " Minishell > " RESET);
		if (!rl || (strncmp(rl, "exit", 4) == 0 && (rl[4] == '\0' || rl[4] == ' ')))
		{
			stop_main(BYE " bye bye \n\n" RESET, args, exp, rl); // doit gerer $?
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
