/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:50:28 by spike             #+#    #+#             */
/*   Updated: 2025/02/14 18:02:51 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while((s1[i] == s2[i]) && s1[i] && s2[i])
// 		i++;
// 	return (s1[i]-s2[i]);
// }

// void	modify_exp(char *s1, char *s2, t_exp *exp, int flag)
// {
// 	int	i;

// 	i = 0;
// 	while(i < exp->ac)
// 	{
// 		if (ft_strcmp(s1, exp->av[i]) == 0)
// 			break;
// 		i++;
// 	}
// 	if (flag == 1)
// 	{
// 		if (i == exp->ac)
// 		{
// 			add_new_exp(exp, s1, s2);
// 		}
// 		else
// 		{
// 			free(exp->translate[i]);
// 			exp->translate[i] = ft_strdup(s2);
// 		}
// 	}
// 	else
// 		delete_one_exp(exp, i);
// }

// int	is_new_env(char **av, t_args *args, t_exp *exp)
// {
// 	int	i;
// 	int	len;
// 	int	quote;

// 	(void)exp;
// 	i = 0;
// 	while (av[i])
// 		i++;

// 	if (i != 3)
// 		return (0);

// 	len = ft_strlen(av[1]);
// 	quote = args->was_quoted[1];
// 	if (ft_strncmp(av[1], "=", len) == 0 && quote == 0 && len == 1)
// 	{
// 		modify_exp(av[0], av[2], exp, 1);
// 		print_exp(exp);
// 		return (-2);
// 	}
// 	return (0);
// }
