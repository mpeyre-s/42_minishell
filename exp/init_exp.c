/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:05:41 by spike             #+#    #+#             */
/*   Updated: 2025/02/03 19:55:44 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_variable(t_exp *exp, const char *var_name)
{
	char *value;

	value = getenv(var_name);
	if (value)
	{
		exp->av[exp->ac] = ft_strdup(var_name);
		exp->translate[exp->ac] = ft_strdup(value);
		exp->ac++;
	}
}

void	init_exp(t_exp *exp)
{
	int	size;

	size = 6;	// 6 variables à gérer : HOME, PATH, USER, PWD, SHELL, HOSTNAME (on peut faire plus mais j'ai la flemme)
	exp->av = calloc(size + 1, sizeof(char *));
	exp->translate = calloc(size + 1, sizeof(char *));


	if (!exp->av || !exp->translate)
	{
		ft_putstr_fd("Erreur d'allocation mémoire pour les variables d'environnement", 2);
		return ;
	}

	exp->ac = 0; // il faut mettre le dollar non ?
	init_variable(exp, "HOME");
	init_variable(exp, "PATH");
	init_variable(exp, "USER");
	init_variable(exp, "PWD");
	init_variable(exp, "SHELL");
	init_variable(exp, "HOSTNAME");

	exp->av[exp->ac] = NULL;
	exp->translate[exp->ac] = NULL;
}
