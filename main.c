/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:31:16 by hduflos           #+#    #+#             */
/*   Updated: 2025/02/18 19:31:52 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exp(t_exp **exp)
{
	if (!exp || !*exp)
		return ;
	free_split(&(*exp)->av, (*exp)->ac);
	free_split(&(*exp)->translate, (*exp)->ac);
	free(*exp);
	*exp = NULL;
}

int	exec(char *rl, t_args *args, t_exp **exp, char ***env)
{
	t_command	*cmd;
	int			result;

	if (empty_rl(rl))
		return (0);
	cmd = create_command(args, 0);
	if (!cmd)
	{
		ft_putstr_fd("Error: failed to parse commands\n", 2);
		return (-1);
	}
	result = start_exec(cmd, env, 0);
	free_exp(exp);
	*exp = malloc(sizeof(t_exp));
	if (!*exp || init_exp(*exp, *env) == -1)
		return (-1);
	free((*exp)->translate[0]);
	(*exp)->translate[0] = ft_itoa(result);
	if (!(*exp)->translate[0])
	{
		free_command_list(cmd);
		return (-1);
	}
	free_command_list(cmd);
	return (result);
}

int	parsing(char *rl, t_args *args, t_exp *exp)
{
	if (empty_rl(rl))
		return (0);
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

void	shell_loop(char *rl, t_args *args, t_exp *exp, char ***env)
{
	while (1)
	{
		usleep(5000);
		rl = readline (COMPUTER " Minishell > " RESET);
		if (!rl || (strncmp(rl, "exit", 4) == 0 && (rl[4] == '\0'
					|| rl[4] == ' ')))
		{
			free_env(env);
			free(env);
			stop_main(BYE " bye bye \n\n" RESET, args, exp, rl);
			exit(0);
		}
		add_history(rl);
		if (parsing(rl, args, exp) == -1)
		{
			free_main("pb parsing\n", args, rl);
			continue ;
		}
		if (exec(rl, args, &exp, env) == -1)
		{
			free_main("pb exec\n", args, rl);
			continue ;
		}
		free_main(NULL, args, rl);
	}
}

int	main(int ac, char **av, char **env)
{
	t_args	*args;
	t_exp	*exp;
	char	*rl;
	char	***shell_env;

	if (ac > 1)
	{
		printf("problem with arguments");
		return (0);
	}
	(void)av;
	shell_env = ft_strdup_env(env);
	shell_lvl(shell_env);
	args = malloc(sizeof(t_args));
	exp = malloc(sizeof(t_exp));
	rl = NULL;
	if (!args || !exp)
		return (stop_main("problem w/ malloc\n", args, exp, rl));
	if (init_exp(exp, env) == -1)
		return (stop_main("\nEnv error\n", args, exp, rl));
	handle_signals();
	shell_loop(rl, args, exp, shell_env);
	return (0);
}
